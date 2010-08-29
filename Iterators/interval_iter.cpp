#include "interval_iter.h"

using namespace std;

namespace rivals {

  IntervalIter::IntervalIter(string chr, Domain start, Domain stop) : Iterator(), chromosome(chr), head(start, stop, BOTH), done(true) {
    chr_list.insert(chromosome);
  }

  void IntervalIter::setChr(std::string chrom){
    done = true;
    if(!chrom.compare(chromosome)) done = false;
  }

  bool IntervalIter::next(std::string & chrom, Interval & intv){
    if(!done){
      done = true;
      chrom = chromosome;
      intv = head;
      return true;
    }
    return false;
  }

}
