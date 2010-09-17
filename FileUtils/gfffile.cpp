#include <sstream>
#include <vector>

#include "typedef.h"
#include "interval.h"
#include "utils.h"
#include "gfffile.h"

using namespace std;

namespace rivals {
  GFFfile::GFFfile(string filename) : file_in(filename.c_str()) {
    if(!file_in.is_open()){
      printf("Could not open gff file %s for reading.\n", filename.c_str());
    }
  }

  GFFfile::~GFFfile(){
    file_in.close();
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
            
      c.setInterval(start, stop, str);
      return true;
    }

    return false;
  }
  
}
