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

#include "no_nests.h"

using namespace std;

namespace rivals {
  
  NoNests::NoNests(Iterator & a) : Iterator(), iter(a) {
    empty = true;
    isFirst = false;
  }

  const ChromList & NoNests::getChrList(){
    return iter.getChrList();
  }

  void NoNests::setChr(std::string chrom){
    iter.setChr(chrom);
    empty = true;
    isFirst = true;
    if(iter.next(chrom, head)){
      empty = false;
    }
  }

  bool NoNests::next(string & chrom, Interval & intv){
    Interval b;
    while(!isEmpty()){
      if(isFirst || head.getStop() > endpoint){
	pop(chrom, intv);
	while(!isEmpty()){
	  if(head.getStart() == intv.getStart()){
	    pop(chrom, intv);
	  }else{
	    break;
	  }
	}
	isFirst = false;
	endpoint = intv.getStop();
	return true;
      }else{
	pop(chrom, intv);
      }
    }
    return false;
  }

}
