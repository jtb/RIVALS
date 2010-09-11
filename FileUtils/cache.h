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
	batch(0);
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

  template <class T>
    class CenteredCache
    {
    public:
    CenteredCache(std::string f, bool read = true) : readonly(read), dirty(false), num_elements(0), file_start(0), first_index(0), valid_size(0) {
        if(readonly){
	  file.open(f.c_str(), std::ios::in | std::ios::binary);
	}else{
	  file.open(f.c_str(), std::ios::in | std::ios::out | std::ios::binary);
	}
	if(!file) printf("Could not open %s for reading.\n", f.c_str());
      }

      ~CenteredCache(){
	flush();
	file.close();
      }

      void flush(){
	if(dirty){
	  this->file.seekg((this->first_index)*sizeof(T) + this->file_start, std::ios::beg);
	  this->file.write((char*)&(this->buffer), (this->valid_size)*sizeof(T));
	  assert(this->file);
	}
	dirty = false;
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

      void set(Capacity index, T element){
	assert(!readonly);
	assert(index < this->num_elements);
	if(index >= this->first_index && index < this->first_index + this->valid_size){
	  this->buffer[index-this->first_index]= element;
	}else{
	  batch(index);
	  this->buffer[index-this->first_index]= element;
	}
	dirty = true;
      }

      Capacity size() const { return num_elements; }
      
      void setRange(off_t offset, Capacity start, Capacity stop){
	assert(start < stop);
	flush();
	file_start = offset + start*sizeof(T);
	num_elements = stop - start;
	batch(0);
      }

    private:
      void batch(Capacity index){
	//if dirty, write it, set dirty false
	flush();
	
	this->first_index = 0;//inclusive
	if(index > CACHE/2){
	  this->first_index = index - CACHE/2;
	}
	this->valid_size = CACHE;
	if(this->num_elements < CACHE + this->first_index){
	  this->valid_size = this->num_elements - this->first_index;
	}

	this->file.seekg((this->first_index)*sizeof(T) + this->file_start, std::ios::beg);
	this->file.read((char*)&(this->buffer), (this->valid_size)*sizeof(T));
	assert(this->file);
      }

      bool readonly;
      bool dirty;
      Capacity num_elements;
      off_t file_start;
      Capacity first_index;
      int valid_size;
      std::fstream file;
      T buffer[CACHE];
    };
}

#endif
