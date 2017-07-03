#include <stdlib.h>

#include "elem.h"
#include "no.h"
#include "abb.h"

int main(void) {

  abb *T;
  T = malloc(sizeof *T);
  T->raiz = NULL;

  
  TElem *x = elem_Novo(10);

  TChave c = 1;
  abb_Insere(T, c, x);
  abb_Remove(T, c);

  free(T);

  return 0;
}
