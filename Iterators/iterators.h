#ifndef ITERS_H_
#define ITERS_H_

#include <list>
#include <memory>
#include <exception>

#include "iterator.h"
#include "sample.h"
#include "range.h"
#include "merge.h"
#include "flatten.h"
#include "clique.h"
#include "no_nests.h"
#include "contained_in.h"
#include "interval_iter.h"
#include "strand.h"
#include "overlaps.h"

namespace rivals {

  class no_own : public std::exception
    {
    public:
      virtual const char* what() const throw();
    };

  class Node {
  public:
  Node(Iterator * i) 
    : iter(i), left_child(0), right_child(0) {
      printf("Creating NODE %zu\n", (size_t)this);
    }
    
  Node(Iterator * i, std::auto_ptr<Node> n)
    : iter(i), left_child(n), right_child(0) {
      printf("Creating NODE %zu\n", (size_t)this);
      n.reset(0);
    }
    
  Node(Iterator * i, std::auto_ptr<Node> n, std::auto_ptr<Node> m)
    : iter(i), left_child(n), right_child(m){
      printf("Creating NODE %zu\n", (size_t)this);
      n.reset(0);
      m.reset(0);
    }
    
    ~Node(){
      printf("Deleting NODE %zu\n", (size_t)this);
    }

    void saveAsBED() {
      return iter->saveAsBED();
    }

    std::auto_ptr<Iterator> iter;

  private:
    std::auto_ptr<Node> left_child;
    std::auto_ptr<Node> right_child;
  };

  std::auto_ptr<Node> range(std::string sample);
  std::auto_ptr<Node> range(std::string sample, std::string chrom);
  std::auto_ptr<Node> range(std::string sample, std::string chrom, Domain start, Domain stop);
  std::auto_ptr<Node> range(std::string sample, std::string chrom, Domain point);
  std::auto_ptr<Node> merge(std::auto_ptr<Node> a, std::auto_ptr<Node> b);
  std::auto_ptr<Node> flatten(std::auto_ptr<Node> a);
  std::auto_ptr<Node> clique(std::auto_ptr<Node> a, Capacity minOverlap);
  std::auto_ptr<Node> no_nests(std::auto_ptr<Node> a);
  std::auto_ptr<Node> contained_in(std::auto_ptr<Node> a, std::auto_ptr<Node> b);
  std::auto_ptr<Node> overlaps(std::auto_ptr<Node> a, std::auto_ptr<Node> b);
  std::auto_ptr<Node> interval(std::string chr, Domain start, Domain stop);
  std::auto_ptr<Node> get_strand(std::auto_ptr<Node> a, int str);
  std::auto_ptr<Node> set_strand(std::auto_ptr<Node> a, int str);
  
}

#endif
