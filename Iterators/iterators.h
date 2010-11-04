/*
 * Copyright 2010 Justin T. Brown
 * All Rights Reserved
 * EMAIL: run.intervals@gmail.com
 *
 * This file is part of Rivals.
 *
 * Rivals is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rivals is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Rivals.  If not, see <http://www.gnu.org/licenses/>.
 */

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
#include "contained_in.h"
#include "contains.h"
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
#ifdef DEBUG
      printf("Creating NODE %zu\n", (size_t)this);
#endif
    }
    
  Node(Iterator * i, std::auto_ptr<Node> n)
    : iter(i), left_child(n), right_child(0) {
#ifdef DEBUG
      printf("Creating NODE %zu\n", (size_t)this);
#endif
      n.reset(0);
    }
    
  Node(Iterator * i, std::auto_ptr<Node> n, std::auto_ptr<Node> m)
    : iter(i), left_child(n), right_child(m){
#ifdef DEBUG
      printf("Creating NODE %zu\n", (size_t)this);
#endif
      n.reset(0);
      m.reset(0);
    }
    
    ~Node(){
#ifdef DEBUG
      printf("Deleting NODE %zu\n", (size_t)this);
#endif
    }

    std::auto_ptr<Iterator> iter;

  private:
    std::auto_ptr<Node> left_child;
    std::auto_ptr<Node> right_child;
  };

  std::auto_ptr<Node> interval(std::string chr, Domain start, Domain stop);
  std::auto_ptr<Node> range(std::string sample);
  std::auto_ptr<Node> range(std::string sample, std::string chrom);
  std::auto_ptr<Node> range(std::string sample, std::string chrom, Domain start, Domain stop);
  std::auto_ptr<Node> range(std::string sample, std::string chrom, Domain point);
 
  std::auto_ptr<Node> merge(std::auto_ptr<Node> a, std::auto_ptr<Node> b);
  
  std::auto_ptr<Node> flatten(std::auto_ptr<Node> a);
  std::auto_ptr<Node> clique(std::auto_ptr<Node> a, Capacity minOverlap);
    
  std::auto_ptr<Node> contained_in(std::auto_ptr<Node> a, std::auto_ptr<Node> b);
  std::auto_ptr<Node> contains(std::auto_ptr<Node> a, std::auto_ptr<Node> b);
  std::auto_ptr<Node> overlaps(std::auto_ptr<Node> a, std::auto_ptr<Node> b);
    
  std::auto_ptr<Node> get_strand(std::auto_ptr<Node> a, int str);
  std::auto_ptr<Node> set_strand(std::auto_ptr<Node> a, int str);

  std::string saveAsBED(std::string filename, std::auto_ptr<Node> a);
  std::string saveAsBED(std::auto_ptr<Node> a);
  std::string saveAsRival(std::string base, std::auto_ptr<Node> a);

  Capacity countIntervals(std::auto_ptr<Node> a);
}

#endif
