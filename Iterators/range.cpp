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

#include "file_utils.h"
#include "range.h"

using namespace std;
namespace rivals {

  Range::Range(string sample, string chrom, Domain start, Domain stop) : Iterator(), samp_name(sample), chr(chrom), on_chromosome(false), d(start, stop, BOTH), offset(0), cvector(fileFromSample(sample)) {
    readChrMap(samp_name, chrmap, chrom);
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      chr_list.insert(it->first);
    }
    
    string version;
    Capacity num_elements;
    readHeader(samp_name, version, offset, num_elements);

    setChr(chrom);
  }

  Range::Range(string sample, string chrom, Domain point) : Iterator(), samp_name(sample), chr(chrom), on_chromosome(false), d(point, point+1, BOTH), offset(0), cvector(fileFromSample(sample)) {
    readChrMap(samp_name, chrmap, chrom);
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      chr_list.insert(it->first);
    }
    
    string version;
    Capacity num_elements;
    readHeader(samp_name, version, offset, num_elements);

    setChr(chrom);
  }
  
  bool Range::next(string & chrom, Interval & intv){
    if(!on_chromosome) return false;
    chrom = chr;
    
    while(!recurse.empty()){
      Cargo c = recurse.top();
      Interval i = cvector.at(c.root);
      if(d.getStart() >= i.getSubMax()){
	recurse.pop();
      }else{
	if(!c.goLeft){
	  //check this one, pop, then put right on top if it exists and start is less than i stop
	  recurse.pop();
	  if(d.getStop() > i.getStart()){
	    Capacity root;
	    if(getMidpoint(c.root+1, c.high, root)){
	      recurse.push(Cargo(c.root+1, c.high, root));
	    }
	  
	    if(i.overlaps(d)){
	      intv = i;
	      return true;
	    }
	  }//else this node and right children do not overlap d
	}else{
	  recurse.top().goLeft = false;
	  //go left
	  Capacity root;
	  if(getMidpoint(c.low, c.root, root)){
	    recurse.push(Cargo(c.low, c.root, root));
	  }
	}
      }
    }
    return false;
  }

  void Range::setChr(string chrom){
    recurse = stack<Cargo>();
    Capacity start;
    Capacity stop;
    if(getRanges(chrom, chrmap, start, stop)){
      on_chromosome = true;
      chr = chrom;
      cvector.setRange(offset, start, stop);
      Capacity root;
      if(getMidpoint(0, cvector.size(), root)){
	recurse.push(Cargo(0, cvector.size(), root));
      }
    }else{
      on_chromosome = false;
    }
  }

}
