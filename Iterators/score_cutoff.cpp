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

#include "score_cutoff.h"

using namespace std;

namespace rivals {

  ScoreCutoff::ScoreCutoff(Iterator & a, int thresh) : Iterator(), iter(a), cutoff(thresh) {
    has_score = a.has_score;
  }
  
  const ChromList & ScoreCutoff::getChrList(){ return iter.getChrList(); }

  void ScoreCutoff::setChr(std::string chrom){ iter.setChr(chrom); }

  bool ScoreCutoff::next(std::string & chrom, Interval & intv){
    while(iter.next(chrom, intv)){
      if(!iter.has_score){
	return true;
      }
      if(iter.score >= cutoff){
	score = iter.score;
      	return true;
      }
    }
    return false;
  }
  
}
