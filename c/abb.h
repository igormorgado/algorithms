#ifndef _ABB_H_
#define _ABB_H_

#include "noarv.h"

typedef struct abb abb;
struct abb {
  noArv *raiz;
};


/* Constroi arvore */
void abb_Constroi(abb *T);

/* Enumera(LISTA) cada chave de T ordenadamente */
void abb_Enumera(abb *T);

/* Obetem o elemento de T com chave c ou NULO se inexistente */
TElem* abb_Busca_(abb *T, TChave c);

TElem* abb_Busca(abb *T, TChave c, noArv **PosIns);

/* Insere Elemento x com chave c em T */
void abb_Insere(abb *T, TChave c, TElem *x);

/* Remove e retorna o elemento de T com chave c */
TElem* abb_Remove(abb *T, TChave c);

/* Executa percurso a partir da raiz de T */
void abb_PercursoInOrdem (abb *T);
void abb_PercursoPreOrdem(abb *T);
void abb_PercursoPosOrdem(abb *T);

#endif
