#ifndef CONTAINED_IN_H_
#define CONTAINED_IN_H_

#include "iterator.h"
#include "no_nests.h"

namespace rivals {

  class ContainedIn : public Iterator {
  public:
    ContainedIn(Iterator & a, Iterator & b);
    ~ContainedIn(){}
    
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
    Domain endpoint;
  };

}

#endif
