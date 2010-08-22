#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <string>
#include <map>

#include "typedef.h"

namespace rivals {
  class BEDfile;

  void writeChrMap(const std::map<std::string, std::pair<Capacity, Capacity> > & chrmap, std::string sample);
  void readChrMap(std::string sample, std::map<std::string, std::pair<Capacity, Capacity> > & chrmap, std::string chrom = ""); 

  bool readHeader(std::string sample, std::string & version, off_t & offset, Capacity & num_elements);

  void rivalWriter(BEDfile & bed, std::string sample);
  void indexNodes(std::string sample);

  std::string fileFromSample(std::string sample);
  std::string chrFromSample(std::string sample);

  bool getRanges(std::string chr, const std::map<std::string, std::pair<Capacity, Capacity> > & chrmap, Capacity & start, Capacity & stop);
  
}

#endif
