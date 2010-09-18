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

#include "nested.h"

using namespace std;

namespace rivals {
  
  Nested::Nested(Iterator & a) : Iterator(), iter(a) {
  }

  const ChromList & Nested::getChrList(){
    return iter.getChrList();
  }

  void Nested::setChr(std::string chrom){
    iter.setChr(chrom);
    list.clear();
    valid = iter.next(chr, top);
  }

  bool Nested::next(string & chrom, Interval & intv){
    while(valid || !list.empty()){
      if(!valid){//list is not empty
	chrom = chr;
	intv = list.back();
	list.pop_back();
	return true;
      }
      
      //If it made it here, top is valid
      if(!list.empty() && list.back().getStop() <= top.getStart()){
	chrom = chr;
	intv = list.back();
	list.pop_back();
	return true;
      }
      
      while(!list.empty() && list.front().getStop() >= top.getStop()){
	list.pop_front();
      }
      
      if(list.empty() || list.front().getStart() < top.getStart()){
	list.push_front(top);
      }
      valid = iter.next(chr, top);
    }
    return false;
  }

}
