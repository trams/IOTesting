#include <exam/suite.h>

#include <string>

class write_perf
{
  public:
    ~write_perf();

    int EXAM_DECL(empty);

    int EXAM_DECL(write_10_t);
    int EXAM_DECL(write_20_t);
    int EXAM_DECL(write_50_t);
  private:
    int write_file(const std::string& filename, int block_count);

    std::vector<std::string> files_to_delete_;
};
