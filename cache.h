#ifndef CACHE_H_
#define CACHE_H_

#include <fstream>
#include "typedef.h"

namespace rivals {

  template <class T>
    class ForwardCache
    {
    public:
    ForwardCache(std::string f) : num_elements(0), file_start(0), first_index(0), valid_size(0) {
        file.open(f.c_str(), std::ios::in | std::ios::binary);
	if(!file) printf("Could not open %s for reading.\n", f.c_str());
	batch(0);
      }

      ~ForwardCache(){
	file.close();
      }

      //index with respect to pseudo-file
      T at(Capacity index){
	assert(index < this->num_elements);
	if(index >= this->first_index && index < this->first_index + this->valid_size){
          return this->buffer[index - this->first_index];
        }else{
          batch(index);
          return this->buffer[index - this->first_index];
        }
      }

      Capacity size() const { return num_elements; }
      
      void setRange(off_t offset, Capacity start, Capacity stop){
	assert(start < stop);
	file_start = offset + start*sizeof(T);
	num_elements = stop - start;
      }

    private:
      void batch(Capacity index){
	this->first_index = index;
	this->valid_size = CACHE;
	if(this->num_elements < CACHE + this->first_index){
	  this->valid_size = this->num_elements - this->first_index;
	}

	this->file.seekg((this->first_index)*sizeof(T) + this->file_start, std::ios::beg);
	this->file.read((char*)&(this->buffer), (this->valid_size)*sizeof(T));
	assert(this->file);
      }
      
      Capacity num_elements;
      off_t file_start;
      Capacity first_index;
      int valid_size;
      std::fstream file;
      T buffer[CACHE];
    };
}

#endif
