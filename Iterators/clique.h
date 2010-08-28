#ifndef CLIQUE_H_
#define CLIQUE_H_

#include <string>
#include <queue>
#include "iterator.h"

namespace rivals {

  class Clique : public Iterator {
  public:
    Clique(Iterator & a, Capacity minOverlap);
    ~Clique(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    const ChromList & getChrList();

  private:
    void start_pop(std::string & chrom, Interval & intv){
      start_full = false;
      if(iter.next(chrom, intv)){
	start_full = true;
	start = intv.getStart();
	endpoints.push(intv.getStop());
      }
    }
    bool start_empty(){ return !start_full; }
   
    Capacity min_overlap;
    Iterator & iter;

    bool in_interval;
    Capacity count;
   
    Capacity start;
    bool start_full;
   
    std::priority_queue<Capacity, std::vector<Capacity>, std::greater<Capacity> > endpoints;

  };

}

#endif
