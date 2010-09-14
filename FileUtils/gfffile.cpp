#include <sstream>
#include <vector>

#include "interval.h"
#include "utils.h"
#include "gfffile.h"

using namespace std;

namespace rivals {
  GFFfile::GFFfile(string filename) : count(0), file_in(filename.c_str()), curr_chr(""), curr_chr_start(0) {
    if(!file_in.is_open()){
      printf("Could not open gff file %s for reading.\n", filename.c_str());
    }
  }

  GFFfile::~GFFfile(){
    file_in.close();
  }

  const map<string, pair<Capacity, Capacity> > &  GFFfile::getChrMap() const {
    return chrmap;
  }
  
  bool GFFfile::next(string & chr, Interval & c){
    if(!file_in.is_open()) return false;
    while(!file_in.eof()){
      getline(file_in, line);
      if(line == "") continue;
      
      vector<string> fields;
      Tokenize(line, fields, " \t");
      assert(fields.size() >= 9);
      chr = fields.at(0);// field 0
      Domain start;// field 3
      Domain stop;// field 4
      
      istringstream s_start(fields.at(3));
      istringstream s_stop(fields.at(4));
      s_start >> start;
      s_stop >> stop;
      
      int str = BOTH;//either strand
      string strand = fields.at(6);// field 6
      if(strand == "-" || strand == "1"){
	  str = MINUS;
	}
	if(strand == "+" || strand == "0"){
	  str = PLUS;
	}
            
      if(chr.compare(curr_chr)){//curr_chr != chr
	if(curr_chr.compare("")){// curr_chr != ""
	  pair<Capacity, Capacity> temp(curr_chr_start, count);
	  chrmap.insert(pair<string, pair<Capacity, Capacity> >(curr_chr, temp));
	}
	curr_chr = chr;
	curr_chr_start = count;
      }
      ++count;

      c.setInterval(start, stop, str);
      return true;
    }

    //Clean up last chr
    if(curr_chr.compare("")){
      pair<Capacity, Capacity> temp(curr_chr_start, count);
      chrmap.insert(pair<string, pair<Capacity, Capacity> >(curr_chr, temp));
    }
    
    return false;
  }
  
}
