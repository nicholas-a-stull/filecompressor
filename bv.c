# include <stdint.h>
# include <stdio.h>
# include "bv.h"

void oneVec(bitV *A)
{
  for (uint32_t i = 0 ; i < ((A->l/8) +1 ); i ++ ) {
    (A->v)[i] |= 0xFF;
  }
}

void appendVec(bitV *a, bitV *b)
{
	a->v = realloc(a->v, ((a->l + b->l) / 8) + 1);

	for (uint32_t i = a->l, j = 0; i < a->l + b->l; i++,j++)
	{
		if (valBit(b, j))
		{
			setBit(a, i);
		}
		else
		{
			clrBit(a, i);
		}
	}
	a->l = a->l + b->l;
  delVec(b);
}

void printVec(bitV *x)
{
	for(uint32_t i = 0 ; i < x->l; i++)
	{
		if(i != 0 && i % 8 == 0)
		{
			printf("\t");
		}
		if(i != 0 && i % 64 == 0)
		{
			printf("\n");
		}
		printf("%d",valBit(x,i));
	}
  printf("\n");
}
