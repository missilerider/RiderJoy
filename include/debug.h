#pragma once

//#define DEBUG

#ifdef DEBUG
  #define pln(x) Serial1.println(x);
  #define p(x) Serial1.print(x);
#else
  #define p(x) ;
  #define pln(x) ;
#endif
