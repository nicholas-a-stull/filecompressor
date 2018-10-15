# ifndef _STACK_H
# define _STACK_H

# define INVALID 0xDeadD00d

# include <stdint.h>
# include <stdbool.h>

typedef uint32_t item; //something needs to be changed?

typedef struct stack
{
	uint32_t size; //how big
	uint32_t top; //index of top
	item *entries; //array of items
}stack;

/*
	function newStack
	@brief: Creates a new stack
	@returns: A pointer to a new stack
*/
stack *newStack();

/*
	function delStack
	@brief:	Deleets a stack
	@param J: The stack to be deleted
*/
void delStack(stack *j);

/*
	function pop
	@brief: Pops an item off the top of the stack
	@param j: The stack to pop the item off
	@returns: The item on the top of the stack
*/
item pop(stack *j);

/*
	function push
	@brief: Pushes an item onto the stack and reallocs if full
	@param j:	The stack to push an item onto
	@param k:	The item to push onto the stack
*/
void push(stack *j, item k);

/*
	function empty
	@brief: Checks if a stack is empty
	@param j:	The stack to check
	@returns: True if empty, false otherwise
*/
bool empty(stack *j);

/*
	function ful
	@brief: Checks if a stack is full
	@param j: The stack to check
	@returns:	True if full, false otherwise
*/
bool full(stack *j);

# endif
