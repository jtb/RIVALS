#ifndef TYPEDEF_H_
#define TYPEDEF_H_

#include <stdint.h>
#include <assert.h>

namespace rivals {

  //typedef int32_t Domain;
  typedef uint32_t Domain;
  typedef uint32_t Length;
  typedef uint64_t Capacity;

  enum Strand { PLUS, MINUS, BOTH};

#define CACHE 1024
  //#define MEMORY 1024*1024*8
#define MEMORY 1024

}

#endif
