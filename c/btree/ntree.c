#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * TODO:
 * traverse (level)
 * isBalanced
 */

#define NNODE_STOP_TRAVERSE true;
#define NNODE_CONT_TRAVERSE false;

typedef enum
{
  TRAVERSE_LEAVES = 1 << 0,
  TRAVERSE_NON_LEAVES = 1 << 1,
  TRAVERSE_ALL = TRAVERSE_LEAVES | TRAVERSE_NON_LEAVES,
  TRAVERSE_MASK = 0x03
} TraverseFlags;

typedef enum
{
  INORDER,
  PREORDER,
  POSTORDER,
  LEVELORDER
} TraverseType;


// Struct to nAry tree
struct nNode {
  int val;                  // Some value (in future use a pointer to some data)
  struct nNode *next;       // Siblings of the same parent if next == NULL is the last
  struct nNode *prev;       // Siblings of same parent if prev == NULL is the first
  struct nNode *parent;     // Points to parent, if NULL is the root 
  struct nNode *children;   // Child node, other childs are found by moving next/prev
                            // if NULL is a leaf node
};

struct NodeLL {
	struct nNode  *node;
	struct NodeLL *next;
	struct NodeLL *prev;
};

struct QueueLL {
  struct NodeLL *head;
  struct NodeLL *tail;
  int size;
};

/* 
 * QUEUE FUNCTIONS
 */

struct QueueLL* newQueueLL() 
{
  struct QueueLL *queue;
  queue = malloc(sizeof *queue);

  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;

  return queue;
}

int isQueueEmptyLL(struct QueueLL *queue) 
{
  return ( queue->head  == NULL ) && (queue->tail == NULL);
}


int isQueueSingleLL(struct QueueLL *queue) 
{
  return ( queue->head == queue->tail ) && (queue->head != NULL);
}

struct nNode *dequeueLL(struct QueueLL *queue)
{
  if (queue->head == NULL)
    return NULL;

  struct nNode *first;

  first = queue->head->node;

  struct NodeLL *oldhead;
  oldhead = queue->head;

  queue->head = queue->head->next;
	//queue->head->prev = NULL;

  if (queue->head == NULL)
    queue->tail = NULL;

  free(oldhead);
  (queue->size)--;

  return first;
}


void destroyQueueLL(struct QueueLL *queue) 
{
  while(!isQueueEmptyLL(queue)) dequeueLL(queue);
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
  free(queue);
  queue = NULL;
}


struct nNode* peekQueueLL(struct QueueLL *queue) 
{
  return queue->head->node;
}



int QueueSizeLL(struct QueueLL *queue) 
{
  return queue->size;
}


int enqueueLL(struct QueueLL *queue, struct nNode *root) 
{

	/* Allocates space to the new element on queue */
  struct NodeLL *new;
  new = malloc(sizeof *new);
  new->node = root;
  new->next = NULL;
	//new->prev = NULL;

	/* If isn't the first element point the
   * actual tail next to the new NodeLL
   */
  if (queue->tail != NULL ) {
    queue->tail->next = new;
    //queue->tail->next->prev = queue->tail;
	}

	/* Point tail to the new Node */
  queue->tail = new;

  if (queue->head == NULL)
    queue->head = queue->tail;

  return ++(queue->size);
}



/*
 * nTree functions
 */

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

// Generic TraverseFunc
typedef bool (*nNodeTraverseFunc) (struct nNode *node, int val);



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


/*
 * nNode_height
 * Return the node height
 */
int nNode_height(struct nNode *node)
{

  int height = 0;
  int child_height = 0;

  struct nNode *child;

  if (!node)
    return 0;

  child = node->children;
  while(child) {

    child_height = nNode_height(child);

    if (child_height > height ) 
      height = child_height;

    child = child->next;
  }

  return height + 1;
}

/*
 * nNode_depth
 * Return the node depth
 */
int nNode_depth(struct nNode *node)
{
  int depth = 0;

  while(node) {
    node = node->parent;
    depth++;
  }
  return depth;
}

/*
 * nNode_n_children
 * Return the nuber of children of node
 */
int nNode_n_children(struct nNode *node)
{

  int n = 0;

  while(node) {
    node = node->next;
    n++;
  }

  return n;
}

/*
 * Check if *ancestor of *node
 */
bool nNode_isAncestor(struct nNode *node, struct nNode *ancestor)
{
  while(node) {
    if (node->parent == ancestor)
      return true;
    node = node->parent;
  }
  return false;
}

bool nNode_isAncestorRec(struct nNode *node, struct nNode *ancestor)
{
  if (node->parent == ancestor) return true;
  return nNode_isAncestor(node->parent, ancestor) || false;
}


/*
 * Check if *descendant of *node
 */
bool nNode_isDescendant(struct nNode *node, struct nNode *descendant)
{
  return nNode_isAncestor(descendant, node);
}


struct nNode* nNode_getRoot(struct nNode *node)
{
  while(node->parent) node = node->parent;

  return node;
}

/*
 * nNode_print
 * Function to be passed to check traverse
 */
bool nNode_print(struct nNode *node, int val) 
{
  printf("Node val: %d\n", node->val);
  return NNODE_CONT_TRAVERSE;
}


bool nNode_traverse_preOrder(
    struct             nNode *node, 
    TraverseFlags      flags, 
    nNodeTraverseFunc  visit,
    int                val )
{
  if((flags & TRAVERSE_LEAVES)     &&    nNode_isLeaf(node)  && visit(node, val))
    return NNODE_CONT_TRAVERSE;
  if((flags & TRAVERSE_NON_LEAVES) && (! nNode_isLeaf(node)) && visit(node, val))
    return NNODE_CONT_TRAVERSE;
  
  struct nNode *child;
  child = node->children;
  
  while(child)
  {
    struct nNode *current;
    current = child;
    child = current->next;

    nNode_traverse_preOrder(current, flags, visit, val);
  }

  return NNODE_STOP_TRAVERSE;
}


void nNode_traverse_posOrder(
    struct             nNode *node, 
    TraverseFlags      flags, 
    nNodeTraverseFunc  visit,
    int                val )
{

  struct nNode *child;
  child = node->children;

  while(child)
  {
    struct nNode *current;
    current = child;

    child = current->next;

    nNode_traverse_posOrder(current, flags, visit, val);
  }

  if((flags & TRAVERSE_LEAVES)     &&    nNode_isLeaf(node) ) visit(node, val);
  if((flags & TRAVERSE_NON_LEAVES) && (! nNode_isLeaf(node))) visit(node, val);

}

/* nNode_traverse_inOrder
 * We assume inOder means to visit the first child before all others
 */
void nNode_traverse_inOrder(
    struct             nNode *node, 
    TraverseFlags      flags, 
    nNodeTraverseFunc  visit,
    int                val )
{
  if (node->children)
  {
    struct nNode *sibling;
    struct nNode *current;

    current = node->children;
    sibling = current->next;

    nNode_traverse_inOrder(current, flags, visit, val);

    if((flags & TRAVERSE_LEAVES)     &&    nNode_isLeaf(node) ) visit(node, val);
    if((flags & TRAVERSE_NON_LEAVES) && (! nNode_isLeaf(node))) visit(node, val);

    while(sibling)
    {
      nNode_traverse_inOrder(sibling, flags, visit, val);
      sibling = sibling->next;
    }
  } else {
      if((flags & TRAVERSE_LEAVES)     &&    nNode_isLeaf(node) ) visit(node, val);
      if((flags & TRAVERSE_NON_LEAVES) && (! nNode_isLeaf(node))) visit(node, val);
  }
}

bool nNode_traverse_levelOrder(
    struct              nNode *node,
    TraverseFlags       flags,
    nNodeTraverseFunc   visit,
    int                 val)
{
  struct nNode *child;
  struct nNode *sibling;
  struct nNode *next;

  struct QueueLL *queue;
  queue = newQueueLL();

  enqueueLL(queue, node);

  while (! isQueueEmptyLL(queue)) {
    next = dequeueLL(queue);

    if(next) {
      if((flags & TRAVERSE_LEAVES)     &&    nNode_isLeaf(next) ) visit(next, val);
      if((flags & TRAVERSE_NON_LEAVES) && (! nNode_isLeaf(next))) visit(next, val);

      child = next->children;
      while(child) {
        enqueueLL(queue, child);
        sibling = child->next;
        while(sibling) {
          enqueueLL(queue, sibling);
          sibling = sibling->next;
        }
        child = child->children;
      }
    }
  }

  destroyQueueLL(queue);
  queue = NULL;

  return true;
}

/*
 * nNode_count
 * 
 */
void nNode_count_func(struct nNode *node, TraverseFlags flags, int *n)
{
  if (node->children)
  {
    struct nNode *child;

    if (flags & TRAVERSE_NON_LEAVES) (*n)++;

    child = node->children;

    while(child)
    {
      nNode_count_func(child, flags, n);
      child = child->next;
    }
  } else if (flags & TRAVERSE_LEAVES) (*n)++;
}

int nNode_count(struct nNode *node, TraverseFlags flags)
{
  int n = 0;
  nNode_count_func(node, flags, &n);

  return n;
}

/*
 * nNode_n_leaves
 * Count the number of leaves under node
 */
int nNode_n_leaves(struct nNode *node)
{
  return nNode_count(node, TRAVERSE_LEAVES);
}
  

/* 
 * nNode_n_nonLeaves
 * Count the number of nonleaves under node
 */
int nNode_n_nonLeaves(struct nNode *node)
{
  return nNode_count(node, TRAVERSE_NON_LEAVES);
}
  
/* 
 * nNode_n_nodes
 * Count the number of nonleaves under node
 */
int nNode_n_nodes(struct nNode *node)
{
  return nNode_count(node, TRAVERSE_ALL);
}
  

/*
 * nNode_find_func
 * Returns  TRUE if node->val == val
 */
bool nNode_find_func(struct nNode *node, int val)
{
   if (node->val == val)
   {
     return NNODE_STOP_TRAVERSE;
   }
   else
   {
     return NNODE_CONT_TRAVERSE;
   }
}

struct nNode* nNode_find(struct nNode *node, int val)
{
  // We found the node return the pointer
  if(nNode_find_func(node, val)) return node;

  // We didn't found le's check the children
  struct nNode *child = node->children;
  while(child) {
    if(nNode_find(child, val)) return child;
    
    // We didn't found on child, lets check his brothers
    struct nNode *sibling = child->next;
    while(sibling) {
      if(nNode_find(sibling, val)) return sibling;
      sibling = sibling->next;
    }

    child = child->children;

  }
  // We didn't found the element return NULL
  return NULL;
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

  printf("\n");
  printf("Root height %d\n", nNode_height(root));
  printf("Root level %d\n", nNode_depth(root));
  printf("Root child %d\n", nNode_n_children(root));
  printf("2 child %d\n", nNode_n_children(root->children));
  printf("3 level %d\n", nNode_depth(root->children));

  printf("\n");
  printf("root isAnc root %d\n",             nNode_isAncestor(root,root));
  printf("root isAnc root-child %d\n",       nNode_isAncestor(root->children,root));
  printf("root isAnc root-child-child %d\n", nNode_isAncestor(root->children->children,root));
  printf("root->2 isAnc root->3 %d\n",       nNode_isAncestor(root->children->next,root->children));

  printf("\n");
  printf("root isAnc root %d\n",             nNode_isAncestorRec(root,root));
  printf("root isAnc root-child %d\n",       nNode_isAncestorRec(root->children,root));
  printf("root isAnc root-child-child %d\n", nNode_isAncestorRec(root->children->children,root));
  printf("root->2 isAnc root->3 %d\n",       nNode_isAncestorRec(root->children->next,root->children));

  printf("\n");
  printf("root-child-child isDes root %d\n", nNode_isDescendant(root,root->children->children));
  printf("root->3 isDes root->2 %d\n",       nNode_isDescendant(root->children->next,root->children));


  printf("\n");
  printf("PRE 1 2 _5 _6 _3 4 _7\n");
  nNode_traverse_preOrder(root, TRAVERSE_ALL, (nNodeTraverseFunc)nNode_print, 0);
  printf("\n");
  nNode_traverse_preOrder(root, TRAVERSE_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  printf("\n");
  nNode_traverse_preOrder(root, TRAVERSE_NON_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  printf("\n");

  // printf("\n");
  // printf("POS _5 _6 2 _3 _7 4 1\n");
  // nNode_traverse_posOrder(root, TRAVERSE_ALL, (nNodeTraverseFunc)nNode_print, 0);
  // printf("\n");   
  // nNode_traverse_posOrder(root, TRAVERSE_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  // printf("\n");   
  // nNode_traverse_posOrder(root, TRAVERSE_NON_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  // printf("\n");

  // printf("\n");
  // printf("IN _5 2 _6 1 _3 _7 4\n");
  // nNode_traverse_inOrder(root, TRAVERSE_ALL, (nNodeTraverseFunc)nNode_print, 0);
  // printf("\n");   
  // nNode_traverse_inOrder(root, TRAVERSE_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  // printf("\n");   
  // nNode_traverse_inOrder(root, TRAVERSE_NON_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  // printf("\n");

  printf("\n");
  printf("LVL 1 2 _3 4 _5 _6 _7\n");
  nNode_traverse_levelOrderA(root, TRAVERSE_ALL, (nNodeTraverseFunc)nNode_print, 0);
  printf("\n");   
  nNode_traverse_levelOrderA(root, TRAVERSE_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  printf("\n");   
  nNode_traverse_levelOrderA(root, TRAVERSE_NON_LEAVES, (nNodeTraverseFunc) nNode_print, 0);
  printf("\n");

  printf("N leaves %d\n",nNode_n_leaves(root));
  printf("N nonleaves %d\n",nNode_n_nonLeaves(root)); 
  printf("N nodes %d\n",nNode_n_nodes(root)); 

  struct nNode *nfind;
  nfind = nNode_find(root,3);
  if(nfind) nNode_print(nfind,0);

  nNodes_free(root);


  return 0;
}
  




