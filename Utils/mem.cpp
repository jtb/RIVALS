#include <iostream>
#include <exception>
#include <cstdlib>

#include "mem.h"

void* operator new (size_t size){
  void *p=malloc(size);
  if(p==0)
    throw std::bad_alloc();
  
  std::cout << "allocating address " << (size_t)p << std::endl;
  mem.insert((size_t)p);
  return p;
}

void operator delete (void *p){
  std::cout << "de-allocating address " << (size_t)p << std::endl;
  mem.erase((size_t)p);
  free(p);
}

void printLeak(){
  std::cout << "You allocated " << mem.total_siz << " blocks of memory." << std::endl;
  std::cout << "Maximum block usage was " << mem.max_siz << " blocks of memory." << std::endl;
  if(mem.leak()){
    std::cout << "You have " << mem.siz << " leaks." << std::endl;
    std::cout << "They are " << std::endl;

    struct Node * n = mem.first;
    while(n){
      std::cout << n->addr << std::endl;
      n = n->next;
    }
  }else{
    std::cout << "No leaks to report.  Good job." << std::endl;
  }
}
