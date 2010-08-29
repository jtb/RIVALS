#ifndef INTERVAL_ITER_H_
#define INTERVAL_ITER_H_

#include "iterator.h"

namespace rivals {

  class IntervalIter : public Iterator {
  public:
    IntervalIter(std::string chr, Domain start, Domain stop);
    ~IntervalIter(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);

  private:
    std::string chromosome;
    Interval head;
    bool done;
  };

}

#endif
