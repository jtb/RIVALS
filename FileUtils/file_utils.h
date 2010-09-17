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

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <string>
#include <map>

#include "typedef.h"

namespace rivals {
  class GenomeFile;

  bool getMidpoint(Capacity low, Capacity high, Capacity & mp);

  void writeChrMap(const std::map<std::string, std::pair<Capacity, Capacity> > & chrmap, std::string sample);
  void readChrMap(std::string sample, std::map<std::string, std::pair<Capacity, Capacity> > & chrmap, std::string chrom = ""); 

  bool readHeader(std::string sample, std::string & version, off_t & offset, Capacity & num_elements);

  void importData(GenomeFile & gf, std::string sample);

  bool rivalWriter(GenomeFile & gf, std::string sample);
  void indexNodes(std::string sample);

  std::string fileFromSample(std::string sample);
  std::string chrFromSample(std::string sample);

  bool getRanges(std::string chr, const std::map<std::string, std::pair<Capacity, Capacity> > & chrmap, Capacity & start, Capacity & stop);
  
}

#endif
