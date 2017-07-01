#include <stdlib.h>
#include <stdio.h>

/* **********************************************
 * BEGIN: elem.h
 ********************************************* */

struct TElem {
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

struct No {
  TChave chave;
  struct TElem *elem;
  struct No *esq;
  struct No *dir;
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

struct abb {
  struct No *raiz;
};

/* Constroi arvore */
void abb_Constroi(struct abb *T);

/* Enumera(LISTA) cada chave de T ordenadamente */
void abb_Enumera(struct abb *T);

/* Obetem o elemento de T com chave c ou NULO se inexistente */
struct TElem* abb_Busca(struct abb *T, TChave c);

struct TElem* abb_BuscaPos(struct abb *T, TChave c, struct No **PosIns);

/* Insere Elemento x com chave c em T */
void abb_Insere(struct abb *T, TChave c, struct TElem *x);

/* Remove e retorna o elemento de T com chave c */
struct TElem* abb_Remove(struct abb *T, TChave c);

/* Executa percurso a partir da raiz de T */
void abb_PercursoInOrdem (struct abb *T);
void abb_PercursoPreOrdem(struct abb *T);
void abb_PercursoPosOrdem(struct abb *T);


/* **********************************************
 * END: abb.h
 ********************************************* */



/* **********************************************
 * BEGIN: elem.c
 ********************************************* */

struct TElem* elem_Novo(int val)
{
  struct TElem *x;

  x = malloc(sizeof *x);
  x->val = val;

  return x;
}

/* **********************************************
 * END: elem.c
 ********************************************* */



/* **********************************************
 * BEGIN: no.c
 ********************************************* */

void no_PercursoInOrdem(struct No *x)
{
  if(x) {
    no_PercursoInOrdem(x->esq);

    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);

    no_PercursoInOrdem(x->dir);
  }
  printf("\n");
}

void no_PercursoPreOrdem(struct No *x)
{
  if(x) {
    printf("(%d) ", x->chave);
    if (x->elem) printf("%d ", x->elem->val);

    no_PercursoPreOrdem(x->esq);
    no_PercursoPreOrdem(x->dir);
  }
  printf("\n");
}

void no_PercursoPosOrdem(struct No *x)
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

void abb_Enumera(struct abb *T)
{
  if(T->raiz)
    no_PercursoInOrdem(T->raiz);
}

struct TElem* abb_Busca(struct abb *T, TChave c)
{
  struct No *q = T->raiz;
  while (q)
    if ((q->chave = c))
      return q->elem;
    else if ( c < q->chave)
      q = q->esq;
    else
      q = q->dir;

  return NULL;
}


struct TElem* abb_BuscaPos(struct abb *T, TChave c, struct No **posins)
{
  struct No *q = T->raiz;
  posins = &(T->raiz);

  while (q)
    if ((q->chave == c))
      return q->elem;
    else if ( c < q->chave) {
      q = q->esq;
      posins = &(q->esq);
    } else {
      q = q->dir;
      posins = &(q->dir);
    }

  return NULL;
}

void abb_Insere(struct abb *T, TChave c, struct TElem *x)
{
  struct No **posins;
  struct No *q;
  struct TElem *v;
  
  posins = malloc(sizeof *posins);
  v = abb_BuscaPos(T, c, posins);

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

struct TElem* abb_Remove(struct abb *T, TChave c)
{
  struct No *q;
  struct No **pontq;
  struct TElem *x;

  pontq = malloc(sizeof *pontq);
  x = abb_BuscaPos(T, c, pontq);

  if (x) {
    q = *pontq;

    if (q->esq) {
      if(! q->esq->dir) {
        q->esq->dir = q->dir;
        *pontq = q->esq;
      } else {
        struct No *qmenor = q->esq->dir;
        struct No *paiqmenor = q->esq;
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

  struct abb *T;
  T = malloc(sizeof *T);
  T->raiz = NULL;

  
  struct TElem *x = elem_Novo(10);

  TChave c = 1;
  abb_Insere(T, c, x);
  abb_Remove(T, c);

  free(T);

  return 0;
}
