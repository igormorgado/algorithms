#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#include "node.h"
#include "btree.h"
#include "queue.h"
#include "queuell.h"



void newTree(struct Tree **T) 
{
  (*T)         = malloc(sizeof *(*T));
  (*T)->root   = NULL;
  (*T)->height = 0;
}


void destroyTree(struct Tree **T)
{
  destroyNodeByRef(&((*T)->root));
  free(*T);
  *T = NULL;
}


void walkTreePre(struct Node *root) 
{
  if (root) {
    printNode(root);
    walkTreePre(root->left);
    walkTreePre(root->right);
  }
}


void walkTreePos(struct Node *root) 
{
  if (root) {
    walkTreePos(root->left);
    walkTreePos(root->right);
    printNode(root);
  }
}


void walkTreeIn(struct Node *root) 
{
  if (root) {
    walkTreeIn(root->left);
    printNode(root);
    walkTreeIn(root->right);
  }
}


void walkTreeLevel(struct Node *root) 
{
  struct Queue *queue;
  queue = newQueue(MAXQUEUESIZE);

  if(root) enqueue(queue, root);

  while (! isQueueEmpty(queue)) {
    struct Node *next = dequeue(queue);

    if (next) {
      printNode(next);

      if (next->left)  enqueue(queue, next->left);
      if (next->right) enqueue(queue, next->right);
    }
  }
  destroyQueue(queue);
}

void walkTreeLevelR(struct Node *root) 
{
  struct Queue *queue;
  queue = newQueue(MAXQUEUESIZE);

  if(root) enqueue(queue, root);

  while (! isQueueEmpty(queue)) {
    struct Node *next = dequeue(queue);

    if (next) {
      printNode(next);

      if (next->right) enqueue(queue, next->right);
      if (next->left)  enqueue(queue, next->left);
    }
  }
  destroyQueue(queue);
}

void walkTreeLevelLL(struct Node *root) 
{

  struct QueueLL *queue;
  queue = newQueueLL();

  enqueueLL(queue, root);

  while (! isQueueEmptyLL(queue)) {
    struct Node *next = dequeueLL(queue);

    if (next) {
      printNode(next);
      if (next->left)  enqueueLL(queue, next->left);
      if (next->right) enqueueLL(queue, next->right);
    }
  }
  destroyQueueLL(queue);
  queue = NULL;
}


int sizeTree(struct Node *root) 
{
  if (root)
    return sizeTree(root->left) + 1 + sizeTree(root->right);
  else
    return 0;
}


/* Insert *node, inside the tree with root *root
 * always trying to minimize the height keeping
 * the tree complete.
 */
void insertNode(struct Tree *T, struct Node *node) 
{
  if (!T->root) {
    /* If the tree is empty, work almost done! Just assign it */
    T->root = node;
  } else {
    /* Otherwise, we need to find the right place QUEUE will come to a hand */

    /* Start the queue and put the tree root at top of it */
    struct Queue *queue;
    queue = newQueue(MAXQUEUESIZE);
    enqueue(queue, T->root);

    /* Looking for the right place */
    struct Node *t;
    while((t = dequeue(queue))) {

      /* If the left side is empty, we found the spot */
      if (!t->left) {
        t->left = node;
        t->left->parent = t;
        break;
      } else {
        /* Otherwise, let's queue the left side for evaluation */
        enqueue(queue, t->left);
      }

      /* If the right side is empty, we do not care about the queue above */
      if (!t->right) {
        t->right = node;
        t->right->parent = t;
        break;
      } else {
        /* The right side has something, let's look further */
        enqueue(queue, t->right);
      }
    }
    destroyQueue(queue);
  }
}


/* insertNodeLL:
 * Insert *node, inside the tree with root *root
 * always trying to minimize the height keeping
 * the tree complete.
 */
void insertNodeLL(struct Tree *T, struct Node *node) 
{
  if (!T->root) {
    /* If the tree is empty, work almost done! Just assign it */
    T->root = node;
  } else {
    /* Otherwise, we need to find the right place QUEUE will come to a hand */

    /* Start the queue and put the tree root at top of it */
    struct QueueLL *queue;
    queue = newQueueLL();
    enqueueLL(queue, T->root);

    /* Looking for the right place */
    struct Node *t;
    while((t = dequeueLL(queue))) {

      /* If the left side is empty, we found the spot */
      if (!t->left) {
        t->left = node;
        t->left->parent = t;
        break;
      } else {
        /* Otherwise, let's queue the left side for evaluation */
        enqueueLL(queue, t->left);
      }

      /* If the right side is empty, we do not care about the queue above */
      if (!t->right) {
        t->right = node;
        t->right->parent = t;
        break;
      } else {
        /* The right side has something, let's look further */
        enqueueLL(queue, t->right);
      }
    }
    destroyQueueLL(queue);
    queue = NULL;
  }
}


void atualizaAltura(struct Node *root)
{
  if(root->left) atualizaAltura(root->left);
  if(root->right) atualizaAltura(root->right);
  
  if(!(root->left || root->right))
    root->Altura = 1;
  else 
    if(!root->left && root->right)
      root->Altura = root->right->Altura +1;
    else if(root->left && !(root->right))
      root->Altura = root->left->Altura + 1;
    else
      root->Altura = maxint(root->left->Altura, root->right->Altura) + 1;
}


void atualizaNivel(struct Node *root)
{
  if(!root->parent)
    root->Nivel = 1;
  else
    root->Nivel = root->parent->Nivel + 1;

  if(root->left)
    atualizaNivel(root->left);

  if(root->right) atualizaNivel(root->right);

}

void atualizaSomaChaveD(struct Node *root)
{
  if (root) {
    atualizaSomaChaveD(root->left);
    atualizaSomaChaveD(root->right);

    root->SomaChaveD = root->val;
    if (root->left) root->SomaChaveD += root->left->SomaChaveD;
    if (root->right) root->SomaChaveD += root->right->SomaChaveD;
  }
}



void atualizaSomaChaveD2(struct Node *root)
{
  if (root) {
    atualizaSomaChaveD2(root->left);
    atualizaSomaChaveD2(root->right);

    root->SomaChaveD2 = 0;

    if (root->left) {
      if(!(root->left->left || root->left->right)) 
        root->SomaChaveD2 += root->left->val;
      else
        root->SomaChaveD2 += root->left->SomaChaveD2 + root->left->val;
    }

    if (root->right) {
      if(!(root->right->left || root->right->right)) 
        root->SomaChaveD2 += root->right->val;
      else
        root->SomaChaveD2 += root->right->SomaChaveD2 + root->right->val;
    }
  }
}


void atualizaSomaChaveD2c(struct Node *root)
{
  root->SomaChaveD2 = root->SomaChaveD - root->val;

  if(root->left) atualizaSomaChaveD2(root->left);
  if(root->right) atualizaSomaChaveD2(root->right);

}


void atualizaSomaChaveA(struct Node *root)
{
  if (!root->parent)
    root->SomaChaveA = root->val;
  else
    root->SomaChaveA = root->parent->SomaChaveA + root->val;

  if (root->left) atualizaSomaChaveA(root->left);
  if (root->right) atualizaSomaChaveA(root->right);

}


void atualizaSomaChaveA2(struct Node *root)
{
  root->SomaChaveA2 = root->SomaChaveA - root->val;
  if (root->left) atualizaSomaChaveA2(root->left);
  if (root->right) atualizaSomaChaveA2(root->right);
}

// void atualizaPNivel(struct Node *root) 
// {
//   struct QueueLL *queue;
//   queue = newQueueLL();
// 
//   enqueueLL(queue, root);
// 
//   while (! isQueueEmptyLL(queue)) {
//     struct Node *next = dequeueLL(queue);
// 
//     if ( next != NULL) {
//       printNode(next);
//       if (next->left != NULL)  enqueueLL(queue, next->left);
//       if (next->right != NULL) enqueueLL(queue, next->right);
//     }
//   }
//   destroyQueueLL(queue);
//   queue = NULL;
// }


int  compareTree(struct Node *roota, struct Node *rootb)
{
  int status = 1;
  if (roota && rootb) {
    if ( compareTree(roota->left, rootb->left) != compareTree(roota->right, rootb->right)) 
      status = 0;
    if(roota->val != rootb->val) 
      status = 0;
  }
  return status;
}


// int  isSubTree(struct Node *sub, struct Node *root)
// {
//   int status = 1;
//   if (roota != NULL && rootb !=NULL) {
//     if ( compareTree(roota->left, rootb->left) != compareTree(roota->right, rootb->right)) 
//       status = 0;
//     if(roota->val != rootb->val) 
//       status = 0;
//   }
// 
//   return status;
// 
// }


int eFolha(struct Node *node)
{
  return !(node->left || node->right);
}

int somaFolha(struct Node *node)
{
  int s = 0;
  if(node) {
    s += somaFolha(node->left) + somaFolha(node->right);
    if (eFolha(node)) 
      s += node->val;
  }
  return s;
}
 



































