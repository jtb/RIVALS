#ifndef ITERATORS_H_
#define ITERATORS_H_

#include <string>
#include <set>
#include <stack>

#include "typedef.h"
#include "cache.h"

namespace rivals {
  class Interval;
  typedef std::set<std::string> ChromList;

  class Iterator{
  public:
  Iterator() : chr(""), has_score(false), score(0) {
      chr_list.clear();
    }
    virtual ~Iterator(){}
    virtual void saveAsBED();

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
    bool has_score;
    int score;
    ChromList chr_list;
  };

  class Sample : public Iterator {
  public:
    Sample(std::string sample);
    Sample(std::string sample, std::string chrom);
    ~Sample(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);

  private:
    std::string samp_name;
    bool on_chromosome;
    Capacity index;
    off_t offset;
    ForwardCache<Interval> fvector;
    std::map<std::string, std::pair<Capacity, Capacity> > chrmap;
  };

  class Range : public Iterator {
  public:
    Range(std::string sample, std::string chrom, Domain start, Domain stop);
    ~Range(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
	    
  private:
    
    std::string samp_name;
    bool on_chromosome;
    Interval d;
    off_t offset;
    CenteredCache<Interval> cvector;
    std::map<std::string, std::pair<Capacity, Capacity> > chrmap;
    
    struct Cargo {
    Cargo(Capacity l, Capacity h, Capacity r) : low(l), high(h), root(r), goLeft(true) {}
      Capacity low;
      Capacity high;
      Capacity root;
      bool goLeft;
    };
    std::stack<Cargo> recurse;
  };

}

#endif
