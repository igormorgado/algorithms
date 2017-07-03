#ifndef NOARV_H_
#define NOARV_H_

#include "elem.h"

typedef struct noArv noArv;
struct noArv {
  TChave chave;
  TElem *elem;
  noArv *esq;
  noArv *dir;
};


/* Executa percurso a partir do elemento x */
void noArv_PercursoInOrdem (struct noArv *x);
void noArv_PercursoPreOrdem(struct noArv *x);
void noArv_PercursoPosOrdem(struct noArv *x);

#endif
