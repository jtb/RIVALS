#ifndef MERGE_H_
#define MERGE_H_

#include <string>
#include "iterator.h"

namespace rivals {

  class Merge : public Iterator {
  public:
    Merge(Iterator & a, Iterator & b);
    ~Merge(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    
  private:
    Iterator & itA;
    Iterator & itB;
    Interval a;
    Interval b;
    bool avalid;
    bool bvalid;
    std::string chromA;
    std::string chromB;
  };

}

#endif
