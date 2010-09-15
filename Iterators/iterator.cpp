#include <iostream>
#include "iterator.h"
#include <fstream>

using namespace std;
namespace rivals {

  void Iterator::saveAsBED(string filename){
    std::ofstream fout;
    bool toFile = false;
    if(filename.compare("")){
      fout.open(filename.c_str());
      toFile = true;
    }
    string chrom;
    string strand;
    set<string>::const_iterator it;
    Interval c;
    for(it = this->getChrList().begin(); it != this->getChrList().end(); ++it){
      chrom = (*it);
      setChr(chrom);

      while(next(chrom, c)){
	if(c.getStrand() == PLUS) strand = "+";
	else if(c.getStrand() == MINUS) strand = "-";
	else strand = ".";
	if(toFile){
	  fout << chrom << "\t" << c.getStart() << "\t" << c.getStop() << "\t\t";
	}else{
	  cout << chrom << "\t" << c.getStart() << "\t" << c.getStop() << "\t\t";
	}
	if(has_score){
	  if(toFile){
	    fout << score;
	  }else{
	    cout << score;
	  }
	}
	if(toFile){
	  fout << "\t" << strand << endl;
	}else{
	  cout << "\t" << strand << endl;
	}
      }
    }
    if(toFile) fout.close();
  }

  void Iterator::saveAsRival(string sample){
  }
  
}
