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

#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "typedef.h"

namespace rivals {

  class Interval {
  public:
    Interval(Domain start, Domain stop, int str);
    Interval();

    int getStrand() const;
    Domain getStart() const;
    Domain getStop() const;
    Domain getSubMax() const;

    void setInterval(Domain start, Domain stop, int str);
    void setStrand(int s);
    void setStart(Domain start);
    void setStop(Domain stop);
     
    void setSubMax(Domain max);

    Length getLength() const;

    bool inRange(Domain start, Domain stop);

    bool overlaps(const Interval & b, bool strand_specific = false);
      
    bool operator<(const Interval & b) const;

    void printInterval() const;

  private:
    Domain submax; // 4 bytes
    Domain left; //   4 bytes
    Domain right; //  4 bytes
    // total bytes = 12 bytes
  };

  class cInterval {
  public:
  cInterval(Domain start, Domain stop, int str) : intv(start, stop, str) {}
  cInterval() : intv() {}

    bool operator<(const cInterval & b) const {
      if(intv.getSubMax() == b.intv.getSubMax()){
	return intv < b.intv;
      }
      return intv.getSubMax() < b.intv.getSubMax();
    }

  private:
    Interval intv;
  };
  
}//namespace rivals

#endif
