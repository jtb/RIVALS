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

#include <sys/stat.h>

#include "bedfile.h"
#include "gfffile.h"
#include "rivals.h"

namespace rivals {
    
  void importBED(std::string source, std::string outbase, bool overwrite){
    struct stat riv;
    struct stat map;
    //if overwrite is true OR one of the two rival files (.map and .riv) does not exist, then create new sample
    if(overwrite || stat(fileFromSample(outbase).c_str(),&riv) || stat(chrFromSample(outbase).c_str(),&map)){
      BEDfile bed(source);
      importData(bed, outbase);
    }
  }

  void importGFF(std::string source, std::string outbase, bool overwrite){
    struct stat riv;
    struct stat map;
    //if overwrite is true OR one of the two rival files (.map and .riv) does not exist, then create new sample
    if(overwrite || stat(fileFromSample(outbase).c_str(),&riv) || stat(chrFromSample(outbase).c_str(),&map)){
      GFFfile gff(source);
      importData(gff, outbase);
    }
  }
}
