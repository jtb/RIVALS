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

#include "utils.h"

using namespace std;

namespace rivals {

  void Tokenize(const string & str, vector<string> & tokens, const string & delimiters){
    string::size_type firstPos = 0;
    string::size_type lastPos = str.find_first_of(delimiters, firstPos);
    while(string::npos != lastPos){
      tokens.push_back(str.substr(firstPos, lastPos - firstPos));
      firstPos = lastPos + 1;
      lastPos = str.find_first_of(delimiters, firstPos);
    }
    tokens.push_back(str.substr(firstPos, lastPos - firstPos));
  }

}
