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

#ifndef TAB_DELIM_H_
#define TAB_DELIM_H_

#include <fstream>
#include <string>
#include <map>

#include "genomefile.h"

namespace rivals {
  class Interval;

  class TabDelim : public GenomeFile {
  public:
    TabDelim(std::string filename);
    ~TabDelim();

    bool next(std::string & chr, Interval & c);

  private:
    std::ifstream file_in;
    std::string line;
  };

}

#endif
