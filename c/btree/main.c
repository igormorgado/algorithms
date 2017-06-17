#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "queue.h"
#include "queuell.h"
#include "btree.h"

int main(void)
{

  // TEST 4
  // Passed on Valgrind
  struct Node *root;

  struct Tree *T;
  newTree(&T);

  root                   = newNode(1);
  root->left             = newNode(2);
  root->right            = newNode(3);

  T->root = root;

  printNode(root->left);
  printNode(T->root->left);

  if (root->left == T->root->left) {
    printf("Equal\n");
  } else {
    printf("Not Equal\n");
  }

  printf("Size %d\n", sizeTree(T->root));
  destroyTree(&T);

  // TEST 3
  // Passed on valgring
  //struct Node *root;

  //struct Tree *T;
  newTree(&T);
  
  root                   = newNode(1);
  root->left             = newNode(2);
  root->right            = newNode(3);

  T->root = root;
  
  int i;
  for(i=4; i<16; i++) 
    insertNodeLL(T, newNode(i));

  printf("\nwalkTreePre\n");
  walkTreePre(T->root);
  printf("\nwalkTreePos\n");
  walkTreePos(T->root);
  printf("\nwalkTreeIn\n");
  walkTreeIn(T->root);
  printf("\nwalkTreeLevel\n");
  walkTreeLevel(T->root);
  destroyTree(&T);
  // END TEST3
  
  // TEST 2
  // Passed on valgrind
  //struct Node *root;
  root                   = newNode(1);
  root->left             = newNode(2);
  root->right            = newNode(3);
  
  // destroyNode(root);
  // root = NULL;

  // END TEST 2

  // TEST 1
  // Passed on Valgring
  struct QueueLL *queue;
  queue = newQueueLL();
  enqueueLL(queue, root);
  enqueueLL(queue, root->left);
  enqueueLL(queue, root->right);
  destroyQueueLL(queue);
  queue = NULL;

  destroyNode(root);
  root = NULL;
  // END TEST1

  return 0;
}
