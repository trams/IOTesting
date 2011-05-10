#include "write_perf.h"

#include <mt/uid.h>

#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

write_perf::~write_perf()
{
  for (int i = 0; i < files_to_delete_.size(); ++i)
    unlink(files_to_delete_[i].c_str());
}

int EXAM_IMPL(write_perf::empty)
{
  return EXAM_RESULT;
}

int write_perf::write_file(const std::string& filename, int block_count)
{
  using namespace std;
  vector<char> block(4096);
  for (int i = 0; i < block.size(); ++i)
    block[i] = rand() % 256;

  fstream file(filename.c_str(), ios_base::out);
  for (int i = 0; i < block_count; ++i)
  {
    file.write(&block[0], block.size());
  }
  return 0;
}

int write_perf::write_file_randomly(const std::string& filename, int block_count)
{
  using namespace std;
  vector<char> block(4096);
  for (int i = 0; i < block.size(); ++i)
    block[i] = rand() % 256;

  vector<int> block_numbers(block_count);
  for (int i = 0; i < block_numbers.size(); ++i)
  {
    block_numbers[i] = i;
  }
  random_shuffle(block_numbers.begin(), block_numbers.end());

  fstream file(filename.c_str(), ios_base::out);
  for (int k = 0; k < block_numbers.size(); ++k)
  {
    file.seekp(block_numbers[k] * 4096);
    file.write(&block[0], block.size());
  }

  return 0;
}

// write files sequentially

int EXAM_IMPL(write_perf::write_10_t)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file(filename, 10*1000);
}

int EXAM_IMPL(write_perf::write_20_t)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file(filename, 20*1000);
}

int EXAM_IMPL(write_perf::write_50_t)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file(filename, 50*1000);
}

int EXAM_IMPL(write_perf::write_100_t)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file(filename, 100*1000);
}

int EXAM_IMPL(write_perf::write_200_t)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file(filename, 200*1000);
}

// write files randomly

int EXAM_IMPL(write_perf::write_10_t_randomly)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file_randomly(filename, 10*1000);
}

int EXAM_IMPL(write_perf::write_20_t_randomly)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file_randomly(filename, 20*1000);
}

int EXAM_IMPL(write_perf::write_50_t_randomly)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file_randomly(filename, 50*1000);
}

int EXAM_IMPL(write_perf::write_100_t_randomly)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file_randomly(filename, 100*1000);
}

int EXAM_IMPL(write_perf::write_200_t_randomly)
{
  std::string filename = xmt::uid_str();
  files_to_delete_.push_back(filename);

  return write_file_randomly(filename, 200*1000);
}

int EXAM_IMPL(write_perf::crash_after_sync)
{
  int* bad_address = NULL;
  const char* string = "Hello world!\n";

  std::fstream file("some_file_after", std::ios_base::out);
  file.write(string, 14);
  file.flush();

  *bad_address = 42;

  return EXAM_RESULT;
}

int EXAM_IMPL(write_perf::crash_before_sync)
{
  int* bad_address = NULL;
  const char* string = "Hello world!\n";

  std::fstream file("some_file_before", std::ios_base::out);
  file.write(string, 14);

  *bad_address = 42;

  return EXAM_RESULT;
}
