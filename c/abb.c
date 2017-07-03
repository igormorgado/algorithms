#include <stdlib.h>
#include <stdio.h>

#include "abb.h"

void abb_Enumera(abb *T)
{
  if(T->raiz)
    noArv_PercursoInOrdem(T->raiz);
}

TElem* abb_Busca_(abb *T, TChave c)
{
  noArv *q = T->raiz;
  while (q)
    if ((q->chave = c))
      return q->elem;
    else if ( c < q->chave)
      q = q->esq;
    else
      q = q->dir;

  return NULL;
}


TElem* abb_Busca(abb *T, TChave c, noArv **posins)
{
  noArv *q = T->raiz;
  posins = &(T->raiz);

  while (q) {
    if ((q->chave == c))
      return q->elem;
    else if ( c < q->chave) {
      q = q->esq;
      posins = &(q->esq);
    } else {
      q = q->dir;
      posins = &(q->dir);
    }
  }

  return NULL;
}

void abb_Insere(abb *T, TChave c, TElem *x)
{
  noArv **posins;
  noArv *q;
  TElem *v;
  
  posins = malloc(sizeof *posins);
  v = abb_Busca(T, c, posins);

  if (!v) {
    q = malloc(sizeof *q);
    q->chave = c;
    q->elem  = x;
    q->esq   = NULL;
    q->dir   = NULL;
    *posins  = q;
  } else {
    printf("Chave existente %d\n", c);
  }

  free(posins);
}

TElem* abb_Remove(abb *T, TChave c)
{
  noArv *q;
  noArv **pontq;
  TElem *x;

  pontq = malloc(sizeof *pontq);
  x = abb_Busca(T, c, pontq);

  if (x) {
    q = *pontq;

    if (q->esq) {
      if(! q->esq->dir) {
        q->esq->dir = q->dir;
        *pontq = q->esq;
      } else {
        noArv *qmenor = q->esq->dir;
        noArv *paiqmenor = q->esq;
        while(qmenor->dir) {
          qmenor = qmenor->dir;
          paiqmenor = qmenor;
          paiqmenor->dir = qmenor->esq;
          qmenor->esq = q->esq;
          qmenor->dir = q->dir;
          *pontq = qmenor;
        }
      }
    } else {
      *pontq = q->dir;
    }
    free(q);
    free(pontq);
    return x;
  } else {
    printf("Chave inexistente %d\n", c);
    free(pontq);
    return NULL;
  }
}

