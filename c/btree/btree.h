#ifndef _BTREE_H
#define _BTREE_H

#include "node.h"

/* Tree*/
struct Tree {
  int height;
  struct Node *root;
};

/* Tree */
void            newTree           (struct Tree **T);  // 08-20
void            destroyTree       (struct Tree **T);
void            printNode         (struct Node *N);                                                                                                 
void            walkTreePre       (struct Node *root);   // 08-31
void            walkTreePos       (struct Node *root);   // 08-33
void            walkTreeIn        (struct Node *root);   // 08-35
void            walkTreeLevel     (struct Node *root);   // 08-37
void            insertNode        (struct Tree *T, struct Node *node);
int             sizeTree          (struct Node *root); 

void            walkTreeLevelLL   (struct Node *root); // 08-37
void            insertNodeLL      (struct Tree *T, struct Node *node);

// Exercicicio 1
void            atualizaAltura       (struct Node *root);
void            atualizaNivel        (struct Node *root);
void            atualizaSomaChaveD   (struct Node *root);
void            atualizaSomaChaveD2  (struct Node *root);
void            atualizaSomaChaveD2c (struct Node *root);
void            atualizaSomaChaveA   (struct Node *root);
void            atualizaSomaChaveA2  (struct Node *root);
void            atualizaPNivel       (struct Node *root);

// Exercicio 2
void            walkTreeLevelR       (struct Node *root); 


// Exercicio 3
int             compareTree          (struct Node *roota, struct Node *rootb); 

// Exercicio 6.c
int eFolha(struct Node *node);
int somaFolha(struct Node *node);

#endif
