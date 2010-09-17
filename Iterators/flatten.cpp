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

#include "flatten.h"

using namespace std;
namespace rivals {
  Flatten::Flatten(Iterator & a) : Iterator(), iter(a), count(0), clean_up(true) {
    has_score = true;
  }

  const ChromList & Flatten::getChrList(){
    return iter.getChrList();
  }

  void Flatten::setChr(std::string chrom){
    iter.setChr(chrom);
    count = 0;
    clean_up = false;
    if(iter.next(chrom, head)){
      count = 1;
      clean_up = true;
    }
  }

  bool Flatten::next(std::string & chrom, Interval & intv){
    Interval b;
    while(iter.next(chrom, b)){
      if(b.getStart() <= head.getStop()){
	if(b.getStop() > head.getStop()) head.setStop(b.getStop());
	count++;
      }else{
	intv = head;
	intv.setStrand(BOTH);
	head = b;
	score = count;
	count = 1;
	return true;
      }
    }

    if(clean_up){
      intv = head;
      intv.setStrand(BOTH);
      score = count;
      clean_up = false;
      return true;
    }
    return false;
  }
}
