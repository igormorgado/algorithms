#include <stdlib.h>
#include "queuell.h"

struct QueueLL* newQueueLL() 
{
  struct QueueLL *queue;
  queue = malloc(sizeof *queue);

  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;

  return queue;
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


struct Node* peekQueueLL(struct QueueLL *queue) 
{
  return queue->head->node;
}


int isQueueEmptyLL(struct QueueLL *queue) 
{
  return ( queue->head  == NULL ) && (queue->tail == NULL);
}


int isQueueSingleLL(struct QueueLL *queue) 
{
  return ( queue->head == queue->tail ) && (queue->head != NULL);
}


int QueueSizeLL(struct QueueLL *queue) 
{
  return queue->size;
}


int enqueueLL(struct QueueLL *queue, struct Node *root) 
{

	/* Allocates space to the new element on queue */
  struct NodeLL *new;
  new = malloc(sizeof *new);
  new->node = root;
  new->next = NULL;

	/* If isn't the first element point the
   * actual tail next to the new NodeLL
   */
  if (queue->tail != NULL )
    queue->tail->next = new;

	/* Point tail to the new Node */
  queue->tail = new;

  if (queue->head == NULL)
    queue->head = queue->tail;

  return ++(queue->size);
}


struct Node *dequeueLL(struct QueueLL *queue)
{
  if (queue->head == NULL)
    return NULL;

  struct Node *first;
  first = queue->head->node;

  struct NodeLL *oldhead;
  oldhead = queue->head;

  queue->head = queue->head->next;

  if (queue->head == NULL)
    queue->tail = NULL;

  free(oldhead);
  (queue->size)--;

  return first;
}

