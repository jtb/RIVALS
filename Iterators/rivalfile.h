#ifndef RIVAL_FILE_H_
#define RIVAL_FILE_H_

#include <fstream>
#include <string>
#include <map>
#include <set>

#include "typedef.h"
#include "genomefile.h"
#include "iterator.h"

namespace rivals {
  
  class RivalFile : public GenomeFile {
  public:
    RivalFile(Iterator & i);
    ~RivalFile();

    bool next(std::string & chr, Interval & c);

  private:
    Iterator & iter;
    std::set<std::string>::const_iterator it;
  };

}

#endif
