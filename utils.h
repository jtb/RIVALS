#ifndef UTILTS_H_
#define UTILTS_H_

#include <string>
#include <vector>
#include <map>
#include "typedef.h"

namespace rivals {
  
  void Tokenize(const std::string & str, std::vector<std::string> & tokens, const std::string & delimiters);

  void writeChrMap(const std::map<std::string, std::pair<Capacity, Capacity> > & chrmap, std::string filename);

}

#endif
