#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <string>
#include <map>

#include "iterator.h"
#include "typedef.h"
#include "cache.h"

namespace rivals {

  class Sample : public Iterator {
  public:
    Sample(std::string sample);
    Sample(std::string sample, std::string chrom);
    ~Sample(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    
  private:
    std::string samp_name;
    std::string chr;
    bool on_chromosome;
    Capacity index;
    off_t offset;
    ForwardCache<Interval> fvector;
    std::map<std::string, std::pair<Capacity, Capacity> > chrmap;
  };
}

#endif
