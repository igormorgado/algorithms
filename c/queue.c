#include <stdlib.h>
#include "queue.h"

/*************************************************************
 * Functions
 *************************************************************/
struct Queue* newQueue(int size)
{
  struct Queue *queue;
  queue = malloc(sizeof *queue);

  queue->head = -1;
  queue->tail = -1;
  queue->size = size;

  queue->elem = calloc(queue->size, sizeof *(queue->elem));

  return queue;
}

void destroyQueue(struct Queue *queue)
{
  free(queue->elem);
  queue->elem = NULL;

  free(queue);
  queue = NULL;
}


int queueSize(struct Queue *queue) 
{
  return (queue->tail) - (queue->head) + 1;
}


int isQueueEmpty(struct Queue *queue)
{
  return queue->head == -1 ;
}


int isQueueFull(struct Queue *queue) 
{
  return queue->tail == (queue->size - 1);
}


int isQueueSingle(struct Queue *queue) 
{
  return queue->head == queue->tail;
}


struct Node* peekQueue(struct Queue *queue)
{
  return queue->elem[queue->head];
}


int enqueue(struct Queue *queue, struct Node *root) 
{
  if (isQueueFull(queue))
    return -1;

  (queue->tail)++;
  queue->elem[queue->tail] = root;

  if (isQueueEmpty(queue)) 
    (queue->head)++;

  return queue->tail;
}


struct Node* dequeue (struct Queue *queue) 
{
  if (isQueueEmpty(queue))
    return NULL;

  struct Node *t;
  t = queue->elem[queue->head];

  if (isQueueSingle(queue))
    queue->head = queue->tail = -1;
  else
    (queue->head)++;

  return t;
}

