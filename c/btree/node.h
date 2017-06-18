#ifndef NODE_H_
#define NODE_H_


/* Node sequential */
struct Node {
  int          val;
  int          Altura;
  int          Nivel;
  int          SomaChaveD;
  int          SomaChaveD2;
  int          SomaChaveA;
  int          SomaChaveA2;
  float        PNivel;
  struct Node *left;
  struct Node *right;
  struct Node *parent;
};

/* Node Linked List */
struct NodeLL {
  struct Node *node;
  struct NodeLL *next;
};

struct Node*    newNode           (int val);         // 08-20
void            destroyNode       (struct Node *root);
void            destroyNodeByRef  (struct Node **node);

void            printNode         (struct Node *N); 

#endif

