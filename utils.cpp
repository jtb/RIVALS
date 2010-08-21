#include "utils.h"

using namespace std;

namespace rivals {

  void Tokenize(const string & str, vector<string> & tokens, const string & delimiters){
    string::size_type firstPos = 0;
    string::size_type lastPos = str.find_first_of(delimiters, firstPos);
    while(string::npos != lastPos){
      tokens.push_back(str.substr(firstPos, lastPos - firstPos));
      firstPos = lastPos + 1;
      lastPos = str.find_first_of(delimiters, firstPos);
    }
    tokens.push_back(str.substr(firstPos, lastPos - firstPos));
  }

}
