#ifndef BED_FILE_H_
#define BED_FILE_H_

#include <fstream>
#include <string>
#include <map>

#include "genomefile.h"

namespace rivals {
  class Interval;

  class BEDfile : public GenomeFile {
  public:
    BEDfile(std::string filename);
    ~BEDfile();

    bool next(std::string & chr, Interval & c);

  private:
    std::ifstream file_in;
    std::string line;
  };

}

#endif
