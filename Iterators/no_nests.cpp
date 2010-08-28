#include "no_nests.h"

using namespace std;

namespace rivals {
  
  NoNests::NoNests(Iterator & a) : Iterator(), iter(a) {
    empty = true;
    isFirst = false;
  }

  const ChromList & NoNests::getChrList(){
    return iter.getChrList();
  }

  void NoNests::setChr(std::string chrom){
    iter.setChr(chrom);
    empty = true;
    isFirst = true;
    if(iter.next(chrom, head)){
      empty = false;
    }
  }

  bool NoNests::next(string & chrom, Interval & intv){
    Interval b;
    while(!isEmpty()){
      if(isFirst || head.getStop() > endpoint){
	pop(chrom, intv);
	while(!isEmpty()){
	  if(head.getStart() == intv.getStart()){
	    pop(chrom, intv);
	  }else{
	    break;
	  }
	}
	isFirst = false;
	endpoint = intv.getStop();
	return true;
      }else{
	pop(chrom, intv);
      }
    }
    return false;
  }

}
