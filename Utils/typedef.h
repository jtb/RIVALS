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

#ifndef TYPEDEF_H_
#define TYPEDEF_H_

#include <stdint.h>
#include <assert.h>

namespace rivals {

  //typedef int32_t Domain;
  typedef uint32_t Domain;
  typedef uint32_t Length;
  typedef uint64_t Capacity;

  enum Strand { PLUS, MINUS, BOTH};

#define CACHE 1024
  //#define MEMORY 1024*1024*8
#define MEMORY 1024

}

#endif
