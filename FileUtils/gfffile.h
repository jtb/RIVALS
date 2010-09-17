#ifndef GFF_FILE_H_
#define GFF_FILE_H_

#include <fstream>
#include <string>
#include <map>

#include "genomefile.h"

namespace rivals {
  class Interval;

  class GFFfile : public GenomeFile  {
  public:
    GFFfile(std::string filename);
    ~GFFfile();

    bool next(std::string & chr, Interval & c);

  private:
    std::ifstream file_in;
    std::string line;
  };

}

#endif
