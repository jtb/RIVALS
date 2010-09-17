#include <sstream>
#include <vector>

#include "typedef.h"
#include "interval.h"
#include "utils.h"
#include "bedfile.h"

using namespace std;

namespace rivals {
  BEDfile::BEDfile(string filename) : file_in(filename.c_str()) {
    if(!file_in.is_open()){
      printf("Could not open bed file %s for reading.\n", filename.c_str());
    }
  }

  BEDfile::~BEDfile(){
    file_in.close();
  }
  
  bool BEDfile::next(string & chr, Interval & c){
    if(!file_in.is_open()) return false;
    while(!file_in.eof()){
      getline(file_in, line);
      if(line == "") continue;
      
      vector<string> fields;
      Tokenize(line, fields, " \t");
      assert(fields.size() >= 3);
      chr = fields.at(0);// field 0
      Domain start;// field 1
      Domain stop;// field 2
      
      istringstream s_start(fields.at(1));
      istringstream s_stop(fields.at(2));
      s_start >> start;
      s_stop >> stop;
      
      int str = BOTH;//either strand
      if(fields.size() >= 6){
	string strand = fields.at(5);// field 5                                                 
	if(strand == "-" || strand == "1"){
	  str = MINUS;
	}
	if(strand == "+" || strand == "0"){
	  str = PLUS;
	}
      }
      c.setInterval(start, stop, str);
      return true;
    }
    
    return false;
  }
  
}
