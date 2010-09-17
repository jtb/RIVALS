#include <iostream>
#include <sys/stat.h>
//#include "bedfile.h"
//#include "gfffile.h"
//#include "file_utils.h"
//#include "iterators.h"
#include "rivals.h"

using namespace std;
using namespace rivals;

int main(){
  //BEDfile bed1("Data/test_sorted.bed");
  //importData(bed1, "bsample2");

  //cout << "intervals is " << sizeof(Interval) << endl;
  //cout << "cIntervals is " << sizeof(cInterval) << endl;

  //BEDfile bed2("Data/itree.bed");
  //importData(bed2, "asample2");

  /**
  struct stat stFileInfo;
  if(stat("csample.riv",&stFileInfo)){//file does not exist 
    BEDfile bed("Data/testOverlap.bed");
    importData(bed, "csample");
  }
  **/

  importBED("Data/testOverlap.bed", "csample");

  /**
  printf("import gff\n");
  GFFfile gff("Data/iSample.gff");
  importData(gff, "gsample");
  printf("done\n");
  **/

  importGFF("Data/iSample.gff", "gsample", true);

  //Chain c;
  //c.range("csample").saveAsBED();
  //c.overlaps(c.flatten(c.range("csample")), c.clique(c.range("csample"), 3)).saveAsBED();
  
  //saveAsRival("bad", range("csample"));
  //overlaps(flatten(range("csample")), clique(range("csample"), 3))->saveAsBED();
  saveAsRival("good", overlaps(flatten(range("csample")), clique(range("csample"), 3)));
  
  saveAsBED("-", range("good"));
  
  saveAsBED("-", clique(range("gsample"), 10));

  printf("save gff to bed\n");
  saveAsBED("gff.bed", range("gsample"));

  //Chain::Instance().setEmpty();
  
  /**
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
  //c.range("asample", "chr1", 16, 22).saveAsBED();
  //c.contained_in(c.get_strand(c.set_strand(c.range("asample", "chr1", 16, 22), MINUS), MINUS),c.interval("chr1", 16, 22)).saveAsBED();

  c.range("bsample", "chr8", 40568857, 41728151).saveAsBED();
  cout << endl << endl;
  c.overlaps(c.range("bsample"), c.interval("chr8", 40568857, 41728151)).saveAsBED();
    
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
  **/
  return 0;
}
