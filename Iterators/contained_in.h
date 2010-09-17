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

#ifndef CONTAINED_IN_H_
#define CONTAINED_IN_H_

#include "iterator.h"

namespace rivals {

  class ContainedIn : public Iterator {
  public:
    ContainedIn(Iterator & a, Iterator & b);
    ~ContainedIn(){}
    
    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    
  private:
    Iterator & iterA;
    Iterator & iterB;
    Interval a;
    Interval b;
    bool avalid;
    bool bvalid;
    std::string chromA;
    std::string chromB;
    Domain endpoint;
  };

}

#endif
