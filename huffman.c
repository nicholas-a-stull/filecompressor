# include "huffman.h"
# include <stdbool.h>
# include <stdlib.h>


treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	treeNode *j = malloc(sizeof(treeNode));
	j->symbol = s;
	j->leaf = l;
	j->count = c;
	j->left = NULL;
	j->right = NULL;
	return j;
}

void delTree(treeNode *t)
{
	if(t == NULL)
	{
		return;
	}

	delTree(t->left);

	delTree(t->right);

	delNode(t);
	t = NULL;
	return;
}

void printTree(treeNode *t, int depth)
{
        if (t && t->leaf)
        {
                if (isalnum(t->symbol))
                {
                        spaces(4 * depth); printf("%c (%lu)\n", t->symbol, t->count);
                }
                else
                {
                        spaces(4 * depth); printf("%X (%lu)\n", t->symbol, t->count);
                }
        }
        else if (t)
        {
                spaces(4 * depth); printf("$ (%lu)\n", t->count);
                printTree(t->left, depth + 1);
                printTree(t->right, depth + 1);
        }
        return;
}


//ENCODE

//void dumpTree(treeNode *t, int file)
//{
//
//}

//DECODE

//treeNode *loadTree(uint8_t *savedTree, uint16_t treeBytes)
//{
//
//}

//DECODE

//int32_t *stepTree(treeNode *root, treeNode *t, uint32_t code)
//{
//
//}

//ENCODE

//void buildCode(treeNode *t, code s, code table[256])
//{
//
//}

treeNode *join(treeNode *l, treeNode *r)
{
	treeNode *j = newNode('$', false, l->count + r->count);
	j->left =  l;
	j->right = r;
	return j;
}

void printNode(treeNode *t)
{
	printf("Symbol: %c\n",t->symbol);
	printf("Count: %lu\n",t->count);
	if (t->leaf)
	{
		printf("Is leaf\n");
	}
	else {
		printf("Is NOT leaf\n");
	}

	printf("\n");
}
