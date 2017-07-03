#include <stdlib.h>
#include <stdio.h>

#include "listalinear.h"

/* Implementacão de lista Linear por lista duplamente encadeada */

// 04 - 41
void ListLinear_Constroi(ListaLinear *L) {
  L->Inicio = NULL;
  L->N = 0;
}

// 04 - 43
void ListaLinear_Destroi(ListaLinear *L) {

  No *p, *pprox;
  pprox = L->Inicio;

  while (pprox != NULL) {
    pprox = p->Prox;
    p = pprox;
    free(p);
  }
}

// 04 - ??
int ListaLinear_Tamanho(ListaLinear *L) {
  return L->N;
}

// 04 - 42
void ListaLinear_Enumera(ListaLinear *L) {
  No *p;
  p = L->Inicio;

  while(p != NULL) {
    printf("%d %d\n", p->Chave, p->Elem->val);
    p = p->Prox;
  }
}


// 04 - 44
TElem* ListaLinear_Busca_NaoOrdenada(ListaLinear *L, TChave c) {

  No *p;
  
  p = L->Inicio;

  while ( p != NULL && p->Chave != c ) 
    p = p->Prox;
  
  if ( p != NULL ) 
    return (p->Elem);
  else
    return ELEMNULO;
}

// 04-47
TElem* ListaLinear_Busca_Ordenada(ListaLinear *L, TChave c, No *noAnt) {

  No *p = L->Inicio;
  noAnt = NULL;

  while ( p != NULL && p->Chave < c ) {
    p = p->Prox;
    noAnt = p;
  }

  if ( p != NULL && p->Chave == c ) 
    return p->Elem;
  else
    return ELEMNULO;

}

// 04 - 45
TElem* ListaLinear_BuscaEm(ListaLinear *L, int Pos) {
  No *p = L->Inicio;

  int i;
  for(i=2; i< Pos; i++) 
    p = p->Prox;

  return p->Elem;
}


// 04 - 48
void ListaLinear_Insere_NaoOrdenada(ListaLinear *L, TChave c, TElem *x) {
  No *Novo;

  Novo = malloc(sizeof *Novo);

  Novo->Chave = c;
  Novo->Elem = x;
  Novo->Prox = L->Inicio;
  L->Inicio = Novo;
  L->N += 1;
}

// 04 - 49
void ListaLinear_InsereEm(ListaLinear *L, int Pos, TChave c, TElem *x) {

  No *p = L->Inicio;

  No *Novo;
  Novo = malloc (sizeof *Novo);

  Novo->Chave = c;
  Novo->Elem = x;

  if (Pos == 1) {
    Novo->Prox = L->Inicio;
    L->Inicio = Novo;
  } else {
    p = L->Inicio;

    int i;
    for (i = 0; i< Pos-1; i++)
      p = p->Prox;

    Novo->Prox = p->Prox;
    p->Prox = Novo;
  }
  L->N += 1;
}

// 04-50
void ListaLinear_Insere_Ordenada(ListaLinear *L, TChave c, TElem *x) {

  No *noAnt;
  No *Novo;
  TElem *v;

  v = ListaLinear_Busca_Ordenada(L, c, noAnt);

  if (E_ELEM_NULO(v)) {
    Novo = malloc(sizeof *Novo); 
    Novo->Chave = c;
    Novo->Elem = x;

    if (noAnt == NULL) {
      Novo->Prox = L->Inicio;
      L->Inicio = Novo;
    } else {
      Novo->Prox = noAnt->Prox;
      noAnt->Prox = Novo;
    }
    L->N += 1;
  } else {
    printf("Chave Existente");
  }
}

TElem* ListaLinear_Remove(ListaLinear *L, TChave c) {
  No *p;
  No *noAnt;
  TElem *x;

  x = ListaLinear_Busca_Ordenada(L, c, noAnt);

  if (! E_ELEM_NULO(x)) {
    if ( noAnt == NULL ) {
      L->Inicio = L->Inicio->Prox;
      p = L->Inicio;
    } else {
      p = noAnt->Prox;
      noAnt->Prox = noAnt->Prox->Prox;
    }
    free(p);
    L->N -= 1;
    return (x);
  } else {
    printf("Chave inexistente");
    return ELEMNULO;
  }
}

TElem* ListaLinear_RemoveEm(ListaLinear *L, int Pos) {
  No *p;
  No *noAnt;
  TElem *x;

  if (Pos == 1) {
    noAnt = NULL;
    x = L->Inicio->Elem;
  } else {
    noAnt = L->Inicio;
    int i;
    for(i=1; i<Pos-2; i++) {
      noAnt = noAnt->Prox;
    }
    x = noAnt->Prox->Elem;
  }

  if (! E_ELEM_NULO(x)) {
    if ( noAnt == NULL ) {
      L->Inicio = L->Inicio->Prox;
      p = L->Inicio;
    } else {
      p = noAnt->Prox;
      noAnt->Prox = noAnt->Prox->Prox;
    }
    free(p);
    L->N -= 1;
    return (x);
  } else {
    printf("Chave inexistente");
    return ELEMNULO;
  }
}

