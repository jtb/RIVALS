#include <fstream>
#include <sstream>
#include <iostream>

#include "bedfile.h"
#include "file_utils.h"
#include "utils.h"
#include "interval.h"
#include "cache.h"

using namespace std;

namespace rivals {
  bool getRanges(string chr, const map<string, pair<Capacity, Capacity> > & chrmap, Capacity & start, Capacity & stop){
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    it = chrmap.find(chr);
    if(it == chrmap.end()){
      return false;
    }
    start = it->second.first;
    stop = it->second.second;
    return true;
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

  void readChrMap(string sample, map<string, pair<Capacity, Capacity> > & chrmap, string chrom){
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
	if(chrom == ""){
	  chrmap.insert(pair<string, pair<Capacity, Capacity> >(chr, temp));
	}else{
	  if(chrom == chr){
	    chrmap.insert(pair<string, pair<Capacity, Capacity> >(chr, temp));
	  }
	}
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

  bool getMidpoint(Capacity low, Capacity high, Capacity & mp){
    mp = (high-low)/2 + low;
    return (low < high);
  }
  
  namespace {
    bool indexNodesHelper(CenteredCache<Interval> & cc, Capacity low, Capacity high, Domain & value){
      Capacity root;
      if(getMidpoint(low, high, root)){
	Domain left, right;
	bool has_left = indexNodesHelper(cc, low, root, left);
	bool has_right = indexNodesHelper(cc, root+1, high, right);

	Interval i = cc.at(root);
	value = i.getStop();
	if(has_left) value = max(value, left);
	if(has_right) value = max(value, right);
	i.setSubMax(value);
	cc.set(root, i);
	return true;
      }
      return false;
    }
    
  }

  void indexNodes(string sample){
    
    map<string, pair<Capacity, Capacity> > chrmap;
    readChrMap(sample, chrmap);
    string version;
    off_t offset;
    Capacity num_elements;
    readHeader(sample, version, offset, num_elements);

    CenteredCache<Interval> cvector(fileFromSample(sample), false);
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    Capacity start;
    Capacity stop;
    string chr;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      Domain value = 0;
      chr = it->first;
      getRanges(chr, chrmap, start, stop);
      cvector.setRange(offset, start, stop);
      indexNodesHelper(cvector, 0, stop-start, value);
    }
  }

  void importData(BEDfile & bed, string sample){
    rivalWriter(bed, sample);
    indexNodes(sample);
  }

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
      Interval prev;

      int count;
      do {
	for(count = 0; count < CACHE; count++){
	  if(!bed.next(chr, c)) break;
	  arr[count] = c;

	  if(chr.compare(curr_chr)){//curr_chr != chr
	    if(curr_chr.compare("")){//curr_chr != ""
	      pair<Capacity, Capacity> temp(curr_chr_start, bed_size);
	      //make sure chromosome does not already exist
	      assert(chrmap.find(curr_chr) == chrmap.end());
	      chrmap.insert(pair<string, pair<Capacity, Capacity> >(curr_chr, temp));
	    }
	    curr_chr = chr;
	    curr_chr_start = bed_size;
	  }else{
	    //check if old interval is less than new interval
	    assert(prev < c || !(c < prev));
	  }
	  bed_size++;
	  prev = c;
	}
	if(count){
          file.write((char *)&arr, count*sizeof(Interval));
        }
      }while(count == CACHE);
   
      if(curr_chr.compare("")){
	pair<Capacity, Capacity> temp(curr_chr_start, bed_size);
	//Make sure that chromosome does not already exist
	assert(chrmap.find(curr_chr) == chrmap.end());
	chrmap.insert(pair<string, pair<Capacity, Capacity> >(curr_chr, temp));
      }

      file.seekg(8 + sizeof(off_t), ios::beg);
      if(!file) printf("ERRRRROR\n");
      file.write((char *)&bed_size, sizeof(Capacity));

      writeChrMap(chrmap, sample);
      
    }else{
      printf("Could not open %s for writing\n", fileFromSample(sample).c_str());
    }

    file.close();
  }

}
