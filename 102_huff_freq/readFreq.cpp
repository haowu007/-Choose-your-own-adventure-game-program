#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream Myfile(fname, std::ifstream::in);
  uint64_t * ans = new uint64_t[257];
  for (size_t i = 0; i < 257; i++) {
    ans[i] = 0;
  }
  char c;
  while (Myfile.get(c)) {
    size_t i = (size_t)c;
    ans[i]++;
  }
  ans[256] = 1;
  Myfile.close();
  return ans;
}
