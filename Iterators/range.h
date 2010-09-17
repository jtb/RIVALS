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

#ifndef RANGE_H_
#define RANGE_H_

#include <string>
#include <set>
#include <map>
#include <stack>

#include "iterator.h"
#include "typedef.h"
#include "cache.h"

namespace rivals {

  class Range : public Iterator {
  public:
    Range(std::string sample, std::string chrom, Domain start, Domain stop);
    Range(std::string sample, std::string chrom, Domain point);
    ~Range(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    	    
  private:

    std::string samp_name;
    std::string chr;
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
