#ifndef NONESTS_H_
#define NONESTS_H_

#include "iterator.h"

namespace rivals {

  class NoNests : public Iterator {
  public:
    NoNests(Iterator & a);
    ~NoNests(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    const ChromList & getChrList();

  private:
    bool isEmpty(){
      return empty;
    }
    bool pop(std::string & chrom, Interval & intv){
      if(!empty){
	intv = head;
	empty = true;
	if(iter.next(chrom, head)){
	  empty = false;
	}
	return true;
      }
      return false;
    }

    Iterator & iter;
    Interval head;
    bool empty;
    bool isFirst;
    Domain endpoint;
  };

}

#endif
