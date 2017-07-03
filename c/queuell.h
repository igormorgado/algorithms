#ifndef _QUEUELL_H_
#define _QUEUELL_H_

#include "node.h"

/* Queue linked list */
struct QueueLL {
  struct NodeLL *head;
  struct NodeLL *tail;
  int size;
};

/* Queue Linked List */
struct QueueLL* newQueueLL        (void); // 05-32
void            destroyQueueLL    (struct QueueLL *queue); // 05-32
struct Node*    peekQueueLL       (struct QueueLL *queue); // 05-33
int             enqueueLL         (struct QueueLL *queue, struct Node *root); // 05-34
struct Node*    dequeueLL         (struct QueueLL *queue); // 05-35
int             queueSizeLL       (struct QueueLL *queue); // 05-36
int             isQueueEmptyLL    (struct QueueLL *queue);
int             isQueueSingleLL   (struct QueueLL *queue);

#endif
