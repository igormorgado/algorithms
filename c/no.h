#ifndef NO_H_
#define NO_H_

#include "elem.h"

// 04 - 41
typedef struct No No;
struct No {
  TChave Chave;
  TElem *Elem;
  No *Prox;
  No *Prev;
};

#endif

