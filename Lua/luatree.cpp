#include <iostream>
#include <string>
#include <stack>

#include "eval.h"
//#include "mem.h"

extern "C" {
#include "includes/lua.h"
#include "includes/lualib.h"
#include "includes/lauxlib.h"
}

std::stack<Eval *> evals;

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
  if(!evals.empty()){
    Eval * n = evals.top();
    evals.pop();
    if(lua_gettop(L) < 2){
      lua_tonumber(L, 1);
      lua_pushstring(L, SaveAsBED(n).c_str());
      return 1;
    }else{
      std::string filename = lua_tostring(L,1);
      lua_tonumber(L,2);
      lua_pushstring(L, SaveAsBED(filename, n).c_str());
      return 1;
    }
  }
  
  return 0;
}
static int saveAsRival(lua_State * L){
  if(!evals.empty()){
    Eval * n = evals.top();
    evals.pop();
    
    std::string basename = lua_tostring(L,1);
    lua_tonumber(L,2);
    lua_pushstring(L, SaveAsRival(basename, n).c_str());
    return 1;
  }
  return 0;
}

static int range(lua_State * L){
  std::string sample = lua_tostring(L,1);
  evals.push(new Range(sample));
  lua_pushnumber(L, 0);//placeholder
  return 1;
}

static int interval(lua_State * L){
  std::string chr = lua_tostring(L,1);
  ptrdiff_t start = lua_tointeger(L,2);
  ptrdiff_t stop = lua_tointeger(L,3);
  
  evals.push(new Interval(chr, start, stop));
  lua_pushnumber(L, 0);//placeholder
  return 1;
}

static int merge(lua_State * L){
  Eval *n = evals.top();
  evals.pop();
  Eval *m = evals.top();
  evals.pop();
  lua_tonumber(L,1);
  lua_tonumber(L,2);
  evals.push(new Merge(n, m));
  lua_pushnumber(L, 0);//placeholder
  return 1;
}

int main(){
  {
    lua_State *L = lua_open();

    lua_register(L, "importBED", importBED);
    lua_register(L, "importGFF", importGFF);
    lua_register(L, "saveAsBED", saveAsBED);
    lua_register(L, "saveAsRival", saveAsRival);
    lua_register(L, "range", range);
    lua_register(L, "interval", interval);
    lua_register(L, "merge", merge);
    
    luaL_dofile(L, "test.lua");
    
    lua_close(L);
  }
  //printLeak();
  return 0;
}
