# ifndef _STACKTWO_H
# define _STACKTWO_H
# define INVALID 0xDeadD00d

# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"

typedef treeNode item3; //something needs to be changed?

typedef struct stack2
{
	uint32_t size; //how big
	uint32_t top; //index of top
	item3 **entries; //array of items
}stack2;

/*
	function newStack
	@brief: Creates a new stack
	@returns: A pointer to a new stack
*/
stack2 *newStack2();

/*
	function delStack
	@brief:	Deleets a stack
	@param J: The stack to be deleted
*/
void delStack2(stack2 *j);

/*
	function pop
	@brief: Pops an item off the top of the stack
	@param j: The stack to pop the item off
	@returns: The item on the top of the stack
*/
bool pop2(stack2 *j, item3 **dest);

/*
	function push
	@brief: Pushes an item onto the stack and reallocs if full
	@param j:	The stack to push an item onto
	@param k:	The item to push onto the stack
*/
void push2(stack2 *j, item3 *k);

/*
	function empty
	@brief: Checks if a stack is empty
	@param j:	The stack to check
	@returns: True if empty, false otherwise
*/
bool empty2(stack2 *j);

/*
	function ful
	@brief: Checks if a stack is full
	@param j: The stack to check
	@returns:	True if full, false otherwise
*/
bool full2(stack2 *j);

void printStack(stack2 *someStack);

# endif
