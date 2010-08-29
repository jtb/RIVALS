#include "strand.h"

using namespace std;

namespace rivals {

  GetStrand::GetStrand(Iterator & a, int str) : Iterator(), iter(a), strand(str) {}

  const ChromList & GetStrand::getChrList(){ return iter.getChrList(); }

  void GetStrand::setChr(std::string chrom){ iter.setChr(chrom); }

  bool GetStrand::next(std::string & chrom, Interval & intv){
    while(iter.next(chrom, intv)){
      if(intv.getStrand() == strand){
	return true;
      }
    }
    return false;
  }

  SetStrand::SetStrand(Iterator & a, int str) : Iterator(), iter(a), strand(str) {}
  
  const ChromList & SetStrand::getChrList(){ return iter.getChrList(); }
  
  void SetStrand::setChr(std::string chrom){ iter.setChr(chrom); }

  bool SetStrand::next(std::string & chrom, Interval & intv){
    while(iter.next(chrom, intv)){
      intv.setStrand(strand);
      return true;
    }
    return false;
  }

}
