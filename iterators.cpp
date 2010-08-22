#include <iostream>
#include "interval.h"
#include "file_utils.h"
#include "iterators.h"

using namespace std;
namespace rivals {

  void Iterator::saveAsBED(){
    string chrom;
    string strand;
    set<string>::const_iterator it;
    Interval c;
    for(it = chr_list.begin(); it != chr_list.end(); ++it){
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

  Sample::Sample(string sample) : Iterator(), samp_name(sample), on_chromosome(false), index(0), offset(0), fvector(fileFromSample(sample)) {
    readChrMap(samp_name, chrmap);
    //set chrlist;
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      chr_list.insert(it->first);
    }

    string version;
    Capacity num_elements;
    readHeader(samp_name, version, offset, num_elements);
  }

  Sample::Sample(string sample, string chrom) : Iterator(), samp_name(sample), on_chromosome(false), index(0), offset(0), fvector(fileFromSample(sample)) {
    readChrMap(samp_name, chrmap, chrom);
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      chr_list.insert(it->first);
    }

    string version;
    Capacity num_elements;
    readHeader(samp_name, version, offset, num_elements);

    setChr(chrom);
  }

  Range::Range(string sample, string chrom, Domain start, Domain stop) : Iterator(), samp_name(sample), on_chromosome(false), d(start, stop, BOTH), offset(0), cvector(fileFromSample(sample)) {
    readChrMap(samp_name, chrmap, chrom);
    map<string, pair<Capacity, Capacity> >::const_iterator it;
    for(it = chrmap.begin(); it != chrmap.end(); ++it){
      chr_list.insert(it->first);
    }
    
    string version;
    Capacity num_elements;
    readHeader(samp_name, version, offset, num_elements);

    setChr(chrom);
  }

  Merge::Merge(Iterator & a, Iterator & b) : itA(a), itB(b) {
    mergeChromLists(a.getChrList(), b.getChrList());
  }


  void Merge::setChr(std::string chrom){
    itA.setChr(chrom);
    itB.setChr(chrom);
    avalid = itA.next(chromA, a);
    bvalid = itB.next(chromB, b);
    chr = chrom;
   }

  bool Sample::next(string & chrom, Interval & intv){
    if(!on_chromosome) return false;
    chrom = chr;
    if(index < fvector.size()){
      intv = fvector.at(index);
      ++index;
      return true;
    }
    return false;
  }

  bool Merge::next(std::string & chrom, Interval & intv){
    if(!avalid && !bvalid) return false;
    
    if(avalid && !bvalid){
      intv = a;
      chrom = chromA;
      avalid = itA.next(chromA, a);
      return true;
    }
    if(!avalid && bvalid){
      intv = b;
      chrom = chromB;
      bvalid = itB.next(chromB, b);
      return true;
    }
    //avalid && bvalid
    assert(chromA == chromB);
    if(a < b){
      intv = a;
      chrom = chromA;
      avalid = itA.next(chromA, a);
    }else{
      intv = b;
      chrom = chromB;
      bvalid = itB.next(chromB, b);
    }
    return true;
  }


  /**
  bool Range::next(string & chrom, Interval & intv){                                                                                                         
    if(!on_chromosome) return false;
    chrom = chr;
    
    while(!recurse.empty()){
      Cargo c = recurse.top();
      intv = cvector.at(c.root);
      if(c.goLeft){
        recurse.top().goLeft = false;
	if(d.getStart() < intv.getSubMax()){
          //search left children, if it exists                                                       
          Capacity root;
          if(getMidpoint(c.low, c.root, root)){
            recurse.push(Cargo(c.low, c.root, root));
          }
        }
      }else{//check this one, then go right                                                          
	recurse.pop();
        if(d.getStop() > intv.getStart()){
          //could be here                                                                            
          Capacity root;
          if(getMidpoint(c.root+1, c.high, root)){
            recurse.push(Cargo(c.root+1, c.high, root));
          }
          if(intv.overlaps(d)){
	    return true;
          }
        }
      }
    }

    return false;
  }
  **/
  
  bool Range::next(string & chrom, Interval & intv){
    if(!on_chromosome) return false;
    chrom = chr;
    
    while(!recurse.empty()){
      Cargo c = recurse.top();
      Interval i = cvector.at(c.root);
      if(d.getStart() >= i.getSubMax()){
	recurse.pop();
      }else{
	if(!c.goLeft){
	  //check this one, pop, then put right on top if it exists and start is less than i stop
	  recurse.pop();
	  if(d.getStop() > i.getStart()){
	    Capacity root;
	    if(getMidpoint(c.root+1, c.high, root)){
	      recurse.push(Cargo(c.root+1, c.high, root));
	    }
	  
	    if(i.overlaps(d)){
	      intv = i;
	      return true;
	    }
	  }//else this node and right children do not overlap d
	}else{
	  recurse.top().goLeft = false;
	  //go left
	  Capacity root;
	  if(getMidpoint(c.low, c.root, root)){
	    recurse.push(Cargo(c.low, c.root, root));
	  }
	}
      }
    }
    return false;
  }
 
  void Sample::setChr(string chrom){
    //get offset, get actual start and stop from chrmap
    Capacity start;
    Capacity stop;
    if(getRanges(chrom, chrmap, start, stop)){
      on_chromosome = true;
      chr = chrom;
      index = 0;
      fvector.setRange(offset, start, stop);
    }else{
      on_chromosome = false;
    }
  }

  void Range::setChr(string chrom){
    recurse = stack<Cargo>();
    Capacity start;
    Capacity stop;
    if(getRanges(chrom, chrmap, start, stop)){
      on_chromosome = true;
      chr = chrom;
      cvector.setRange(offset, start, stop);
      Capacity root;
      if(getMidpoint(0, cvector.size(), root)){
	recurse.push(Cargo(0, cvector.size(), root));
      }
    }else{
      on_chromosome = false;
    }
  }

}
