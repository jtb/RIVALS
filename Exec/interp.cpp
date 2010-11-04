#include <iostream>
#include <string>
#include <stack>

#include "eval.h"

#ifdef DEBUG
#include "mem.h"
#endif

#include "lua.hpp"

static int importBED(lua_State * L){
  std::string arg1 = lua_tostring(L,1);
  std::string arg2 = lua_tostring(L,2);
  rivals::importBED(arg1, arg2);
  return 0;
}
static int importGFF(lua_State * L){
  std::string arg1 = lua_tostring(L,1);
  std::string arg2 = lua_tostring(L,2);
  //std::cout << "importGFF(" << arg1 << " , " << arg2 << ")" << std::endl;
  rivals::importGFF(arg1, arg2);
  return 0;
}

static int saveAsBED(lua_State * L){
  if(lua_gettop(L)){
    if(lua_gettop(L) < 2){
      Eval * n = (Eval *)lua_touserdata(L, 1);
      lua_pushstring(L, SaveAsBED(n).c_str());
      return 1;
    }else{
      std::string filename = lua_tostring(L,1);
      Eval * n = (Eval *)lua_touserdata(L,2);
      lua_pushstring(L, SaveAsBED(filename, n).c_str());
      return 1;
    }
  }
  return 0;
}

static int saveAsRival(lua_State * L){
  if(lua_gettop(L)){
    std::string basename = lua_tostring(L,1);
    Eval * n = (Eval *)lua_touserdata(L,2);
    lua_pushstring(L, SaveAsRival(basename, n).c_str());
    return 1;
  }
  return 0;
}

static int countIntervals(lua_State * L){
  if(lua_gettop(L)){
    Eval * n = (Eval *)lua_touserdata(L,1);
    lua_pushinteger(L, CountIntervals(n));
    return 1;
  }
  return 0;
}

static int range(lua_State * L){
  if(lua_gettop(L) == 1){
    std::string sample = lua_tostring(L,1);
    Eval * n = new Range1(sample);
    lua_pushlightuserdata(L, (void*)n);
    return 1;
  }
  if(lua_gettop(L) == 2){
    std::string sample = lua_tostring(L,1);
    std::string chr = lua_tostring(L,2);
    Eval * n = new Range2(sample, chr);
    lua_pushlightuserdata(L, (void*)n);
    return 1;
  }
  if(lua_gettop(L) == 4){
    std::string sample = lua_tostring(L,1);
    std::string chr = lua_tostring(L,2);
    ptrdiff_t start = lua_tointeger(L,3);
    ptrdiff_t stop = lua_tointeger(L,4);
    Eval * n = new Range4(sample, chr, start, stop);
    lua_pushlightuserdata(L, (void*)n);
    return 1;
  }
   
  return 0;
}

static int interval(lua_State * L){
  std::string chr = lua_tostring(L,1);
  ptrdiff_t start = lua_tointeger(L,2);
  ptrdiff_t stop = lua_tointeger(L,3);
  
  Eval * n = new Interval(chr, start, stop);
  lua_pushlightuserdata(L, (void*)n);
  return 1;
}

static int merge(lua_State * L){
  Eval *n = (Eval *)lua_touserdata(L,1);
  Eval *m = (Eval *)lua_touserdata(L,2);
  Eval * mer = new Merge(n, m);
  lua_pushlightuserdata(L, (void*)mer);

  return 1;
}

int main(int argc, char *argv[]){
  {
    lua_State *L = lua_open();
    luaL_openlibs(L);

    lua_register(L, "importBED", importBED);
    lua_register(L, "importGFF", importGFF);
    lua_register(L, "saveAsBED", saveAsBED);
    lua_register(L, "saveAsRival", saveAsRival);
    lua_register(L, "count", countIntervals);
    lua_register(L, "range", range);
    lua_register(L, "interval", interval);
    lua_register(L, "merge", merge);
    
    if(luaL_dofile(L, argv[1])!=0) fprintf(stderr,"%s\n",lua_tostring(L,-1));

    lua_close(L);
  }

#ifdef DEBUG
  printLeak();
#endif

  return 0;
}
