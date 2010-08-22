#ifndef RANGE_H_
#define RANGE_H_

#include <string>
#include <set>
#include <map>
#include <stack>

#include "iterator.h"
#include "typedef.h"
#include "cache.h"

namespace rivals {

  class Range : public Iterator {
  public:
    Range(std::string sample, std::string chrom, Domain start, Domain stop);
    ~Range(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    	    
  private:

    std::string samp_name;
    std::string chr;
    bool on_chromosome;
    Interval d;
    off_t offset;
    CenteredCache<Interval> cvector;
    std::map<std::string, std::pair<Capacity, Capacity> > chrmap;
    
    struct Cargo {
    Cargo(Capacity l, Capacity h, Capacity r) : low(l), high(h), root(r), goLeft(true) {}
      Capacity low;
      Capacity high;
      Capacity root;
      bool goLeft;
    };
    std::stack<Cargo> recurse;
  };
}

#endif
