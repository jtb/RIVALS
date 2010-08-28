#ifndef ITERS_H_
#define ITERS_H_

#include "iterator.h"
#include "sample.h"
#include "range.h"
#include "merge.h"
#include "flatten.h"
#include "clique.h"
#include "no_nests.h"

namespace rivals {

  class Chain {
  public:
    Iterator & range(std::string sample){
      Sample *s = new Sample(sample);
      v.push_back(s);
      return *s;
    }
    Iterator & range(std::string sample, std::string chrom){
      Sample *s = new Sample(sample, chrom);
      v.push_back(s);
      return *s;
    }
    Iterator & range(std::string sample, std::string chrom, Domain start, Domain stop){
      Range *r = new Range(sample, chrom, start, stop);
      v.push_back(r);
      return *r;
    }
    Iterator & range(std::string sample, std::string chrom, Domain point){
      Range *r = new Range(sample, chrom, point);
      v.push_back(r);
      return *r;
    }
    Iterator & merge(Iterator & a, Iterator & b){
      Merge * m = new Merge(a, b);
      v.push_back(m);
      return *m;
    }
    Iterator & flatten(Iterator & a){
      Flatten * f = new Flatten(a);
      v.push_back(f);
      return *f;
    }
    Iterator & clique(Iterator & a, Capacity minOverlap){
      Clique * c = new Clique(a, minOverlap);
      v.push_back(c);
      return *c;
    }
    Iterator & no_nests(Iterator & a){
      NoNests * nn = new NoNests(a);
      v.push_back(nn);
      return *nn;
    }
    
    ~Chain(){
      for(size_t i = 0; i < v.size(); i++){
	printf("deleting %zu\n", i);
	delete v.at(i);
      }
    }
    
  private:
    std::vector<Iterator *> v;
  };

}

#endif
