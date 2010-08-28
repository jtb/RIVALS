#include "clique.h"

using namespace std;
namespace rivals {
  Clique::Clique(Iterator & a, Capacity minOverlap) : Iterator(), min_overlap(minOverlap), iter(a), in_interval(false), count(0), start(0), start_full(false) {
    has_score = true;
  }

  const ChromList & Clique::getChrList(){
    return iter.getChrList();
  }

  void Clique::setChr(std::string chrom){
    iter.setChr(chrom);
    Interval b;
    count = 0;
    start_pop(chrom, b);
  }

  bool Clique::next(std::string & chrom, Interval & intv){
    score = 0;
    in_interval = false;
    Interval b;
    while(!start_empty() || in_interval){
      //start
      Capacity end = endpoints.top();
      if(start_empty() || end <= start){
	endpoints.pop();
	count--;
	if(count < min_overlap && in_interval){
	  intv.setStop(end);
	  intv.setStrand(BOTH);
	  return true;
	}
      }else{//start < end
	count++;
	if(count >= min_overlap){
	  if(!in_interval){
	    in_interval = true;
	    score = count;
	    intv.setStart(start);
	  }else{
	    if(count > score) score = count;
	  }
	}
	start_pop(chrom, b);
      }
    }
    return false;
  }
  
}
