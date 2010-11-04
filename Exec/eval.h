#ifndef EVAL_H_
#define EVAL_H_

#include <iostream>
#include <string>

#include "rivals.h"

class Eval {
 public:
 Eval() : left_child(0), right_child(0) { }
	
	virtual ~Eval(){
		delete right_child;
		right_child=0;
		delete left_child;
		left_child=0;
	}

	virtual std::auto_ptr<rivals::Node> eval() = 0;
	
 protected:
	Eval * left_child;
	Eval * right_child;
		
};

class Range1 : public Eval {
 public:
 Range1(std::string samp) : Eval(), sample(samp) {}
  ~Range1(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::range(sample);
  }
 private:
  std::string sample;
};

class Range2 : public Eval {
 public:
 Range2(std::string samp, std::string ch) : Eval(), sample(samp), chr(ch) {}
  ~Range2(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::range(sample, chr);
  }
 private:
  std::string sample;
  std::string chr;
};

class Range4 : public Eval {
 public:
 Range4(std::string samp, std::string ch, ptrdiff_t start, ptrdiff_t stop) : Eval(), sample(samp), chr(ch), begin(start), end(stop) {}
  ~Range4(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::range(sample, chr, begin, end);
  }
 private:
  std::string sample;
  std::string chr;
  rivals::Domain begin;
  rivals::Domain end;
};

class Interval : public Eval {
 public:
 Interval(std::string chr, ptrdiff_t start, ptrdiff_t stop) : Eval(), chrom(chr), begin(start), end(stop) {}
  ~Interval(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::interval(chrom, begin, end);
  }
 private:
  std::string chrom;
  rivals::Domain begin;
  rivals::Domain end;
};

class Merge : public Eval {
 public:
 Merge(Eval * n, Eval * m) : Eval() {
    left_child = n;
    right_child = m;
  }
  ~Merge(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::merge(left_child->eval(), right_child->eval());
  }
};

std::string SaveAsBED(Eval * n){
  std::string filename = rivals::saveAsBED(n->eval());
  delete n;
  return filename;
}

std::string SaveAsBED(std::string file, Eval *n){
  std::string filename = rivals::saveAsBED(file, n->eval());
  delete n;
  return filename;
}

std::string SaveAsRival(std::string base, Eval *n){
  std::string basename = rivals::saveAsRival(base, n->eval());
  delete n;
  return basename;
}

rivals::Capacity CountIntervals(Eval *n){
  rivals::Capacity num_intervals = rivals::countIntervals(n->eval());
  delete n;
  return num_intervals;
}

#endif
