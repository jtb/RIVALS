#include <fstream>
#include <iostream>

#include "utils.h"

using namespace std;

namespace rivals {

  void Tokenize(const string & str, vector<string> & tokens, const string & delimiters){
    string::size_type firstPos = 0;
    string::size_type lastPos = str.find_first_of(delimiters, firstPos);
    while(string::npos != lastPos){
      tokens.push_back(str.substr(firstPos, lastPos - firstPos));
      firstPos = lastPos + 1;
      lastPos = str.find_first_of(delimiters, firstPos);
    }
    tokens.push_back(str.substr(firstPos, lastPos - firstPos));
  }
  
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

}
