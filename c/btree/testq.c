#include <stdlib.h>
#include "node.h"
#include "queue.h"
#include "queuell.h"

int main(void)
{
  struct Node *root;

  struct QueueLL *queue;
  queue = newQueueLL();

  root                   = newNode(1);
  root->left             = newNode(2);
  root->right            = newNode(3);

  enqueueLL(queue, root);
  enqueueLL(queue, root->left);
  enqueueLL(queue, root->right);

  destroyQueueLL(queue);
  queue = NULL;

  destroyNode(root);
  root = NULL;

  return 0;
}
