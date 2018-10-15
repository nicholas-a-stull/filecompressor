# include "huffman.h"

int main(void)
{
  treeNode *huff = newNode('a',false,10);

  huff->left = newNode('b',false,22);

  huff->right = newNode('c',false,25);

  huff->left->left = newNode('d',true,33);
  huff->left->right = newNode('e',true,35);

  huff->right->left = newNode('f',true,37);
  huff->right->right = newNode('g',true,39);

  // printTree(huff,3);

  printNode(huff);

  delTree(huff);

  return 0;
}
