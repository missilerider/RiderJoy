#pragma once

// Comentar la siguiente línea para que no se escriba sobre Serial1 nada (producción)
//#define DEBUG

#ifdef DEBUG
  #define pln(x) Serial1.println(x);
  #define p(x) Serial1.print(x);
  #define pbit(x) Serial1.print((uint32_t)x, BIN);
  #define pbitln(x) Serial1.println((uint32_t)x, BIN);
#else
  #define p(x) ;
  #define pln(x) ;
  #define pbit(x) ;
  #define pbitln(x) ;
  #define pbit64ln(x) ;
#endif
