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

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <string>
#include <set>
#include "interval.h"

namespace rivals {
  typedef std::set<std::string> ChromList;

  class Iterator {
  public:
  Iterator() : has_score(false), score(0) {
      chr_list.clear();
    }
    virtual ~Iterator(){}

    virtual bool next(std::string & chrom, Interval & intv) = 0;
    virtual void setChr(std::string chrom) = 0;
    
    virtual const ChromList & getChrList(){
      return chr_list;
    }
    
    bool has_score;
    int score;
    
  protected:
    virtual void mergeChromLists(const ChromList & clist1, const ChromList & clist2){
      chr_list.clear();
      ChromList::const_iterator it;
      for(it = clist1.begin(); it != clist1.end(); ++it){
	chr_list.insert(*it);
      }
      for(it = clist2.begin(); it != clist2.end(); ++it){
	chr_list.insert(*it);
      }
    }
    
    ChromList chr_list;
  };
  
}

#endif
