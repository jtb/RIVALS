#ifndef STRAND_H_
#define STRAND_H_

#include "iterator.h"

namespace rivals {

  class GetStrand : public Iterator {
  public:
    GetStrand(Iterator & a, int strand);
    ~GetStrand(){}
    
    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    const ChromList & getChrList();
  
  private:
    Iterator & iter;
    int strand;
  };
  
  class SetStrand : public Iterator {
  public:
    SetStrand(Iterator & a, int strand);
    ~SetStrand(){}
    
    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    const ChromList & getChrList();
  
  private:
    Iterator & iter;
    int strand;
  };


}

#endif
