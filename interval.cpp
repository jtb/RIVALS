#include "interval.h"

namespace rivals {

  Interval::Interval(Domain start, Domain stop, int str)
    : left(start), right(stop), submax(0), strand(str) {
    if(left > right){
      Domain temp = left;
      left = right;
      right = temp;
    }
  }
  
  Interval::Interval()
    : left(0), right(0), submax(0), strand(0) {}

  int Interval::getStrand() const { return strand; }
  Domain Interval::getStart() const { return left; }
  Domain Interval::getStop() const { return right; }
  Domain Interval::getSubMax() const { return submax; }

  void Interval::setInterval(Domain start, Domain stop, int str){
    setStart(start);
    setStop(stop);
    setStrand(str);
  }
  
  void Interval::setStrand(int s) { strand = s; }
  void Interval::setStart(Domain start) { left = start; }
  void Interval::setStop(Domain stop) { right = stop; }
  
  void Interval::setSubMax(Domain max) { submax = max; }

  Length Interval::getLength() const { return (right - left); }

  bool Interval::overlaps(const Interval & b, bool strand_specific){
    if(getStrand() == b.getStrand() || getStrand() == BOTH || b.getStrand() == BOTH || !strand_specific){
      return (left < b.getStop() && b.getStart() < right);
    }
    return false;
  }

  bool Interval::operator<(const Interval & b) const {
    if(left == b.getStart()){
      return (right < b.getStop());
    }
    return (left < b.getStart());
  }

}//namespace rivals
