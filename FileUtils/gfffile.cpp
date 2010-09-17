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
#include "gfffile.h"

using namespace std;

namespace rivals {
  GFFfile::GFFfile(string filename) : file_in(filename.c_str()) {
    if(!file_in.is_open()){
      printf("Could not open gff file %s for reading.\n", filename.c_str());
    }
  }

  GFFfile::~GFFfile(){
    file_in.close();
  }
  
  bool GFFfile::next(string & chr, Interval & c){
    if(!file_in.is_open()) return false;
    while(!file_in.eof()){
      getline(file_in, line);
      if(line == "") continue;
      
      vector<string> fields;
      Tokenize(line, fields, " \t");
      assert(fields.size() >= 9);
      chr = fields.at(0);// field 0
      Domain start;// field 3
      Domain stop;// field 4
      
      istringstream s_start(fields.at(3));
      istringstream s_stop(fields.at(4));
      s_start >> start;
      s_stop >> stop;
      
      int str = BOTH;//either strand
      string strand = fields.at(6);// field 6
      if(strand == "-" || strand == "1"){
	  str = MINUS;
	}
	if(strand == "+" || strand == "0"){
	  str = PLUS;
	}
            
      c.setInterval(start, stop, str);
      return true;
    }

    return false;
  }
  
}
