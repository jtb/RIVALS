#include <sstream>
#include <vector>
#include <iostream>
#include "rivalfile.h"

using namespace std;

namespace rivals {
  RivalFile::RivalFile(Iterator & i) : iter(i) {
    it = iter.getChrList().begin();
    if(it != iter.getChrList().end()){
      iter.setChr(*it);
    }
  }

  RivalFile::~RivalFile(){
  }
  
  bool RivalFile::next(string & chr, Interval & c){
    while(it != iter.getChrList().end()){
      if(iter.next(chr, c)) return true;
      ++it;
      if(it != iter.getChrList().end()) iter.setChr(*it);
      
    }
    return false;
  }
  
}
