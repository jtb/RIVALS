#include "flatten.h"

using namespace std;
namespace rivals {
  Flatten::Flatten(Iterator & a) : Iterator(), iter(a), count(0), clean_up(true) {
    has_score = true;
  }

  const ChromList & Flatten::getChrList(){
    return iter.getChrList();
  }

  void Flatten::setChr(std::string chrom){
    iter.setChr(chrom);
    if(iter.next(chrom, head)){
      count = 1;
    }
    clean_up = true;
  }

  bool Flatten::next(std::string & chrom, Interval & intv){
    Interval b;
    while(iter.next(chrom, b)){
      if(b.getStart() <= head.getStop()){
	if(b.getStop() > head.getStop()) head.setStop(b.getStop());
	count++;
      }else{
	intv = head;
	intv.setStrand(BOTH);
	head = b;
	score = count;
	count = 1;
	return true;
      }
    }

    if(clean_up){
      intv = head;
      intv.setStrand(BOTH);
      score = count;
      clean_up = false;
      return true;
    }
    return false;
  }
}
