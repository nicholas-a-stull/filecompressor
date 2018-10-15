# include "stacktwo.h"
# include "stack.h"
# include <stdio.h>

int main() {
  stack *bob = newStack();
  uint32_t a[] = {1,2,3,4,5};
  uint32_t b[] = {123,235234,459,545,634,987,123};

  if (empty(bob))
  {
	printf("fgdfg");
  }


  for(uint32_t i = 0; i < 5; i ++)
  {
    push(bob,a[i]);
  }

  for(uint32_t i = 0; i < 5; i++)
  {
    printf("%d\n",bob->entries[i] );
  }

  printf("\n\n" );
  for(uint32_t i = 0; i < 7; i ++)
  {
    push(bob,b[i]);
  }

  for(uint32_t i = 0; i < 12; i++)
  {
    printf("%d\n",bob->entries[i] );
  }

  item y[] = {pop(bob),pop(bob),pop(bob)};

  for (uint32_t i = 0; i < 3 ;i++)
  {
    printf("%d was popped off of bob\n",y[i] );
  }


  delStack(bob);


  printf("\n\nStack of treeNodes!\n\n");

  treeNode *something = newNode('a',false,10);
  treeNode *biggerSomething = newNode('b',false,20);
  treeNode *evenBiggerSomething = newNode('c',false,15);
  treeNode *blah = newNode('d',false,1);
  treeNode *blah2 = newNode('e',false,6);

  stack2 *billy = newStack2();
  push2(billy,something);
  push2(billy,biggerSomething);
  push2(billy,evenBiggerSomething);
  push2(billy,blah);
  push2(billy,blah2);

  printStack(billy);

  printf("\nPopped Something off of Bill!\n" );

  treeNode *tset = NULL;
  pop2(billy, &tset);
  printf("This was popped off billy:\n");

  printNode(tset);

  printf("\nBilly after pops!\n");

  printStack(billy);

  treeNode *grim = newNode('h', true, 12);
  push2(billy, grim);

  printStack(billy);

  delStack2(billy);

  return 0;
}
