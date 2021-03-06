#include "write_perf.h"

#include <exam/suite.h>
#include <misc/opts.h>
#include <iostream>

int main(int argc, const char** argv)
{
  Opts opts;

  opts.description( "test suite for write perfomance" );
  opts.usage( "[options]" );

  opts << option<void>( "print this help message", 'h', "help" )
       << option<void>( "list all test cases", 'l', "list" )
       << option<std::string>( "run tests by number <num list>", 'r', "run" )
       << option<void>( "print status of tests within test suite", 'v', "verbose" )
       << option<void>(  "trace checks", 't', "trace" );

  try {
    opts.parse( argc, argv );
  }
  catch (...) {
    opts.help( std::cerr );
    return 1;
  }

  if ( opts.is_set( 'h' ) ) {
    opts.help( std::cerr );
    return 0;
  }

  exam::trivial_time_logger tlogger(std::cout);
  exam::test_suite t("write perfomance test suite", 20);
  t.set_logger(&tlogger);

  write_perf p;

  t.add( &write_perf::empty, p, "an empty test case");

  t.add( &write_perf::write_10_t, p, "write a 40 megabyte file");
  t.add( &write_perf::write_20_t, p, "write a 80 megabyte file");
  t.add( &write_perf::write_50_t, p, "write a 200 megabyte file");
  t.add( &write_perf::write_100_t, p, "write a 400 megabyte file");
  t.add( &write_perf::write_200_t, p, "write a 800 megabyte file");

  t.add( &write_perf::write_10_t_randomly, p, "write a 40 megabyte file randomly");
  t.add( &write_perf::write_20_t_randomly, p, "write a 80 megabyte file randomly");
  t.add( &write_perf::write_50_t_randomly, p, "write a 200 megabyte file randomly");
  t.add( &write_perf::write_100_t_randomly, p, "write a 400 megabyte file randomly");
  t.add( &write_perf::write_200_t_randomly, p, "write a 800 megabyte file randomly");

  t.add( &write_perf::crash_after_sync, p, "crash after a sync");
  t.add( &write_perf::crash_before_sync, p, "crash before a sync");

  if ( opts.is_set( 'l' ) ) {
    t.print_graph( std::cerr );
    return 0;
  }

  if ( opts.is_set( 'v' ) ) {
    t.flags( t.flags() | exam::base_logger::verbose );
  }

  if ( opts.is_set( 't' ) ) {
    t.flags( t.flags() | exam::base_logger::trace );
  }

  if ( opts.is_set( 'r' ) ) {
    std::stringstream ss( opts.get<std::string>( 'r' ) );
    int n;
    while ( ss >> n ) {
      t.single( n );
    }

    return 0;
  }

  return t.girdle();
}
