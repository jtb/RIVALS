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

#ifndef CLIQUE_H_
#define CLIQUE_H_

#include <string>
#include <queue>
#include "iterator.h"

namespace rivals {

  class Clique : public Iterator {
  public:
    Clique(Iterator & a, Capacity minOverlap);
    ~Clique(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    const ChromList & getChrList();

  private:
    void start_pop(std::string & chrom, Interval & intv){
      start_full = false;
      if(iter.next(chrom, intv)){
	start_full = true;
	start = intv.getStart();
	endpoints.push(intv.getStop());
      }
    }
    bool start_empty(){ return !start_full; }
   
    Capacity min_overlap;
    Iterator & iter;

    bool in_interval;
    int count;
   
    Capacity start;
    bool start_full;
   
    std::priority_queue<Capacity, std::vector<Capacity>, std::greater<Capacity> > endpoints;

  };

}

#endif
