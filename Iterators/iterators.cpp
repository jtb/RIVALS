/*
 * Copyright 2010 Justin T. Brown
 * All Rights Reserved
 * EMAIL: run.intervals@gmail.com
 *
 * This file is part of Rivals.
 *
 * Rivals is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Rivals is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Rivals.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "iterators.h"
#include <iostream>
#include <fstream>
#include "rivalfile.h"
#include "file_utils.h"

namespace rivals {

  const char* no_own::what() const throw(){
    return "Each iterator may only be evaluated once.";
  }

  std::auto_ptr<Node> range(std::string sample){
    return std::auto_ptr<Node>(new Node(new Sample(sample)));
  }
  std::auto_ptr<Node> range(std::string sample, std::string chrom){
    return std::auto_ptr<Node>(new Node(new Sample(sample, chrom)));
  }
  std::auto_ptr<Node> range(std::string sample, std::string chrom, Domain start, Domain stop){
    return std::auto_ptr<Node>(new Node(new Range(sample, chrom, start, stop)));
  }
  std::auto_ptr<Node> range(std::string sample, std::string chrom, Domain point){
    return std::auto_ptr<Node>(new Node(new Range(sample, chrom, point)));
  }
  std::auto_ptr<Node> merge(std::auto_ptr<Node> a, std::auto_ptr<Node> b){
    if(!a.get()) throw no_own();
    if(!b.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new Merge(*(a->iter),*(b->iter)), a, b));
  }
  std::auto_ptr<Node> flatten(std::auto_ptr<Node> a){
    if(!a.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new Flatten(*(a->iter)), a));
  }
  std::auto_ptr<Node> clique(std::auto_ptr<Node> a, Capacity minOverlap){
    if(!a.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new Clique(*(a->iter), minOverlap), a));
  }
  std::auto_ptr<Node> no_nests(std::auto_ptr<Node> a){
    if(!a.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new NoNests(*(a->iter)), a));
  }
  std::auto_ptr<Node> contained_in(std::auto_ptr<Node> a, std::auto_ptr<Node> b){
    if(!a.get()) throw no_own();
    if(!b.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new ContainedIn(*(a->iter),*(b->iter)), a, b));
  }
  std::auto_ptr<Node> overlaps(std::auto_ptr<Node> a, std::auto_ptr<Node> b){
    if(!a.get()) throw no_own();
    if(!b.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new Overlaps(*(a->iter),*(b->iter)), a, b));
  }
  std::auto_ptr<Node> interval(std::string chr, Domain start, Domain stop){
    return std::auto_ptr<Node>(new Node(new IntervalIter(chr, start, stop)));
  }
  std::auto_ptr<Node> get_strand(std::auto_ptr<Node> a, int str){
    if(!a.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new GetStrand(*(a->iter), str), a));
  }
  std::auto_ptr<Node> set_strand(std::auto_ptr<Node> a, int str){
    if(!a.get()) throw no_own();
    return std::auto_ptr<Node>(new Node(new SetStrand(*(a->iter), str), a));
  }

  std::string saveAsBED(std::auto_ptr<Node> a){
    saveAsBED("-", a);
  }

  std::string saveAsBED(std::string filename, std::auto_ptr<Node> a){
    std::ofstream fout;
    bool toFile = false;
    if(filename.compare("-")){
      fout.open(filename.c_str());
      toFile = true;
    }
    std::string chrom;
    std::string strand;
    std::set<std::string>::const_iterator it;
    Interval c;
    for(it = a->iter->getChrList().begin(); it != a->iter->getChrList().end(); ++it){
      chrom = (*it);
      a->iter->setChr(chrom);

      while(a->iter->next(chrom, c)){
        if(c.getStrand() == PLUS) strand = "+";
        else if(c.getStrand() == MINUS) strand = "-";
        else strand = ".";
        if(toFile){
          fout << chrom << "\t" << c.getStart() << "\t" << c.getStop() << "\t\t";
        }else{
	  std::cout << chrom << "\t" << c.getStart() << "\t" << c.getStop() << "\t\t";
        }
        if(a->iter->has_score){
          if(toFile){
            fout << a->iter->score;
          }else{
	    std::cout << a->iter->score;
          }
        }
        if(toFile){
          fout << "\t" << strand << std::endl;
        }else{
	  std::cout << "\t" << strand << std::endl;
        }
      }
    }
    if(toFile) fout.close();
    return filename;
  }
 
  std::string saveAsRival(std::string base, std::auto_ptr<Node> a){
    RivalFile rf(*(a->iter));
    importData(rf, base);
    return base;
  }
  
}
