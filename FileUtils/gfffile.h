#ifndef GFF_FILE_H_
#define GFF_FILE_H_

#include <fstream>
#include <string>
#include <map>

#include "typedef.h"
#include "genomefile.h"

namespace rivals {
  class Interval;

  class GFFfile : public GenomeFile  {
  public:
    GFFfile(std::string filename);
    ~GFFfile();

    bool next(std::string & chr, Interval & c);
    const std::map<std::string, std::pair<Capacity, Capacity> > & getChrMap() const;

  private:
    Capacity count;
    std::map<std::string, std::pair<Capacity, Capacity> > chrmap;
    std::ifstream file_in;
    std::string line;
    std::string curr_chr;
    Capacity curr_chr_start;
  };

}

#endif
