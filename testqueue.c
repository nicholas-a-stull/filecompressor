# include "queue.h"
# include <stdio.h>

int main() {
  queue *jim = newQueue(10);
  treeNode *something = newNode('a',false,10);
  treeNode *biggerSomething = newNode('b',false,20);
  treeNode *evenBiggerSomething = newNode('c',false,15);
 treeNode *blah = newNode('d',false,1);
  treeNode *blah2 = newNode('e',false,6);

  if(emptyQ(jim))
  {
    printf("Jim is empty\n");
  }

  enqueue(jim,something);
  enqueue(jim,biggerSomething);
  enqueue(jim,evenBiggerSomething);
  enqueue(jim,blah);
  enqueue(jim,blah2);


  printf("queue before dequeue\n\n");
  printqueue(jim);

  item2 *heyy = NULL;
  dequeue(jim,&heyy);

  printf("queue after dequeue\n\n");

  printqueue(jim);

  printf("dequeue is:\n ");
  printNode(heyy);
  delQueue(jim);
  return 0;
}
