# ifndef _HUFFMAN
# define _HUFFMAN

# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>

# include "code.h"

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct DAH treeNode;

struct DAH
{
  uint8_t symbol;
  uint64_t count;
  bool leaf;
  treeNode *left, *right;
};

/*
  function newNode
  @brief: The constructor function for a treeNode data structure
  @param s: The symbol for the treeNode
  @param l: If the treeNode is a leaf
  @param c: The count associated with the treeNode
  @return:  A pointer to a leaf node

*/
treeNode *newNode(uint8_t s, bool l, uint64_t c);

/*
  function delTree
  @brief: Deletes an etire tree
  @param t: A pointer to a node of a tree
  @return:  A tree node
*/
void delTree(treeNode *t);

/*
  function dumpTree
  @brief: Dumps a huffman tree into a file
  @param t: A pointer to treeNode to dump
  @param file:  An integer which specifies the file to dump to
*/
//void dumpTree(treeNode *t, int file);

/*
  function loadTree
  @brief: Loads a huffman tree from a file
  @param savedTree: An array of bytes indicatig a tree
  @param treeBytes: An int specifying the amount of bytes in a Tree
  @return: A pointer to a treeNode
*/
//treeNode *loadTree(uint8_t *savedTree, uint16_t treeBytes);

/*
  function stepTree
  @brief: Step through a tree following the code
  @param root:  The root of the huffman tree
  @param t: A treenode from the root of the last parameter?
  @param code: The code of which to step the tree through
  @returns: a pointer to an int32_t ?
*/
//int32_t *stepTree(treeNode *root, treeNode *t, uint32_t code);

/*
  function buildCode
  @brief: Parse a Huffman tree to build codes
  @param t: A treenode to build the code from
  @param s: ?
  @param table: ?
*/
//void buildCode(treeNode *t, code s, code table[256]);

/*
  function delNode
  @brief: Deletes a node
  @param t: A treenode to be deleted
*/
static inline void delNode(treeNode *h)
{
	free(h);
 	h = NULL;
	return;
}

/*
  function compare
  @brief: Compares two nodes
  @param t: left treenode to compare
  @param r: Right tree node to compare
  @returns: The difference between two adjacent nodes
*/
static inline int8_t compare(treeNode *l, treeNode *r)
{
  return l->count - r->count;
}

/*
  function join
  @brief: Joins two nodes
  @param t: left treenode to join
  @param r: Right tree node to join
  @returns: The resulting node when joing two adjacent nodes
*/
treeNode *join(treeNode *l, treeNode *r);

static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }

void printTree(treeNode *t, int depth);

void printNode(treeNode *t);

# endif
