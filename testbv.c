# include "bv.h"
# include <stdio.h>

int main()
{
	bitV *j = newVec(24);
	bitV *h = newVec(8);
	oneVec(h);
	printf("Bitvector J pre-append\n");
	printVec(j);
	printf("Bitvector H pre-append\n");
	printVec(h);
	appendVec(j, h);
	printf("Bitvector J post-append\n");
	printVec(j);
	printf("Bitvector H pre-append\n");
	printVec(h);
	delVec(j);
	delVec(h);
	return 0;
}
