#include <iostream>
#include "bedfile.h"
#include "file_utils.h"
#include "iterators.h"

using namespace std;
using namespace rivals;

int main(){
  BEDfile bed1("Data/test_sorted.bed");
  importData(bed1, "bsample");

  BEDfile bed2("Data/itree.bed");
  importData(bed2, "asample");

  Range r("bsample", "chr3", 1500000, 3000000);
  Sample s("asample");
  Merge m(r,s);
  m.saveAsBED();

  cout << endl << endl;
  Range z("asample", "chr1", 19);
  z.saveAsBED();

  return 0;
}