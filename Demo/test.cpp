#include <iostream>
#include "bedfile.h"
#include "file_utils.h"
#include "iterators.h"

using namespace std;
using namespace rivals;

int main(){
  BEDfile bed1("Data/test_sorted.bed");
  importData(bed1, "bsample");

  //BEDfile bed2("Data/itree.bed");
  //importData(bed2, "asample");

  Chain c;
  //Sample s1("bsample");
  //Sample s2("bsample");
  //c.flatten(c.clique(s, 2)).saveAsBED();
  //c.merge(s,s).saveAsBED();

  //chr8 40568857 405688824 .
  //chr8 78193723 781937484 .
  //chr8 85059549 850595744 .
  //chr8 101641327 1016413524 .
  //chr8 125556826 1255568374 .
  //chr8 127407510 127407535 .
  //c.clique(c.merge(c.range("bsample", "chr8", 40568857, 227407535),c.range("bsample", "chr8", 40568857, 227407535)), 4).saveAsBED();

  //c.no_nests(c.range("asample")).saveAsBED();
  //c.contained_in(c.flatten(c.range("asample")), c.range("asample")).saveAsBED();
  c.range("asample", "chr1", 16, 22).saveAsBED();
  c.contained_in(c.get_strand(c.set_strand(c.range("asample", "chr1", 16, 22), MINUS), MINUS),c.interval("chr1", 16, 22)).saveAsBED();

  //Clique c(s, 5);
  //c.saveAsBED();

  //Merge(Sample("asample"), Sample("asample")).saveAsBED();
  //Sample s("asample");
  //s.saveAsBED();
  //cout << endl << endl;
  //Flatten f(s);
  //f.saveAsBED();

  //Range r("bsample", "chr3", 1500000, 3000000);
  //Sample s("asample");
  //Merge m(r,s);
  //m.saveAsBED();

  //cout << endl << endl;
  //Range z("asample", "chr1", 19);
  //z.saveAsBED();

  return 0;
}
