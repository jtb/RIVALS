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

#include "clique.h"

using namespace std;
namespace rivals {
  Clique::Clique(Iterator & a, Capacity minOverlap) : Iterator(), min_overlap(minOverlap), iter(a), in_interval(false), count(0), start(0), start_full(false) {
    has_score = true;
  }

  const ChromList & Clique::getChrList(){
    return iter.getChrList();
  }

  void Clique::setChr(std::string chrom){
    while(!endpoints.empty()){
      endpoints.pop();
    }
    iter.setChr(chrom);
    Interval b;
    count = 0;
    start_pop(chrom, b);
  }

  bool Clique::next(std::string & chrom, Interval & intv){
    score = 0;
    in_interval = false;
    Interval b;
    while(!start_empty() || in_interval){
      //start
      Capacity end = endpoints.top();
      if(start_empty() || end <= start){
	assert(count > 0);
	endpoints.pop();
	count--;
	if(count < min_overlap && in_interval){
	  intv.setStop(end);
	  intv.setStrand(BOTH);
	  return true;
	}
      }else{//start < end
	count++;
	if(count >= min_overlap){
	  if(!in_interval){
	    in_interval = true;
	    score = count;
	    intv.setStart(start);
	  }else{
	    if(count > score) score = count;
	  }
	}
	start_pop(chrom, b);
      }
    }
    return false;
  }
  
}
