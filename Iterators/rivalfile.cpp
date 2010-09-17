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

#include <sstream>
#include <vector>
#include <iostream>
#include "rivalfile.h"

using namespace std;

namespace rivals {
  RivalFile::RivalFile(Iterator & i) : iter(i) {
    it = iter.getChrList().begin();
    if(it != iter.getChrList().end()){
      iter.setChr(*it);
    }
  }

  RivalFile::~RivalFile(){
  }
  
  bool RivalFile::next(string & chr, Interval & c){
    while(it != iter.getChrList().end()){
      if(iter.next(chr, c)) return true;
      ++it;
      if(it != iter.getChrList().end()) iter.setChr(*it);
      
    }
    return false;
  }
  
}
