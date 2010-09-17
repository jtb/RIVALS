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

#include "merge.h"

using namespace std;
namespace rivals {
  Merge::Merge(Iterator & a, Iterator & b) : Iterator(), itA(a), itB(b) {
    mergeChromLists(a.getChrList(), b.getChrList());
  }


  void Merge::setChr(std::string chrom){
    itA.setChr(chrom);
    itB.setChr(chrom);
    avalid = itA.next(chromA, a);
    bvalid = itB.next(chromB, b);
  }

  bool Merge::next(std::string & chrom, Interval & intv){
    if(!avalid && !bvalid) return false;
    
    if(avalid && !bvalid){
      intv = a;
      chrom = chromA;
      avalid = itA.next(chromA, a);
      return true;
    }
    if(!avalid && bvalid){
      intv = b;
      chrom = chromB;
      bvalid = itB.next(chromB, b);
      return true;
    }
    //avalid && bvalid
    assert(chromA == chromB);
    if(a < b){
      intv = a;
      chrom = chromA;
      avalid = itA.next(chromA, a);
    }else{
      intv = b;
      chrom = chromB;
      bvalid = itB.next(chromB, b);
    }
    return true;
  }

}
