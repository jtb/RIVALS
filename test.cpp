#include <iostream>
#include <string>

#include "interval.h"
#include "file_utils.h"
//#include "utils.h"
#include "bedfile.h"
#include "cache.h"
#include "iterators.h"

using namespace std;
using namespace rivals;

int main(){
  Interval a(6, 128, PLUS);
  Interval b(5, 15, MINUS);
  a.printInterval();
  b.printInterval();
  printf("%d\n", a.overlaps(b));
  printf("%d\n", !a.overlaps(b, true));
  printf("%d\n", b < a);

  BEDfile bed("test_sorted.bed");
  rivalWriter(bed, "awesome_sample");

  string version;
  off_t offset;
  Capacity num_elements;
  if(readHeader("awesome_sample", version, offset, num_elements)){
    cout << version << "\t" << offset << "\t" << num_elements << endl;
  }
  ForwardCache<Interval> fvector(fileFromSample("awesome_sample"));
  CenteredCache<Interval> cvector(fileFromSample("awesome_sample"), true);
  fvector.setRange(offset, 1, 11);
  cvector.setRange(offset, 1, 11);
  Interval intv;
  for(Capacity i = 0; i < fvector.size(); i++){
    intv = fvector.at(i);
    intv.printInterval();
    intv = cvector.at(i);
    intv.printInterval();
  }

  fvector.setRange(offset, 0, 14);
  cvector.setRange(offset, 0, 14);
  for(Capacity i = 0; i < fvector.size(); i++){
    intv = fvector.at(i);
    intv.printInterval();
    intv = cvector.at(i);
    intv.printInterval();
  }

  string name = "charfile.txt";
  CenteredCache<char> twc(name, false);
  twc.setRange(0, 0, 16);
  twc.set(14, 'W');
  for(Capacity i = 0; i < twc.size(); i++){
    printf("%c", twc.at(i));
  }
  printf("\n");

  Sample s("awesome_sample");
  s.setChr("chrY");
  string chrom;
  while(s.next(chrom, intv)){
    printf("%s\t", chrom.c_str());
    intv.printInterval();
  }

  //indexNodes(offset, "awesome_sample");

  /**
  string bedfile = "test_sorted.bed";
  BEDfile bf(bedfile);
  Interval c;
  string chr;
  while(bf.next(chr, c)){}

  writeChrMap(bf.getChrMap(), "mychr.map");
  **/

  return 0;
}
