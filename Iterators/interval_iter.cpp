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

#include "interval_iter.h"

using namespace std;

namespace rivals {

  IntervalIter::IntervalIter(string chr, Domain start, Domain stop) : Iterator(), chromosome(chr), head(start, stop, BOTH), done(true) {
    chr_list.insert(chromosome);
  }

  void IntervalIter::setChr(std::string chrom){
    done = true;
    if(!chrom.compare(chromosome)) done = false;
  }

  bool IntervalIter::next(std::string & chrom, Interval & intv){
    if(!done){
      done = true;
      chrom = chromosome;
      intv = head;
      return true;
    }
    return false;
  }

}
