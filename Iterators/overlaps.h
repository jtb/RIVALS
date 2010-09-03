#ifndef OVERLAPS_H_
#define OVERLAPS_H_

#include "iterator.h"

namespace rivals {

  class Overlaps : public Iterator {
  public:
    Overlaps(Iterator & a, Iterator & b);
    ~Overlaps(){}
    
    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    
  private:
    Iterator & iterA;
    Iterator & iterB;
    Interval a;
    Interval b;
    bool avalid;
    bool bvalid;
    std::string chromA;
    std::string chromB;
  };

}

#endif
