#include <stdlib.h>
#include <stdio.h>

#include "listadupla.h"

/* Implementacão de lista Dupla por lista duplamente encadeada */

// 04 - 41
void ListaDupla_Constroi(ListaDupla *L) {
  L->Inicio = NULL;
  L->N = 0;
}

// 04 - 43
void ListaDupla_Destroi(ListaDupla *L) {

  No *p, *pprox;
  pprox = L->Inicio;

  while (pprox != NULL) {
    pprox = p->Prox;
    p = pprox;
    free(p);
  }
}

// 04 - ??
int ListaDupla_Tamanho(ListaDupla *L) {
  return L->N;
}

// 04 - 42
void ListaDupla_Enumera(ListaDupla *L) {
  No *p;
  p = L->Inicio;

  while(p != NULL) {
    printf("%d %d\n", p->Chave, p->Elem->val);
    p = p->Prox;
  }
}


// 04 - 44
TElem* ListaDupla_Busca_NaoOrdenada(ListaDupla *L, TChave c) {

  No *p;
  
  p = L->Inicio;

  while ( p != NULL && p->Chave != c ) 
    p = p->Prox;
  
  if ( p != NULL ) 
    return (p->Elem);
  else
    // ("NULO")
    return NULL;
}

// 04-47
TElem* ListaDupla_Busca_Ordenada(ListaDupla *L, TChave c, No *noAnt) {

  No *p = L->Inicio;
  noAnt = NULL;

  while ( p != NULL && p->Chave < c ) {
    p = p->Prox;
    noAnt = p;
  }

  if ( p != NULL && p->Chave == c ) 
    return p->Elem;
  else
    // ("NULO")
    return NULL;

}

// 04 - 45
TElem* ListaDupla_BuscaEm(ListaDupla *L, int Pos) {
  No *p = L->Inicio;

  int i;
  for(i=2; i< Pos; i++) 
    p = p->Prox;

  return p->Elem;
}


// 04 - 48
void ListaDupla_Insere_NaoOrdenada(ListaDupla *L, TChave c, TElem *x) {
  No *Novo;

  Novo = malloc(sizeof *Novo);

  Novo->Chave = c;
  Novo->Elem = x;
  Novo->Prev = NULL;
  Novo->Prox = L->Inicio;
  L->Inicio->Prev = Novo;
  L->Inicio = Novo;
  L->N += 1;
}

// 04 - 49
void ListaDupla_InsereEm(ListaDupla *L, int Pos, TChave c, TElem *x) {

  No *p = L->Inicio;

  No *Novo;
  Novo = malloc (sizeof *Novo);

  Novo->Chave = c;
  Novo->Elem = x;

  if (Pos == 1) {
    Novo->Prox = L->Inicio;
    Novo->Prox->Prev = Novo;
    L->Inicio = Novo;
  } else {
    p = L->Inicio;

    int i;
    for (i = 0; i< Pos-1; i++)
      p = p->Prox;

    p->Prev->Prox = Novo;
    Novo->Prev = p->Prev;
    Novo->Prox = p;
    p->Prev = Novo;
  }
  L->N += 1;
}

// 04-50
void ListaDupla_Insere_Ordenada(ListaDupla *L, TChave c, TElem *x) {

  No *noAnt;
  No *Novo;
  TElem *v;

  v = ListaDupla_Busca_Ordenada(L, c, noAnt);

  // ("NULO")
  if (v == NULL) {
    Novo = malloc(sizeof *Novo); 
    Novo->Chave = c;
    Novo->Elem = x;

    if (noAnt == NULL) {
      Novo->Prox = L->Inicio;
      Novo->Prox->Prev = Novo;
      L->Inicio = Novo;
    } else {
      Novo->Prox = noAnt->Prox;
      noAnt->Prox = Novo;
      Novo->Prev = noAnt;
    }
    L->N += 1;
  } else {
    printf("Chave Existente");
  }
}

TElem* ListaDupla_Remove(ListaDupla *L, TChave c) {
  No *p;
  No *noAnt;
  TElem *x;

  x = ListaDupla_Busca_Ordenada(L, c, noAnt);

  // ("NULO")
  if (x != NULL) {
    if ( noAnt == NULL ) {
      L->Inicio = L->Inicio->Prox;
      L->Inicio->Prev = NULL;
      p = L->Inicio;
    } else {
      p = noAnt->Prox;
      noAnt->Prox = noAnt->Prox->Prox;
      noAnt->Prox->Prev = noAnt;
    }
    free(p);
    L->N -= 1;
    return (x);
  } else {
    printf("Chave inexistente");
    /* ("NULO") */
    return NULL;
  }
}

TElem* ListaDupla_RemoveEm(ListaDupla *L, int Pos) {
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

  // ("NULO")
  if (x != NULL) {
    if ( noAnt == NULL ) {
      L->Inicio = L->Inicio->Prox;
      L->Inicio->Prev = NULL;
      p = L->Inicio;
    } else {
      p = noAnt->Prox;
      noAnt->Prox = noAnt->Prox->Prox;
      noAnt->Prox->Prev = noAnt;
    }
    free(p);
    L->N -= 1;
    return (x);
  } else {
    printf("Chave inexistente");
    /* ("NULO") */
    return NULL;
  }
}

