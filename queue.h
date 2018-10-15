# ifndef _QUEUE
# define _QUEUE

# include <stdint.h>
# include <stdbool.h>

# include "huffman.h"

typedef treeNode item2; // Defined in huffman.h

typedef struct queue
{
  uint32_t size; //Size of queue
  uint32_t head, tail; //Front and rear locations
  item2 **Q;  //An array of treenode items
  uint32_t curSize;
} queue;

/*
  newQueue function
  @brief: Creates a queue data structure
  @param size:  The size of the queue
  @returns: A pointer to a queue data structure
*/
queue *newQueue(uint32_t size);

/*
  delQueue function
  @brief: deletes a queue data structure
  @param q:  A pointer to some queue
  @returns: void
*/
void delQueue(queue *q);

/*
  empty function
  @brief: checks if a queue is empty
  @param q:  A pointer to a queue
  @returns: True if empty , False otherwise
*/
bool emptyQ(queue *q);

/*
  full function
  @brief: checks if a queue is full
  @param q:  A pointer to a queue
  @returns: True if empty , False otherwise
*/
bool fullQ(queue *q);

/*
  enqueue function
  @brief: Tries to enqueue a treenode item
  @param q:  A pointer to a queue
  @param i: A treenode item to enqueue
  @returns: True if successfull enqueue, False otherwise
*/
bool enqueue(queue *q, item2 *i);

/*
  dequeue function
  @brief: Tries to dequeue a treenode item
  @param q:  A pointer to a queue
  @param i: A pointer to a treenode item to dequeue
  @returns: True if successfull dequeue, False otherwise
*/
bool dequeue(queue *q, item2 **i);

void printqueue(queue *q);

# endif
