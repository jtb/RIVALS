#include "overlaps.h"

using namespace std;

namespace rivals {

  Overlaps::Overlaps(Iterator & a, Iterator & b) : Iterator(), iterA(a), iterB(b) {
    mergeChromLists(iterA.getChrList(), iterB.getChrList());
  }

  void Overlaps::setChr(std::string chrom){
    iterA.setChr(chrom);
    iterB.setChr(chrom);
    avalid = iterA.next(chromA, a);
    bvalid = iterB.next(chromB, b);
  }

  bool Overlaps::next(string & chrom, Interval & intv){
    while(avalid && bvalid){
      assert(chromA == chromB);
      if(a.getStop() <= b.getStart()){
	avalid = iterA.next(chromA, a);
	continue;
      } 
      if(b.getStop() <= a.getStart()){
	bvalid = iterB.next(chromB, b);
	continue;
      }
      //Sb < Ea && Sa < Eb, so they overlap
      intv = a;
      chrom = chromA;
      avalid = iterA.next(chromA, a);
      return true;
    }
    return false;
  }
  
}
