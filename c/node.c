#include <stdio.h>
#include <stdlib.h>
#include "node.h"

struct Node* newNode(int val) 
{
  struct Node *node;
  node = malloc(sizeof *node);
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  return node;
}


void destroyNode(struct Node *node)
{
  if(node->left != NULL) {
    destroyNode(node->left);
    node->left = NULL;
  }
  if(node->right != NULL) {
    destroyNode(node->right);
    node->right = NULL;
  }
  free(node);
  node = NULL;
}

void destroyNodeByRef(struct Node **node)
{
  if((*node)->left != NULL) {
    destroyNodeByRef(&((*node)->left));
    (*node)->left = NULL;
  }
  if((*node)->right != NULL) {
    destroyNodeByRef(&((*node)->right));
    (*node)->right = NULL;
  }
  free(*node);
  *node = NULL;
}


void printNode(struct Node *N)
{
  printf("Value %d\n", N->val);
}
