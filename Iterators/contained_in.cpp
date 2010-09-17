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

#include "contained_in.h"

using namespace std;

namespace rivals {

  ContainedIn::ContainedIn(Iterator & a, Iterator & b) : Iterator(), iterA(a), iterB(b) {
    mergeChromLists(iterA.getChrList(), iterB.getChrList());
  }

  void ContainedIn::setChr(std::string chrom){
    iterA.setChr(chrom);
    iterB.setChr(chrom);
    avalid = iterA.next(chromA, a);
    bvalid = iterB.next(chromB, b);
    endpoint = b.getStop();
  }

  bool ContainedIn::next(string & chrom, Interval & intv){
    while(avalid && bvalid){
      assert(chromA == chromB);
      if(a.getStart() < b.getStart()){
	avalid = iterA.next(chromA, a);
      }else{//b.start <= a.start
	if(b.getStop() > endpoint){
	  endpoint = b.getStop();
	}
	if(a.getStop() <= endpoint){
	  intv = a;
	  chrom = chromA;
	  avalid = iterA.next(chromA, a);
	  return true;
	}else{
	  bvalid = iterB.next(chromB, b);
	}
      }
    }
    return false;
  }

}
