#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* **********************************************
 * BEGIN: elem.h
 ********************************************* */

typedef struct TElem TElem;
struct TElem {
  bool status;
  int val;
};


/* Cria um novo TElem e atribui um valor a ele */
struct TElem* elem_Novo(int val);

/* **********************************************
 * END: elem.h
 ********************************************* */



/* **********************************************
 * BEGIN: no.h
 ********************************************* */

typedef int TChave;

typedef struct No No;
struct No {
  TChave chave;
  TElem *elem;
  No *esq;
  No *dir;
};


/* Executa percurso a partir do elemento x */
void no_PercursoInOrdem (struct No *x);
void no_PercursoPreOrdem(struct No *x);
void no_PercursoPosOrdem(struct No *x);


/* **********************************************
 * END: no.h
 ********************************************* */



/* **********************************************
 * BEGIN: abb.h
 ********************************************* */

typedef struct abb abb;
struct abb {
  No *raiz;
};


/* Constroi arvore */
void abb_Constroi(abb *T);

/* Enumera(LISTA) cada chave de T ordenadamente */
void abb_Enumera(abb *T);

/* Obetem o elemento de T com chave c ou NULO se inexistente */
TElem* abb_Busca_(abb *T, TChave c);

TElem* abb_Busca(abb *T, TChave c, No **PosIns);

/* Insere Elemento x com chave c em T */
void abb_Insere(abb *T, TChave c, TElem *x);

/* Remove e retorna o elemento de T com chave c */
TElem* abb_Remove(abb *T, TChave c);

/* Executa percurso a partir da raiz de T */
void abb_PercursoInOrdem (abb *T);
void abb_PercursoPreOrdem(abb *T);
void abb_PercursoPosOrdem(abb *T);


/* **********************************************
 * END: abb.h
 ********************************************* */



/* **********************************************
 * BEGIN: elem.c
 ********************************************* */

TElem* elem_Novo(int val)
{
  TElem *x;

  x = malloc(sizeof *x);
  x->val = val;
  x->status = true;

  return x;
}

/* **********************************************
 * END: elem.c
 ********************************************* */



/* **********************************************
 * BEGIN: no.c
 ********************************************* */

void no_PercursoInOrdem(No *x)
{
  if(x) {
    no_PercursoInOrdem(x->esq);

    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);

    no_PercursoInOrdem(x->dir);
  }
  printf("\n");
}

void no_PercursoPreOrdem(No *x)
{
  if(x) {
    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);

    no_PercursoPreOrdem(x->esq);
    no_PercursoPreOrdem(x->dir);
  }
  printf("\n");
}

void no_PercursoPosOrdem(No *x)
{
  if(x) {
    no_PercursoPosOrdem(x->esq);
    no_PercursoPosOrdem(x->dir);

    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);
  }
  printf("\n");
}

/* **********************************************
 * END: no.c
 ********************************************* */



/* **********************************************
 * BEGIN: abb.c
 ********************************************* */

void abb_Enumera(abb *T)
{
  if(T->raiz)
    no_PercursoInOrdem(T->raiz);
}

TElem* abb_Busca_(abb *T, TChave c)
{
  No *q = T->raiz;
  while (q)
    if ((q->chave = c))
      return q->elem;
    else if ( c < q->chave)
      q = q->esq;
    else
      q = q->dir;

  return NULL;
}


TElem* abb_Busca(abb *T, TChave c, No **posins)
{
  No *q = T->raiz;
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
  No **posins;
  No *q;
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
  No *q;
  No **pontq;
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
        No *qmenor = q->esq->dir;
        No *paiqmenor = q->esq;
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

/* **********************************************
 * END: abb.c
 ********************************************* */

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
