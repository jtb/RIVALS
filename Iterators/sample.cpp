#include "file_utils.h"
#include "sample.h"

using namespace std;
namespace rivals {
  Sample::Sample(string sample) : Iterator(), samp_name(sample), chr(""), on_chromosome(false), index(0), offset(0), fvector(fileFromSample(sample)) {
    readChrMap(samp_name, chrmap);
    //set chrlist;
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      chr_list.insert(it->first);
    }

    string version;
    Capacity num_elements;
    readHeader(samp_name, version, offset, num_elements);
  }

  Sample::Sample(string sample, string chrom) : Iterator(), samp_name(sample), chr(chrom), on_chromosome(false), index(0), offset(0), fvector(fileFromSample(sample)) {
    readChrMap(samp_name, chrmap, chrom);
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      chr_list.insert(it->first);
    }

    string version;
    Capacity num_elements;
    readHeader(samp_name, version, offset, num_elements);

    setChr(chrom);
  }

  bool Sample::next(string & chrom, Interval & intv){
    if(!on_chromosome) return false;
    chrom = chr;
    if(index < fvector.size()){
      intv = fvector.at(index);
      ++index;
      return true;
    }
    return false;
  }
 
  void Sample::setChr(string chrom){
    //get offset, get actual start and stop from chrmap
    Capacity start;
    Capacity stop;
    if(getRanges(chrom, chrmap, start, stop)){
      on_chromosome = true;
      chr = chrom;
      index = 0;
      fvector.setRange(offset, start, stop);
    }else{
      on_chromosome = false;
    }
  }
}
