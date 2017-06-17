#ifndef QUEUE_H_
#define QUEUE_H_

#include "node.h"

#define MAXQUEUESIZE 50

/* Queue sequential */
struct Queue {
  int head;
  int tail;
  int size;
  struct Node **elem;
};


 /* Queue Sequential */
struct Queue*   newQueue          (int size); //05-27
void            destroyQueue      (struct Queue *queue);
struct Node*    peekQueue         (struct Queue *queue); // 05-28
int             enqueue           (struct Queue *queue, struct Node *root); // 05-29
struct Node*    dequeue           (struct Queue *queue); // 05-30
int             queueSize         (struct Queue *queue); // 05-31
int             isQueueEmpty      (struct Queue *queue);
int             isQueueFull       (struct Queue *queue);
int             isQueueSingle     (struct Queue *queue);

#endif
