#include <iostream>
#include "file_utils.h"
#include "iterator.h"

using namespace std;
namespace rivals {

  void Iterator::saveAsBED(){
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
	cout << chrom << "\t" << c.getStart() << "\t" << c.getStop() << "\t\t";
	if(has_score){
	  cout << score;
	}
	cout << "\t" << strand << endl;
      }
    }
  }

}
