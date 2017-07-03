#include <stdlib.h>
#include <stdio.h>

#include "elem.h"
#include "no.h"
#include "abb.h"

TElem* cria_nulo(void) {
  return ELEMNULO;
}

int main(void) {

  abb *T;
  T = malloc(sizeof *T);
  T->raiz = NULL;

  
  TElem *x = elem_Novo(10);
  TElem *NULO = ELEMNULO;

  
  if (E_ELEM_NULO(NULO))
    printf("NULO é nulo\n");
  else
    printf("NULO nao é nulo\n");

  if (E_ELEM_NULO(x))
    printf("x é nulo\n");
  else
    printf("x nao é nulo\n");

  if (E_ELEM_NULO(cria_nulo()))
    printf("cria é nulo\n");
  else
    printf("cria nao é nulo\n");


  TChave c = 1;
  abb_Insere(T, c, x);
  abb_Remove(T, c);


  free(T);

  return 0;
}
