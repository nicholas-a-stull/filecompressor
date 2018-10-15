# include "stack.h"
# include <stdlib.h>

stack *newStack()
{
	stack *j = malloc(sizeof(stack));
	j->size = 10;
	j->top = 0;
	j->entries = (item *) calloc(j->size, sizeof(item));
	return j;
}

void delStack(stack *j)
{
	free(j->entries);
	free(j);
}

item pop(stack *j)
{
	if(j->top != 0)
	{
		j->top -= 1;
		return j->entries[j->top];
	}
	else
	{
		return INVALID;
	}
}

void push(stack *j, item k)
{
	if(j->top != j->size)
	{
		j->entries[j->top] = k;
		j->top += 1;
	}
	else
	{
		j->size *= 2;
		j->entries = realloc(j->entries, sizeof(item) * j->size);
		j->entries[j->top] = k;
		j->top += 1;
	}
	return;
}

bool empty(stack *j)
{
	return j->top == 0;
}

bool full(stack *j)
{
	return j->top == j->size;
}
