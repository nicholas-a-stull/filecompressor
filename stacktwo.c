# include "stacktwo.h"
# include <stdlib.h>
# include "huffman.h"

stack2 *newStack2()
{
	stack2 *j = malloc(sizeof(stack2));
	j->size = 10;
	j->top = 0;
	j->entries = calloc(j->size, sizeof(item3));
	for(uint32_t i = 0; i < j->size; i++)
	{
		j->entries[i] = NULL;
	}
	return j;
}

void delStack2(stack2 *j)
{
	for(uint32_t i = 0; i < j->size; i++)
	{
		if(j->entries[i] != NULL)
		{
			free(j->entries[i]);
		}
	}
	free(j->entries);
	free(j);
}

bool pop2(stack2 *j,item3** dest)
{

	if(j->top != 0)
	{
		j->top -= 1;
		*dest = j->entries[j->top];
		return true;
	}
	else
	{
		printf("Under flow error!\n" );
		return false;
	}
}

void push2(stack2 *j, item3 *k)
{
	if(j->top != j->size)
	{
		// if (j->entries[j->top] != NULL)
		// {
		// 	delNode(j->entries[j->top]);
		// }
		j->entries[j->top] = k;
		j->top += 1;
	}
	else
	{
		j->size *= 2;
		j->entries = realloc(j->entries, sizeof(item3) * j->size);

		// if (j->entries[j->top] != NULL)
		// {
		// 	delNode(j->entries[j->top]);
		// }

		j->entries[j->top] = k;
		j->top += 1;
	}
	return;
}

bool empty2(stack2 *j)
{
	return j->top == 0;
}

bool full2(stack2 *j)
{
	return j->top == j->size;
}

void printStack(stack2 *someStack)
{
	for (uint32_t i = 0; i < someStack->top; i++)
	{
		if(someStack->entries[i] != NULL)
		{
			printNode(someStack->entries[i]);
		}
	}
}
