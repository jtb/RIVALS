#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <string>
#include <set>
#include "interval.h"

namespace rivals {
  typedef std::set<std::string> ChromList;

  class Iterator{
  public:
  Iterator() : has_score(false), score(0) {
      chr_list.clear();
    }
    virtual ~Iterator(){}
    virtual void saveAsBED();

    virtual bool next(std::string & chrom, Interval & intv) = 0;
    virtual void setChr(std::string chrom) = 0;
    
    virtual const ChromList & getChrList(){
      return chr_list;
    }
    
  protected:
    virtual void mergeChromLists(const ChromList & clist1, const ChromList & clist2){
      chr_list.clear();
      ChromList::const_iterator it;
      for(it = clist1.begin(); it != clist1.end(); ++it){
	chr_list.insert(*it);
      }
      for(it = clist2.begin(); it != clist2.end(); ++it){
	chr_list.insert(*it);
      }
    }
    
    bool has_score;
    int score;
    ChromList chr_list;
  };
}

#endif
