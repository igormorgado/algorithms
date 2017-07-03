#ifndef _ELEM_H_
#define _ELEM_H_

#include <stdbool.h>

typedef int TChave;

// ?? - ??
typedef struct TElem TElem;
struct TElem {
  bool status;
  int val;
};

struct TElem* elem_Novo(int val);

struct TElem* elem_Nulo(void);

#define E_ELEM_NULO(elem)       (((elem)->status == false)?true:false)

#define ELEMNULO  elem_Nulo()

#endif
