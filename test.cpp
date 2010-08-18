#include <iostream>
#include <string>

#include "interval.h"
#include "utils.h"
#include "bedfile.h"

using namespace std;
using namespace rivals;

int main(){
  Interval a(10, 20, PLUS);
  Interval b(5, 15, MINUS);
  printf("%d\n", a.overlaps(b));
  printf("%d\n", !a.overlaps(b, true));
  printf("%d\n", b < a);

  string bedfile = "test_sorted.bed";
  BEDfile bf(bedfile);
  Interval c;
  string chr;
  while(bf.next(chr, c)){}

  writeChrMap(bf.getChrMap(), "mychr.map");

  return 0;
}
