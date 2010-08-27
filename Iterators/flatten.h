#ifndef FLATTEN_H_
#define FLATTEN_H_

#include <string>
#include "iterator.h"

namespace rivals {

  class Flatten : public Iterator {
  public:
    Flatten(Iterator & a);
    ~Flatten(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    const ChromList & getChrList();

  private:
    Iterator & iter;
    Interval head;
    int count;
    bool clean_up;
  };

}

#endif
