#ifndef ITERATORS_H_
#define ITERATORS_H_

#include <string>
#include <set>

#include "typedef.h"
#include "cache.h"

namespace rivals {
  class Interval;
  typedef std::set<std::string> ChromList;

  class Iterator{
  public:
  Iterator() : chr(""){}
    virtual ~Iterator(){}

    virtual bool next(std::string & chrom, Interval & intv) = 0;
    virtual void setChr(std::string chrom){
      chr = chrom;
    }
    
    virtual std::string getChr(){
      return chr;
    }
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
    
    std::string chr;
    ChromList chr_list;
  };

  //void saveAsBED(Iterator & iter);

  class Sample : public Iterator {
  public:
    Sample(std::string sample);
    ~Sample(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);

  private:
    std::string samp_name;
    Capacity index;
    off_t offset;
    ForwardCache<Interval> fvector;
    std::map<std::string, std::pair<Capacity, Capacity> > chrmap;
  };

}

#endif
