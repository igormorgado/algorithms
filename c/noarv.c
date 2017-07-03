#include <stdio.h>

#include "noarv.h"

void noArv_PercursoInOrdem(noArv *x)
{
  if(x) {
    noArv_PercursoInOrdem(x->esq);

    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);

    noArv_PercursoInOrdem(x->dir);
  }
  printf("\n");
}

void noArv_PercursoPreOrdem(noArv *x)
{
  if(x) {
    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);

    noArv_PercursoPreOrdem(x->esq);
    noArv_PercursoPreOrdem(x->dir);
  }
  printf("\n");
}

void noArv_PercursoPosOrdem(noArv *x)
{
  if(x) {
    noArv_PercursoPosOrdem(x->esq);
    noArv_PercursoPosOrdem(x->dir);

    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);
  }
  printf("\n");
}

