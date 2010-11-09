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

class Flatten : public Eval {
 public:
 Flatten(Eval * n) : Eval() {
    left_child = n;
  }
  ~Flatten(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::flatten(left_child->eval());
  }
};

class Clique : public Eval {
 public:
 Clique(Eval * n, ptrdiff_t min) : Eval(), minOverlap(min) {
    left_child = n;
  }
  ~Clique(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::clique(left_child->eval(), minOverlap);
  }
 private:
  rivals::Capacity minOverlap;
};

class Contained_In : public Eval {
 public:
 Contained_In(Eval * n, Eval * m) : Eval() {
    left_child = n;
    right_child = m;
  }
  ~Contained_In(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::contained_in(left_child->eval(), right_child->eval());
  }
};

class Contains : public Eval {
 public:
 Contains(Eval * n, Eval * m) : Eval() {
    left_child = n;
    right_child = m;
  }
  ~Contains(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::contains(left_child->eval(), right_child->eval());
  }
};

class Overlaps : public Eval {
 public:
 Overlaps(Eval * n, Eval * m) : Eval() {
    left_child = n;
    right_child = m;
  }
  ~Overlaps(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::overlaps(left_child->eval(), right_child->eval());
  }
};

class Get_Strand : public Eval {
 public:
 Get_Strand(Eval * n, int str) : Eval(), strand(str) {
    left_child = n;
  }
  ~Get_Strand(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::get_strand(left_child->eval(), strand);
  }
 private:
  int strand;
};

class Set_Strand : public Eval {
 public:
 Set_Strand(Eval * n, int str) : Eval(), strand(str) {
    left_child = n;
  }
  ~Set_Strand(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::set_strand(left_child->eval(), strand);
  }
 private:
  int strand;
};

class Score_Cutoff : public Eval {
 public:
 Score_Cutoff(Eval * n, int thr) : Eval(), thresh(thr) {
    left_child = n;
  }
  ~Score_Cutoff(){}

  std::auto_ptr<rivals::Node> eval(){
    return rivals::score_cutoff(left_child->eval(), thresh);
  }
 private:
  int thresh;
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
