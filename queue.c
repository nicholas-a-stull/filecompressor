# include "queue.h"
# include "huffman.h"
# include <stdio.h>
# define SWAP(x,y) { treeNode *temp = x; x = y; y = temp; }

//code adapted from darrell long's example
queue *newQueue(uint32_t size)
{
	queue *j = malloc(sizeof(queue));
	j->size = size;
	j->head = 0;
	j->tail = 0;
	j->Q = calloc(size, sizeof(item2));
	for(uint32_t i = 0; i < j->size; i++)
	{
		j->Q[i] = NULL;
	}
	j->curSize = 0;
	return j;
}

void delQueue(queue *q)
{
	for(uint32_t i = 0; i < q->size; i++ )
	{
		if(q->Q[i] != NULL)
		{
			free(q->Q[i]);
		}
	}
	free(q->Q);
	free(q);
}

bool emptyQ(queue *q)
{
	return q->tail == q->head;
}

bool fullQ(queue *q)
{
	return ((q->head +1) % q->size) == ((q->tail) % q->size);
}

bool enqueue(queue *q, item2 *i)
{
	if (fullQ(q))
	{
		return false;
	}
	else if (emptyQ(q))
	{
		q->Q[q->head] = i;
		q->head += 1;
		q->head = q->head % q->size;
		q->curSize++;
		return true;
	}
	else
	{
		if( q->Q[q->head] != NULL)
		{
			delNode(q->Q[q->head]);
		}
		q->Q[q->head] = i;

		int j = q->head;
		while(
					j>=0
					&& (j-1)>=0
					&& q->Q[j] != NULL
					&& q->Q[j-1] != NULL
					&& q->Q[j-1]->count > q->Q[j]->count
				)
		{
			SWAP(q->Q[j-1], q->Q[j]);
			j--;
		}


		q->head +=1;
		q->head = q->head % q->size;
		q->curSize++;

		return true;

	}

}

bool dequeue(queue *q, item2 **i)
{
	if (emptyQ(q))
	{
		return false;
	}
	else
	{
		if(i || !i)
		{
			*i = q->Q[q->tail];
		}
		q->tail = (q->tail + 1) % q->size;
		q->curSize--;
		return true;
	}

}

void printqueue(queue *q)
{
	for (uint32_t i = q->tail; i % q->size < q->head % q->size; i++)
	{
		if(q->Q[i] != NULL)
		{
			printNode(q->Q[i]);
		}
	}
	printf("\n");
}
