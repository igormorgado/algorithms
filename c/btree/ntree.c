#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * TODO:
 * traverse (pre,in,pos,level)
 * node height
 * isBalanced
 * isAncestor
 * number of Nodes
 * number of children of root
 * node depth
 * find
 * find_child_with_data
 *
 */

// Struct to nAry tree
struct nNode {
  int val;                  // Some value (in future use a pointer to some data)
  struct nNode *next;       // Siblings of the same parent if next == NULL is the last
  struct nNode *prev;       // Siblings of same parent if prev == NULL is the first
  struct nNode *parent;     // Points to parent, if NULL is the root 
  struct nNode *children;   // Child node, other childs are found by moving next/prev
                            // if NULL is a leaf node
};


struct nNode* nNode_new(int val)
{
  struct nNode *node;

  node = malloc(sizeof *node);

  node->val       = val;
  node->next      = NULL;
  node->prev      = NULL;
  node->parent    = NULL;
  node->children  = NULL;

  return node;
}


/* Free memory */
void nNode_free(struct nNode *node)
{
  free(node);
}


/* Recursively free a nTree
 * do not mantain the relationship
 **/
void nNodes_free(struct nNode *node)
{
  while(node)
  {
    struct nNode *next = node->next;

    if (node->children)
      nNodes_free(node->children);
    nNode_free(node);
    node = next;
  }
}


bool nNode_isRoot(struct nNode *node)
{
  return (!node->parent && !node->prev && !node->next);
}


bool nNode_isLeaf(struct nNode *node)
{
  return (!node->children);
}


/* Removes a node from a tree, the node becomes the new tree */
void nNode_unlink(struct nNode *node)
{
  // Points previous next to the next (since we will get out)
  if (node->prev)
    node->prev->next = node->next;
  else if (node->parent) // we are the first child point correctly
    node->parent->children = node->next;

  // We have no parents anymore
  node->parent = NULL;

  // We have newer brothers
  if (node->next) {
    node->next->prev = node->prev;
    node->next = NULL;
  }
  node->prev = NULL;
}


/*
 * nNode_destroy
 * Destroy a node and all childs and free it from memory
 * it keeps the relationships coherent (if not deleting  root)
 */
void nNode_destroy(struct nNode *node)
{
  if(! nNode_isRoot(node))
    nNode_unlink(node);

  nNodes_free(node);
}


/* nNode_nth_child
 * Return a pointer to nth node, if member doesn't exist return NULL
 */
struct nNode* nNode_nth_child(struct nNode *parent, int position)
{
  struct nNode *node;
  node = parent->children;
  if(node) 
    while ((position-- > 0) && node)
      node = node->next;
  
  return node;
}


/*
 * nNode_insert_before
 * Insert *node as a child of *parent and before *sibling
 * if *sibling is NULL add as last sibling
 */
struct nNode* nNode_insert_before(struct nNode *parent, struct nNode *sibling, struct nNode *node)
{
  /* build parent relationship */
  node->parent = parent;

  // sibling was passed
  if (sibling) {
    // isn't the first sibling
    if (sibling->prev) {
      node->prev = sibling->prev;
      node->prev->next = node;
      node->next = sibling;
      sibling->prev = node;
    } else {
      // is the first, there is no prev. lets take his place
      node->parent->children = node;
      node->next = sibling;
      sibling->prev = node;
    }
  } else {
    // lets check if parent has any child
    if (parent->children) {
      // Lets point it
      sibling = parent->children;

      // lets move on siblings
      while(sibling->next)
        sibling = sibling->next;

      // Now we are at end of sibling list
      node->prev = sibling;
      sibling->next = node;
    } else {
      node->parent->children = node; // there is no one, node is alone 
    }
  }
  return node;
}


/*
 * nNode_insert_after
 * Insert *node as a child of *parent and before *sibling
 * if *sibling is NULL add as first sibling
 */
struct nNode* nNode_insert_after(struct nNode *parent, struct nNode *sibling, struct nNode *node)
{
  node->parent = parent;

  if (sibling) {
    if (sibling->next) {
      sibling->next->prev = node;
    }
    node->next = sibling->next;
    node->prev = sibling;
    sibling->next = node;
  } else {
    // sibling not passed,
    // is there already an children
    if(parent->children) {
      node->next = parent->children;
      parent->children->prev = node;
    }
    parent->children = node;
  }
  return node;
}


/*
 * nNode_prepend
 * Insert the node as first child
 */
struct nNode* nNode_prepend(struct nNode *parent, struct nNode *node)
{
  return nNode_insert_before(parent, parent->children, node);
}


/*
 * nNode_append
 * Append a node as last child of parent
 */
struct nNode* nNode_append(struct nNode *parent, struct nNode *node)
{
  return nNode_insert_before(parent, NULL, node);
}


/*
 * nNode_insert
 * Insert Node under Parent in nth postion */
struct nNode* nNode_insert(struct nNode *parent, int position, struct nNode *node)
{
  if(position > 0)
    return nNode_insert_before(parent, nNode_nth_child(parent, position), node);
  else if (position == 0)
    return nNode_prepend(parent, node);
  else
    return nNode_append(parent,node);
}


int main(void) {

  struct nNode *root;
  

  /*                      1
   */
  root = nNode_new(1);

  /*                      1
   *            /---------|--------\
   *          2           3         4
   */
  nNode_insert(root, 2, nNode_new(2));
  nNode_insert(root, 3, nNode_new(3));
  nNode_insert(root, 4, nNode_new(4));

  /*                      1
   *            /---------|--------\
   *          2           3         4
   *        /   \                 
   *      5       6              
   */
  nNode_insert(root->children, 5, nNode_new(5));
  nNode_insert(root->children, 6, nNode_new(6));

  /*                      1
   *            /---------|--------\
   *          2           3         4
   *        /   \                 /
   *      5       6              7
   */
  nNode_insert(root->children->next->next, 7, nNode_new(7));

  nNodes_free(root);

  return 0;
}
  




