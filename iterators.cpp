#include "interval.h"
#include "file_utils.h"
#include "iterators.h"

using namespace std;
namespace rivals {

  //void saveAsBED(Iterator & iter);
  Sample::Sample(std::string sample) : Iterator(), samp_name(sample), index(0), offset(0), fvector(fileFromSample(sample)) {
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

  bool Sample::next(std::string & chrom, Interval & intv){
    chrom = chr;
    if(index < fvector.size()){
      intv = fvector.at(index);
      ++index;
      return true;
    }
    return false;
  }

  void Sample::setChr(std::string chrom){
    chr = chrom;
    index = 0;
    //get offset, get actual start and stop from chrmap
    Capacity start;
    Capacity stop;
    getRanges(chr, chrmap, start, stop);
    fvector.setRange(offset, start, stop);
  }

}
