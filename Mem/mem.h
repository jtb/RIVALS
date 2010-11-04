#ifndef MEMCHECK_H_
#define MEMCHECK_H_

#include <new>

void* operator new (size_t);
void operator delete (void *);

void printLeak();

namespace {
  
  struct Node {
    size_t addr;
    struct Node * next;
  };
  
  struct MemList {
    void insert(size_t s){
      struct Node * n;
      n = (struct Node *) malloc(sizeof(struct Node));
      n->addr = s;
      n->next = first;
      first = n;
      siz++;
      total_siz++;
      if(max_siz < siz) max_siz = siz;
    }
    
    void erase(size_t s){
      if(!first){
	std::cout << "attempting to free unallocated memory!" << std::endl;
	return;
      }
      
      struct Node * n = first;
      if(n->addr == s){//delete first
	first = n->next;
	free(n);
	siz--;
	return;
      }
      
      struct Node * prev = n;
      n = n->next;
      
      while(n){
	if(n->addr == s){
	  prev->next = n->next;
	  free(n);
	  siz--;
	  return;
	}
	prev = n;
	n = n->next;
      }
      //not found
      std::cout << "attempting to free unallocated memory!" << std::endl;
    }
    
    bool leak() { return (siz > 0); }
    
    struct Node * first;
    size_t siz;
    size_t max_siz;
    size_t total_siz;
  } mem = {0, 0, 0, 0};
}
#endif
