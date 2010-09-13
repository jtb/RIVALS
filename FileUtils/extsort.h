#ifndef EXTERNAL_SORT_H_
#define EXTERNAL_SORT_H_

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "cache.h"
#include "typedef.h"

namespace rivals {

  template <class T>
    class SortFile
    {
    public:
    SortFile(std::string f, off_t header = 0) : origfile(f), base("ExtSortTemp."), offset(header), head(0) {
	file.open(f.c_str(), std::ios::in | std::ios::binary);
	if(!file) printf("Could not open %s for reading.\n", f.c_str());
		
	off_t size = 0;
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0, std::ios::beg);
	num_elements = (size - offset)/sizeof(T);
	std::cout << "number of elements is " << num_elements << std::endl;
	
	head = new char[offset];
	file.read(head, offset);

	traverseTree();
	rename("ExtSortTemp.0", origfile.c_str());
      }

      ~SortFile(){
	delete[] head;
	head = 0;
      }

      void traverseTree(){
	int num_files = 0;
	std::string filename;
	Capacity n;
	//T * buffer = new T[MEMORY];
	T buffer[MEMORY];

	for(Capacity first_index = 0; first_index < num_elements; first_index += MEMORY){
	  //create filename, and sort chunk
	  std::ostringstream stm;
	  stm << base << num_files;
	  filename = stm.str();
	  n = sortChunk(filename, buffer, first_index);
	  Cargo c(n, filename);
	  while(!fstack.empty() && fstack.top().num <= n){
	    //do merging
	    c = fstack.top();
	    fstack.pop();
	    //Capacity merge(std::string file1, std::string file2, Capacity siz1, Capacity siz2, std::string fileOut)
	    c.num = merge(c.filename, filename, c.num, n, c.filename);
	    n = c.num;
	    filename = c.filename;
	  }
	  fstack.push(c);
	  num_files++;
	}
	//clean up
	//remove original file
	file.close();
	remove(origfile.c_str());
	//merge until one
	if(!fstack.empty()){
	  Cargo c = fstack.top();
	  n = c.num;
	  filename = c.filename;
	  fstack.pop();
	  while(!fstack.empty()){
	    c = fstack.top();
	    fstack.pop();
	    c.num = merge(c.filename, filename, c.num, n, c.filename);
	    n = c.num;
	    filename = c.filename;
	  }
	}
      }
     
      Capacity sortChunk(std::string f, T *buffer, Capacity first_index){
	Capacity valid_size = MEMORY;
	if(this->num_elements < valid_size + first_index){
	  valid_size = this->num_elements - first_index;
	}
	//T buffer2[MEMORY];
	this->file.read((char*)buffer, valid_size*sizeof(T));
	assert(this->file);
	std::sort(buffer, buffer+valid_size);
	std::fstream outfile;
	outfile.open(f.c_str(), std::ios::out|std::ios::binary|std::ios::trunc);
	//outfile.seekg(offset, std::ios::beg);
	outfile.write(head, offset);
	outfile.write((char*)buffer, valid_size*sizeof(T));
	outfile.close();

	return valid_size;
      }

      Capacity merge(std::string file1, std::string file2, Capacity siz1, Capacity siz2, std::string fileOut){
	printf("merging %s and %s\n", file1.c_str(), file2.c_str());
	std::fstream out;
	out.open("ExtSortTemp.temp", std::ios::out | std::ios::binary | std::ios::trunc);
        if(!out) printf("Could not open temp file for writing.\n");
	//out.seekg(offset, std::ios::beg);
	out.write(head, offset);
	T buffer[CACHE];

	Capacity c1 = 0;
	Capacity c2 = 0;
	ForwardCache<T> cache1(file1);
        ForwardCache<T> cache2(file2);
        cache1.setRange(offset, 0, siz1);
        cache2.setRange(offset, 0, siz2);

	bool avalid = (0 < cache1.size());
        bool bvalid = (0 < cache2.size());
	Capacity count;
	do {
          for(count = 0; count < CACHE; count++){
	    if(!avalid && !bvalid) break;
	    if(avalid && !bvalid || (avalid && bvalid && cache1.at(c1) < cache2.at(c2))){
              buffer[count] = cache1.at(c1);
              c1++;
              avalid = (c1 < cache1.size());
              continue;
            }
	    buffer[count] = cache2.at(c2);
            c2++;
            bvalid = (c2 < cache2.size());
          }
	  if(count){
	    out.write((char*)&buffer, count*sizeof(T));
          }
	}while(count == CACHE);
	
	out.close();
	remove(file1.c_str());
	remove(file2.c_str());
	rename("ExtSortTemp.temp", fileOut.c_str());

	return (c1+c2);
      }

    private:
      std::string origfile;
      std::string base;
      off_t offset; //init to header
      char * head;
      std::fstream file;
      Capacity num_elements;

      struct Cargo{
      Cargo(Capacity n, std::string file) : num(n), filename(file) {}
	Capacity num;
	std::string filename;
      };
      std::stack<Cargo> fstack;
    };

}

#endif
