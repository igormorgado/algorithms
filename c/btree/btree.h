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

#endif
