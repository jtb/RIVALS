#include <fstream>
#include <sstream>
#include <iostream>

#include "bedfile.h"
#include "file_utils.h"
#include "utils.h"
#include "interval.h"

using namespace std;

namespace rivals {
  void getRanges(string chr, const map<string, pair<Capacity, Capacity> > & chrmap, Capacity & start, Capacity & stop){
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    it = chrmap.find(chr);
    if(it == chrmap.end()){
      printf("Chromosome not in map!\n");
    }
    start = it->second.first;
    stop = it->second.second;
  }

  void writeChrMap(const map<string, pair<Capacity, Capacity> > & chrmap, string sample){
    string filename = chrFromSample(sample);
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

  void readChrMap(string sample, map<string, pair<Capacity, Capacity> > & chrmap){
    string filename = chrFromSample(sample);
    chrmap.clear();
    ifstream file_in(filename.c_str());
    string line;
    
    if(file_in.is_open()){
      while(!file_in.eof()){
        getline(file_in, line);
        if(line == "") continue;
        vector<string> fields;
        Tokenize(line, fields, " \t");
        assert(fields.size() == 3);
        string chr = fields.at(0);
	
	Capacity start;
	Capacity stop;
	istringstream s_start(fields.at(1));
        s_start >> start;
	istringstream s_stop(fields.at(2));
        s_stop >> stop;

	pair<Capacity, Capacity> temp(start, stop);
	chrmap.insert(pair<string, pair<Capacity, Capacity> >(chr, temp));
      }
    }else{
      printf("Could not open %s\n", filename.c_str());
    }
    file_in.close();
  }

  bool readHeader(string sample, string & version, off_t & offset, Capacity & num_elements){
    version = "";
    offset = 0;
    num_elements = 0;
    string filename = fileFromSample(sample);
    fstream file;
    file.open(filename.c_str(), ios::in | ios::binary);
    if(!file){
      printf("Could not open %s for reading.\n", filename.c_str());
      return false;
    }
    char vers[8+1];
    file.seekg(0, ios::beg);
    file.read(vers, 8);
    vers[8] = 0;
    version = vers;
    if(version.compare("RIVAL001")){
      printf("Version numbers do not agree.\n");
      return false;
    }
    file.read((char *)&offset, sizeof(off_t));
    file.read((char *)&num_elements, sizeof(Capacity));
    
    file.close();
    return true;
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

      off_t offset = 8 + sizeof(off_t) + sizeof(Capacity);
      file.write((char *)&offset, sizeof(off_t));
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

      file.seekg(8 + sizeof(off_t), ios::beg);
      if(!file) printf("ERRRRROR\n");
      cout <<"bed size is " << bed_size << endl;
      file.write((char *)&bed_size, sizeof(Capacity));

      writeChrMap(chrmap, chrFromSample(sample));
      
      //chrmap.clear();
      //readChrMap(chrFromSample(sample), chrmap);
      //writeChrMap(chrmap, chrFromSample("blah"));
    }else{
      printf("Could not open %s for writing\n", fileFromSample(sample).c_str());
    }

    file.close();
  }

}
