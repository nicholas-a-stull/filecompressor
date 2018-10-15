# include "bv.h"
# include <getopt.h>
# include "stacktwo.h"
# include <stdio.h>
# include "string.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

void freeParams(bitV *bv, char *inputFile, char *outputFile)
{
  enum{IN,OUT,VERB};
  if(valBit(bv,IN))
  {
    free(inputFile);
  }

  if(valBit(bv,OUT))
  {
    free(outputFile);
  }

  delVec(bv);
}

bool validateFile(int fd, char *fileName)
{

  uint32_t signatureCheck;
  read(fd,&signatureCheck,4);

  if(signatureCheck != 0xDeadD00d)
  {
    printf("%s is not a huffman compressed file\n", fileName);
    return false;
  }

  return true;

}

uint64_t getFileSize(int cInputFile)
{
  uint64_t fileSize;
  read(cInputFile,&fileSize,8);
  return fileSize;
}

uint16_t getTreeSize(int cInputFile)
{
  uint16_t treeSize;
  read(cInputFile,&treeSize,2);
  return treeSize;
}

bitV *byteToBit(uint8_t theByte)
{
  bitV *someBV = newVec(8);
//  bitV *tempBV = newVec(8);
  int container = -1;

  for(int i = 8; i >= 0 ; i--)
  {
    container = ((theByte & (0x1 << i % 8)) != 0);
    if(container == 1)
    {
      setBit(someBV,i);
    }
    else if(container == 0)
    {
      clrBit(someBV,i);
    }
    else
    {
      printf("Wtf?");
    }
  }
  return someBV;
}

int32_t stepTree( treeNode *root, treeNode **t, uint32_t code)
{

  if(code == 0)
  {
    *t = (*t)->left;
  }

  else if(code == 1)
  {
    *t = (*t)->right;
  }

  if((*t)->leaf)
  {
    int32_t symbol = (*t)->symbol;
    *t = root;
    return symbol;
  }
  else
  {
    return -1;
  }

}

treeNode *loadTree(uint8_t savedTree[], uint16_t treeSize, stack2 *nodeStack)
{
  treeNode *tempA;
  treeNode *tempB;
  treeNode *parent;
  treeNode *last;

  for(uint16_t i = 0; i < treeSize; i++)
  {
    if(savedTree[i] == 'L')
    {
      push2(nodeStack,newNode(savedTree[++i], true, 0));
    }
    else if(savedTree[i] == 'I')
    {
      pop2(nodeStack, &tempA);
      pop2(nodeStack, &tempB);
      parent = join(tempB,tempA);
      push2(nodeStack,parent);
    }
  }

  pop2(nodeStack,&last);
  return last;

}



int main(int argc, char *argv[])
{
  // Getopt Variables
  enum {IN,OUT,VERB};
  bitV *sortVector = newVec(3);
  int getOption;
  char *inputFile;
  char *outputFile;

  while( (getOption = getopt(argc,argv,"i:I:o:O:Vv")) != -1 )
  {
    switch(getOption)
    {
      case 'i':
      case 'I':
      setBit(sortVector,IN);
      inputFile = malloc(strlen(optarg)+1);
      strcpy(inputFile,optarg);
      break;
      case 'o':
      case 'O':
      setBit(sortVector,OUT);
      outputFile = malloc(strlen(optarg)+1);
      strcpy(outputFile,optarg);
      break;
      case 'v':
      case 'V':
      setBit(sortVector,VERB);
      break;

      case '?':
      printf("Unknown argument!\n");
      freeParams(sortVector,inputFile,outputFile);
      return 1;
    }

  }

  /*
  @brief: Checks if there is an input file
  */
  if(!valBit(sortVector,IN))
  {
    printf("No input file specified!\n");
    freeParams(sortVector,inputFile,outputFile);
    return 1;
  }

  /*
  @brief: If there is try to open it and exit if not
  */
  int cInputFile;
  if ((cInputFile = open(inputFile, O_RDWR)) < 0)
  {
    printf("Cannot find file %s\n", inputFile);
    freeParams(sortVector,inputFile,outputFile);
    return 0;
  }

  /*
  @brief: Check if input file is valid
  */
  if(!validateFile(cInputFile,inputFile))
  {
    freeParams(sortVector,inputFile,outputFile);
    return 0;
  }

  /*
  @brief: If output file is specified
  */
  if(valBit(sortVector,OUT))
  {
    FILE* file_ptr = fopen(outputFile, "w");
    fclose(file_ptr);
  }

  // Get file size
  uint64_t fileSize = getFileSize(cInputFile);

  uint16_t treeSize = getTreeSize(cInputFile);

  if(valBit(sortVector,VERB))
  {
    printf("Original file size: %lu | Tree size: %d \n", fileSize, treeSize);
  }

  uint8_t *savedTree = malloc(sizeof(uint8_t) * treeSize);

  for(uint8_t i = 0; i < treeSize ; i++)
  {
    read(cInputFile,&savedTree[i],sizeof(uint8_t));
  }


  stack2 *nodeStack = newStack2();
  stack2 *nodeStackTwo = newStack2();
  treeNode *tempNode = loadTree(savedTree,treeSize,nodeStack);
  treeNode *tracker = loadTree(savedTree,treeSize,nodeStackTwo);


   //Read in first byte
    uint8_t buffer;
    ssize_t bytesRead = read(cInputFile,&buffer,1);
    int cOutputFile = open(outputFile,O_RDWR);
    bitV *firstVec = byteToBit(buffer);
    while( bytesRead == 1)
    {
        bytesRead = read(cInputFile, &buffer, 1);
        if(bytesRead != 1)
         {
           break;
         }
        appendVec(firstVec, byteToBit(buffer));
    }


    //
    int8_t container;

    for(uint32_t i = 0, count = 0; i < firstVec->l && count < fileSize; i++)
    {
        container = stepTree(tempNode, &tracker, valBit(firstVec,i));

        if(container != -1)
        {
            if(valBit(sortVector, OUT))
            {
                write(cOutputFile, &container, 1);
                count++;
            }

            else
            {
                write(1,&container, 1);
                count++;
            }

        }
    }














  // Freeing memory
  free(savedTree);
  delVec(firstVec);
  delStack2(nodeStack);
  freeParams(sortVector,inputFile,outputFile);
  return 0;
}
