#include <stdlib.h>

#include "elem.h"

TElem* elem_Nulo(void)
{
  TElem *x;

  x = malloc(sizeof *x);
  x->val = 0;
  x->status = false;

  return x;
}


TElem* elem_Novo(int val)
{
  TElem *x;

  x = malloc(sizeof *x);
  x->val = val;
  x->status = true;

  return x;
}

