#include <iostream>
#include <string>
#include <stack>

#include "eval.h"

#ifdef DEBUG
#include "mem.h"
#endif

#include "lua.hpp"

int toStrand(const char * str){
  if(!strcmp(str, "+") || !strcmp(str, "0")) return rivals::PLUS;
  if(!strcmp(str, "-") || !strcmp(str, "1")) return rivals::MINUS;

  return rivals::BOTH;
}

int luaL_checkBool(lua_State * L, int arg){
  if(!lua_isboolean(L, arg)){ luaL_typerror(L, arg, "boolean"); }
  return lua_toboolean(L, arg);
}

Eval * luaL_checkRunner(lua_State * L, int arg){
  if(!lua_islightuserdata(L, arg)){ luaL_typerror(L, arg, "Runner"); }
  return (Eval *)lua_touserdata(L, arg);
}

static int importBED(lua_State * L){
  if(lua_gettop(L) != 2 && lua_gettop(L) !=3){ luaL_error(L, "Expecting 2 or 3 arguments to importBED command"); }
  
  std::string arg1 = luaL_checkstring(L,1);
  std::string arg2 = luaL_checkstring(L,2);

  if(lua_gettop(L) == 2){
    lua_pushstring(L, rivals::importBED(arg1, arg2).c_str());
  }else{
    int overwrite = luaL_checkBool(L,3);
    lua_pushstring(L, rivals::importBED(arg1, arg2, overwrite).c_str());
  }
  return 1;
}
static int importGFF(lua_State * L){
  if(lua_gettop(L) != 2 && lua_gettop(L) !=3){ luaL_error(L, "Expecting 2 or 3 arguments to importGFF command"); }

  std::string arg1 = luaL_checkstring(L,1);
  std::string arg2 = luaL_checkstring(L,2);
  if(lua_gettop(L) == 2){
    lua_pushstring(L, rivals::importGFF(arg1, arg2).c_str());
  }else{
    int overwrite = luaL_checkBool(L, 3);
    lua_pushstring(L, rivals::importGFF(arg1, arg2, overwrite).c_str());
  }
  return 1;
}

static int saveAsBED(lua_State * L){
  if(lua_gettop(L) != 1 && lua_gettop(L) != 2){ luaL_error(L, "Expecting 1 or 2 arguments to saveAsBED command"); }
    
  Eval * n = luaL_checkRunner(L, 1);
  if(lua_gettop(L) == 1){
    lua_pushstring(L, SaveAsBED(n).c_str());
  }else{
      std::string filename = luaL_checkstring(L,2);
      lua_pushstring(L, SaveAsBED(filename, n).c_str());
  }
  return 1;
}

static int saveAsRival(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to saveAsRival command"); }
    
  Eval * n = luaL_checkRunner(L, 1);
  std::string basename = luaL_checkstring(L,2);
  lua_pushstring(L, SaveAsRival(basename, n).c_str());
  return 1;
}

static int countIntervals(lua_State * L){
  if(lua_gettop(L) != 1){ luaL_error(L, "Expecting 1 argument to count command"); }
 
  Eval * n = luaL_checkRunner(L, 1);
  lua_pushinteger(L, CountIntervals(n));
  return 1;
}

static int range(lua_State * L){
  if(lua_gettop(L) != 1 && lua_gettop(L) != 2 && lua_gettop(L) != 4){ luaL_error(L, "Expecting 1, 2 or 4 arguments to range command"); }
  
  std::string sample = luaL_checkstring(L, 1);
  if(lua_gettop(L) == 1){
    Eval * n = new Range1(sample);
    lua_pushlightuserdata(L, (void*)n);
    return 1;
  }
  if(lua_gettop(L) == 2){
    std::string chr = luaL_checkstring(L,2);
    Eval * n = new Range2(sample, chr);
    lua_pushlightuserdata(L, (void*)n);
    return 1;
  }
  if(lua_gettop(L) == 4){
    std::string chr = luaL_checkstring(L,2);
    ptrdiff_t start = luaL_checkinteger(L,3);
    ptrdiff_t stop = luaL_checkinteger(L,4);
    Eval * n = new Range4(sample, chr, start, stop);
    lua_pushlightuserdata(L, (void*)n);
    return 1;
  }

  return 0;
}

static int interval(lua_State * L){
  if(lua_gettop(L) != 3){ luaL_error(L, "Expecting 3 arguments to interval command"); }
  
  std::string chr = luaL_checkstring(L,1);
  ptrdiff_t start = luaL_checkinteger(L,2);
  ptrdiff_t stop = luaL_checkinteger(L,3);
  
  Eval * n = new Interval(chr, start, stop);
  lua_pushlightuserdata(L, (void*)n);
  return 1;
}

static int merge(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to merge command"); }
  
  Eval * n = luaL_checkRunner(L, 1);
  Eval * m = luaL_checkRunner(L, 2);
  Eval * mer = new Merge(n, m);
  lua_pushlightuserdata(L, (void*)mer);
  return 1;
}

static int flatten(lua_State * L){
  if(lua_gettop(L) != 1){ luaL_error(L, "Expecting 1 argument to flatten command"); }
    
  Eval * n = luaL_checkRunner(L, 1);
  Eval * flat = new Flatten(n);
  lua_pushlightuserdata(L, (void*)flat);
  return 1;
}

static int clique(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to clique command"); }
 
  Eval * n = luaL_checkRunner(L, 1);
  ptrdiff_t minOverlap = luaL_checkinteger(L,2);
  Eval * cl = new Clique(n, minOverlap);
  lua_pushlightuserdata(L, (void*)cl);
  return 1;
}

static int contained_in(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to contained_in command"); }
  
  Eval * n = luaL_checkRunner(L, 1);
  Eval * m = luaL_checkRunner(L, 2);
  Eval * ci = new Contained_In(n, m);
  lua_pushlightuserdata(L, (void*)ci);
  return 1;
}

static int contains(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to contains command"); }
  
  Eval * n = luaL_checkRunner(L, 1);
  Eval * m = luaL_checkRunner(L, 2);
  Eval * c = new Contains(n, m);
  lua_pushlightuserdata(L, (void*)c);
  return 1;
}

static int overlaps(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to overlaps command"); }
  
  Eval * n = luaL_checkRunner(L, 1);
  Eval * m = luaL_checkRunner(L, 2);
  Eval * ov = new Overlaps(n, m);
  lua_pushlightuserdata(L, (void*)ov);
  return 1;
}

static int get_strand(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to get_strand command"); }
  
  Eval * n = luaL_checkRunner(L, 1);
  int strand = toStrand(luaL_checkstring(L,2));
  Eval * gs = new Get_Strand(n, strand);
  lua_pushlightuserdata(L, (void*)gs);
  return 1;
}

static int set_strand(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to set_strand command"); }
  
  Eval * n = luaL_checkRunner(L, 1);
  int strand = toStrand(luaL_checkstring(L,2));
  Eval * ss = new Set_Strand(n, strand);
  lua_pushlightuserdata(L, (void*)ss);
  return 1;
}

static int score_cutoff(lua_State * L){
  if(lua_gettop(L) != 2){ luaL_error(L, "Expecting 2 arguments to score_cutoff command"); }
  
  Eval * n = luaL_checkRunner(L, 1);
  int thresh = luaL_checkint(L,2);
  Eval * gs = new Score_Cutoff(n, thresh);
  lua_pushlightuserdata(L, (void*)gs);
  return 1;
}

int main(int argc, char *argv[]){
  {
    lua_State *L = lua_open();
    luaL_openlibs(L);

    lua_register(L, "importBED", importBED);
    lua_register(L, "importGFF", importGFF);
    
    lua_register(L, "interval", interval);        
    lua_register(L, "range", range);

    lua_register(L, "merge", merge);
    lua_register(L, "flatten", flatten);
    lua_register(L, "clique", clique);
    lua_register(L, "contained_in", contained_in);
    lua_register(L, "contains", contains);
    lua_register(L, "overlaps", overlaps);
    lua_register(L, "get_strand", get_strand);
    lua_register(L, "set_strand", set_strand);
    lua_register(L, "score_cutoff", score_cutoff);
    
    lua_register(L, "saveAsBED", saveAsBED);
    lua_register(L, "saveAsRival", saveAsRival);
    lua_register(L, "count", countIntervals);

    
    if(luaL_dofile(L, argv[1])!=0) fprintf(stderr,"%s\n",lua_tostring(L,-1));
    lua_close(L);
  }

#ifdef DEBUG
  printLeak();
#endif

  return 0;
}
