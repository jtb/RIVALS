#include <iostream>
#include <string>

#include "rivals.h"

#ifdef DEBUG
#include "mem.h"
#endif

using namespace std;
using namespace rivals;

int main(){
  {
  /* Import files into RIVAL format
     First argument is the name of the text file(BED or GFF format).
     Second argument is name of sample.
     Output is two files, sample.riv and sample.map, where sample is the name supplied in argument 2.
     Note 1: If a .map and .riv file are already present, then it will not re-import them.
     Note 2: Importing requires sorting.  If the intervals are already sorted by genomic order, they will not 
     need to be sorted during import.
   */

  cout << "Importing Files..." << endl << endl;
  string rival1 = "Output/bed_test";
  string rival2 = "Output/gff_test";
  importBED("../Data/test.bed", rival1);
  importGFF("../Data/chrX.gff", rival2);

  /* Source Iterator
     You can load all or parts of the RIVAL file using the "range" iterator
     range(sample)                   <-- loads entire rival file
     range(sample, chr)              <-- only loads specified chromosome
     range(sample, chr, start, stop) <-- only loads intervals that overlap the range
     range(sample, chr, point)       <-- only loads intervals that overlap the point
     Note 1: The RIVAL format allows you to efficiently jump to a particular chromosome or range
     instead of doing a full linear traversal of all intervals.
     Note 2: The contents of the file don't actually get loaded into memory, so the range iterator
     will work on files larger than the available memory
  
     Chaining Iterators
     An iterator performs some action on 1 or 2 streams of sorted intervals and 
     outputs the results as a stream of intervals sorted by genomic location.  Therefore,
     multiple iterators can be chained together to perform complicated tasks.  See manual for
     description of iterators.

     Sink Iterator
     You can save the results as a text file (BED) or as a RIVAL file.  The RIVAL file can be used in further
     iterator chains without importing.  The BED file will need to be imported if you wish to use it further.
     saveAsBED
     saveAsRival
  */

  /** Examples **/
  //Save to BED file
  cout << "Example 1:" << endl;
  saveAsBED("Output/gff.bed", range(rival2));
  cout << "Saved to Output/gff.bed" << endl << endl;

  //Print to standard out all intervals that overlap chr8:28510032-31173640
  cout << "Example 2:" << endl;
  saveAsBED(range(rival1, "chr8", 28510032, 31173640));
  cout << endl;

  //Do the same as above, but save to a Rival file.  Print out regions after changing strands to '-'
  cout << "Example 3:" << endl;
  saveAsRival("Output/output", range(rival1, "chr8", 28510032, 31173640));
  cout << "Saved to output.riv and output.map" << endl;
  saveAsBED(set_strand(range("Output/output"), MINUS));
  cout << endl;

  //These two methods should give identical results, but one is more efficent
  cout << "Example 4:" << endl;
  //Method 1: Uses range to find intervals quickly
  cout << "Method 1:" << endl;
  saveAsBED(range(rival2, "chrX", 100165880, 100168052));
  //Method 2: Finds intervals in rival2 that overlap the specified interval.  Requires a linear
  //traversal overl rival2.
  cout << "Method 2:" << endl;
  saveAsBED(overlaps(range(rival2), interval("chrX", 100165880, 100168052)));
  cout << endl;

  //Find the intersection of two interval graphs
  //First, we "flatten" the two interval graphs.  Next we merge the two lists of intervals
  //together and find all regions that overlap by 2.
  cout << "Example 5:" << endl;
  saveAsBED( clique( merge( flatten( range(rival1) ), flatten( range(rival2) )) , 2 ) );
  }

#ifdef DEBUG
  printLeak();
#endif
  
  return 0;
}
