#ifndef UTILTS_H_
#define UTILTS_H_

#include <string>
#include <vector>

namespace rivals {
  void Tokenize(const std::string & str, std::vector<std::string> & tokens, const std::string & delimiters);
}

#endif
