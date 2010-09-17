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

#ifndef INTERVAL_ITER_H_
#define INTERVAL_ITER_H_

#include "iterator.h"

namespace rivals {

  class IntervalIter : public Iterator {
  public:
    IntervalIter(std::string chr, Domain start, Domain stop);
    ~IntervalIter(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);

  private:
    std::string chromosome;
    Interval head;
    bool done;
  };

}

#endif
