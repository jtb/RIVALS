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

#include "typedef.h"
#include "interval.h"
#include "utils.h"
#include "tabdelim.h"

using namespace std;

namespace rivals {
  TabDelim::TabDelim(string filename) : file_in(filename.c_str()) {
    if(!file_in.is_open()){
      printf("Could not open tab delimited file %s for reading.\n", filename.c_str());
    }
  }

  TabDelim::~TabDelim(){
    file_in.close();
  }
  
  bool TabDelim::next(string & chr, Interval & c){
    if(!file_in.is_open()) return false;
    while(!file_in.eof()){
      getline(file_in, line);
      if(!checkLine(line)) continue;
      
      vector<string> fields;
      Tokenize(line, fields, " \t");

      if(fields.size() < 3) continue;
      if(!checkChr(fields.at(0))) continue;
      if(!checkPos(fields.at(1))) continue;
      if(!checkPos(fields.at(2))) continue;

      chr = fields.at(0);// field 0
      Domain start;// field 1
      Domain stop;// field 2
      
      istringstream s_start(fields.at(1));
      istringstream s_stop(fields.at(2));
      s_start >> start;
      s_stop >> stop;
      
      int str = BOTH;//either strand
      if(fields.size() >= 4){
	string strand = fields.at(3);// field 4                                                 
	if(strand == "-" || strand == "1"){
	  str = MINUS;
	}
	if(strand == "+" || strand == "0"){
	  str = PLUS;
	}
      }
      c.setInterval(start, stop, str);
      return true;
    }
    
    return false;
  }
  
}
