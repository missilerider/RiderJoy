#pragma once

// Comentar la siguiente línea para que no se escriba sobre Serial1 nada (producción)
#define DEBUG

#ifdef DEBUG
  #define pln(x) Serial1.println(x);
  #define p(x) Serial1.print(x);
#else
  #define p(x) ;
  #define pln(x) ;
#endif
