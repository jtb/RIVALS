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

#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <string>
#include <map>

#include "iterator.h"
#include "typedef.h"
#include "cache.h"

namespace rivals {

  class Sample : public Iterator {
  public:
    Sample(std::string sample);
    Sample(std::string sample, std::string chrom);
    ~Sample(){}

    bool next(std::string & chrom, Interval & intv);
    void setChr(std::string chrom);
    
  private:
    std::string samp_name;
    std::string chr;
    bool on_chromosome;
    Capacity index;
    off_t offset;
    ForwardCache<Interval> fvector;
    std::map<std::string, std::pair<Capacity, Capacity> > chrmap;
  };
}

#endif
