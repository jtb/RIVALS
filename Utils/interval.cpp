#include <iostream>
#include "interval.h"

namespace rivals {

  Interval::Interval(Domain start, Domain stop, int str) : submax(0), left(0), right(0) {
    setInterval(start, stop, str);
  }
  
  Interval::Interval()
    : submax(0), left(0), right(0) {}

  int Interval::getStrand() const {
    if(right&1) return MINUS;
    if(left&1) return BOTH;
    return PLUS;
  }
  Domain Interval::getStart() const { return (left>>1); }
  Domain Interval::getStop() const { return (right>>1); }
  Domain Interval::getSubMax() const { return submax; }

  Length Interval::getLength() const { return (getStop() - getStart()); }

  void Interval::printInterval() const{
    std::cout << getSubMax() << "\t" << getStart() << "\t" << getStop() << "\t";
    int s = getStrand();
    if(s == MINUS) std::cout << "-" << std::endl;
    else if(s == PLUS) std::cout << "+" << std::endl;
    else std::cout << "." << std::endl;
  }
  
  void Interval::setInterval(Domain start, Domain stop, int str){
    assert(inRange(start, stop));
    setStart(start);
    setStop(stop);
    setStrand(str);
  }

  bool Interval::inRange(Domain start, Domain stop){
    if(stop <= start) return false;
    //std::cout << std::numeric_limits<Domain>::min()/2 << std::endl;
    //std::cout << std::numeric_limits<Domain>::max()/2 << std::endl;
    if(start < std::numeric_limits<Domain>::min()/2) return false;
    if(stop  > std::numeric_limits<Domain>::max()/2) return false;
    return true;
  }
  
  void Interval::setStrand(int s) {
    Domain one = 1;
    Domain c_one = ~1;
    if(s==MINUS){
      right |= one; 
    }else{
      right &= c_one;
    }
    if(s==BOTH){
      left |= one;
    }else{
      left &= c_one;
    }
  }
  void Interval::setStart(Domain start) {
    left = (left&1) | (start<<1);
  }
  void Interval::setStop(Domain stop) { 
    right = (right&1) | (stop<<1); 
  }
  void Interval::setSubMax(Domain max) { submax = max; }

  bool Interval::overlaps(const Interval & b, bool strand_specific){
    if(getStrand() == b.getStrand() || getStrand() == BOTH || b.getStrand() == BOTH || !strand_specific){
      return (getStart() < b.getStop() && b.getStart() < getStop());
    }
    return false;
  }

  bool Interval::operator<(const Interval & b) const {
    if(getStart() == b.getStart()){
      return (getStop() < b.getStop());
    }
    return (getStart() < b.getStart());
  }

}//namespace rivals
