#include "merge.h"

using namespace std;
namespace rivals {
  Merge::Merge(Iterator & a, Iterator & b) : Iterator(), itA(a), itB(b) {
    mergeChromLists(a.getChrList(), b.getChrList());
  }


  void Merge::setChr(std::string chrom){
    itA.setChr(chrom);
    itB.setChr(chrom);
    avalid = itA.next(chromA, a);
    bvalid = itB.next(chromB, b);
  }

  bool Merge::next(std::string & chrom, Interval & intv){
    if(!avalid && !bvalid) return false;
    
    if(avalid && !bvalid){
      intv = a;
      chrom = chromA;
      avalid = itA.next(chromA, a);
      return true;
    }
    if(!avalid && bvalid){
      intv = b;
      chrom = chromB;
      bvalid = itB.next(chromB, b);
      return true;
    }
    //avalid && bvalid
    assert(chromA == chromB);
    if(a < b){
      intv = a;
      chrom = chromA;
      avalid = itA.next(chromA, a);
    }else{
      intv = b;
      chrom = chromB;
      bvalid = itB.next(chromB, b);
    }
    return true;
  }

}
