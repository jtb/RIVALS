#include <fstream>
#include <iostream>

#include "bedfile.h"
#include "file_utils.h"
#include "interval.h"

using namespace std;

namespace rivals {
  void writeChrMap(const map<string, pair<Capacity, Capacity> > & chrmap, string filename){
    ofstream file_out (filename.c_str());
    if (file_out.is_open())
      {
        map<string, pair<Capacity, Capacity> >::const_iterator it;
        for(it = chrmap.begin(); it != chrmap.end(); ++it){
          file_out << it->first << "\t" << it->second.first << "\t" << it->second.second << endl;
        }
        file_out.close();
      }
    else{
      printf("Unable to open Chromosome Map file %s for writing\n", filename.c_str());
    }
  }

  string fileFromSample(string sample) { return sample + ".riv"; }
  string chrFromSample(string sample) { return sample + ".map"; }

  void rivalWriter(BEDfile & bed, string sample){
    
    map<string, pair<Capacity, Capacity> > chrmap;
    Capacity bed_size = 0;
    string curr_chr = "";
    Capacity curr_chr_start = 0;
    
    fstream file;
    file.open(fileFromSample(sample).c_str(), ios::out | ios::binary | ios::trunc);
    if(file.is_open()){
      //writeHeader
      char version[8] = {'R','I','V','A','L','0','0','1'};
      file.seekg(0, ios::beg);
      file.write(version, 8);

      uint32_t offset = 8 + sizeof(uint32_t) + sizeof(Capacity);
      printf("offset is %u\n", offset);
      file.write((char *)&offset, sizeof(uint32_t));
      file.write((char *)&bed_size, sizeof(Capacity));

      Interval arr[CACHE];
      string chr;
      Interval c;

      int count;
      do {
	for(count = 0; count < CACHE; count++){
	  if(!bed.next(chr, c)) break;
	  arr[count] = c;

	  if(chr.compare(curr_chr)){//curr_chr != chr
	    if(curr_chr.compare("")){//curr_chr != ""
	      pair<Capacity, Capacity> temp(curr_chr_start, bed_size);
	      chrmap.insert(pair<string, pair<Capacity, Capacity> >(curr_chr, temp));
	    }
	    curr_chr = chr;
	    curr_chr_start = bed_size;
	  }
	  bed_size++;
	}
	if(count){
          file.write((char *)&arr, count*sizeof(Interval));
        }
      }while(count == CACHE);
   
      if(curr_chr.compare("")){
	pair<Capacity, Capacity> temp(curr_chr_start, bed_size);
	chrmap.insert(pair<string, pair<Capacity, Capacity> >(curr_chr, temp));
      }

      file.seekg(8 + sizeof(uint32_t), ios::beg);
      if(!file) printf("ERRRRROR\n");
      cout <<"bed size is " << bed_size << endl;
      file.write((char *)&bed_size, sizeof(Capacity));

      writeChrMap(chrmap, chrFromSample(sample));
    }else{
      printf("Could not open %s for writing\n", fileFromSample(sample).c_str());
    }

    file.close();
  }

}
