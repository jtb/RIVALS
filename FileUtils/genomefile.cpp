#include "genomefile.h"

bool checkLine(std::string & line){
  if(line.empty() || line[0] == '#') return false;
  return true;
}
bool checkChr(std::string & chr){
  if(chr.empty()) return false;
  return true;
}
bool checkPos(std::string & s){
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
  return true;
}
