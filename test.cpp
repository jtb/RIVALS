#include <iostream>
#include <string>

#include "interval.h"
#include "file_utils.h"
//#include "utils.h"
#include "bedfile.h"
#include "cache.h"

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
  fvector.setRange(offset, 1, 11);
  Interval intv;
  for(Capacity i = 0; i < fvector.size(); i++){
    intv = fvector.at(i);
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
