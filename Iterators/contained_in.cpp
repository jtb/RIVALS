#include "contained_in.h"

using namespace std;

namespace rivals {

  ContainedIn::ContainedIn(Iterator & a, Iterator & b) : Iterator(), iterA(a), iterB(b) {
    mergeChromLists(iterA.getChrList(), iterB.getChrList());
  }

  void ContainedIn::setChr(std::string chrom){
    iterA.setChr(chrom);
    iterB.setChr(chrom);
    avalid = iterA.next(chromA, a);
    bvalid = iterB.next(chromB, b);
    endpoint = b.getStop();
  }

  bool ContainedIn::next(string & chrom, Interval & intv){
    while(avalid && bvalid){
      assert(chromA == chromB);
      if(a.getStart() < b.getStart()){
	avalid = iterA.next(chromA, a);
      }else{//b.start <= a.start
	if(b.getStop() > endpoint){
	  endpoint = b.getStop();
	}
	if(a.getStop() <= endpoint){
	  intv = a;
	  chrom = chromA;
	  avalid = iterA.next(chromA, a);
	  return true;
	}else{
	  bvalid = iterB.next(chromB, b);
	}
      }
    }
    return false;
  }

}
