#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "typedef.h"

namespace rivals {

  class Interval {
  public:
    Interval(Domain start, Domain stop, int str);
    Interval();

    int getStrand() const;
    Domain getStart() const;
    Domain getStop() const;
    Domain getSubMax() const;

    void setInterval(Domain start, Domain stop, int str);
  
    void setSubMax(Domain max);

    Length getLength() const;

    bool overlaps(const Interval & b, bool strand_specific = false);
      
    bool operator<(const Interval & b) const;

  private:
    void setStrand(int s);
    void setStart(Domain start);
    void setStop(Domain stop);
    
    Domain left; //      4 bytes
    Domain right; //     4 bytes
    Domain submax; //    4 bytes
    int strand; // 4 bytes
    // total bytes =     16 bytes
  };
  
}//namespace rivals

#endif
