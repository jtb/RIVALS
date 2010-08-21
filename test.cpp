#include <iostream>
#include <string>

#include "interval.h"
#include "file_utils.h"
//#include "utils.h"
#include "bedfile.h"

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
