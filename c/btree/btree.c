#include <stdlib.h>
#include "btree.h"
#include "queue.h"
#include "queuell.h"


void newTree(struct Tree **T) 
{
  (*T)       = malloc(sizeof *(*T));

  (*T)->root = NULL;
  (*T)->height = 0;
}


void destroyTree(struct Tree **T)
{
  destroyNodeByRef(&((*T)->root));
  // (*T)->root = NULL;
  free(*T);
  *T = NULL;
}


void walkTreePre(struct Node *root) 
{
  if (root != NULL) {
    printNode(root);
    walkTreePre(root->left);
    walkTreePre(root->right);
  }
}


void walkTreePos(struct Node *root) 
{
  if (root != NULL) {
    walkTreePos(root->left);
    walkTreePos(root->right);
    printNode(root);
  }
}


void walkTreeIn(struct Node *root) 
{
  if (root != NULL) {
    walkTreeIn(root->left);
    printNode(root);
    walkTreeIn(root->right);
  }
}


void walkTreeLevel(struct Node *root) 
{
  struct Queue *queue;
  queue = newQueue(MAXQUEUESIZE);

  if(root != NULL) enqueue(queue, root);

  while (! isQueueEmpty(queue)) {
    struct Node *next = dequeue(queue);

    if ( next != NULL) {
      printNode(next);
      if (next->left != NULL)  enqueue(queue, next->left);
      if (next->right != NULL) enqueue(queue, next->right);
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

    if ( next != NULL) {
      printNode(next);
      if (next->left != NULL)  enqueueLL(queue, next->left);
      if (next->right != NULL) enqueueLL(queue, next->right);
    }
  }
  destroyQueueLL(queue);
  queue = NULL;
}


int sizeTree(struct Node *root) 
{
  if (root == NULL)
    return 0;
  return sizeTree(root->left) + 1 + sizeTree(root->right);
}


/* Insert *node, inside the tree with root *root
 * always trying to minimize the height keeping
 * the tree complete.
 */
void insertNode(struct Tree *T, struct Node *node) 
{
  if (T->root == NULL) {
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
      if (t->left == NULL) {
        t->left = node;
        break;
      } else {
        /* Otherwise, let's queue the left side for evaluation */
        enqueue(queue, t->left);
      }

      /* If the right side is empty, we do not care about the queue above */
      if (t->right == NULL) {
        t->right = node;
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
  if (T->root == NULL) {
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
      if (t->left == NULL) {
        t->left = node;
        break;
      } else {
        /* Otherwise, let's queue the left side for evaluation */
        enqueueLL(queue, t->left);
      }

      /* If the right side is empty, we do not care about the queue above */
      if (t->right == NULL) {
        t->right = node;
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

