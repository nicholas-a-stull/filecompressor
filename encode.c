# include <stdio.h>
# include <string.h>
# include "huffman.h"
# include "stack.h"
# include "queue.h"
# include "stacktwo.h"
# include "code.h"
# include "bv.h"
# include <getopt.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

uint16_t leafcount = 0;

void makeHist(int in, uint32_t *table)
{
	ssize_t bytesRead = 1;
	uint8_t buf[1];

	while (bytesRead == 1)
	{
		bytesRead = read(in, buf, 1);
	//	printf("%d\n", buf[0]);
		table[buf[0]] += 1;
	}
	table[0] += 1;
	table[255] += 1;
        close(in);

	//test print
//	for (int i = 0; i < 256; i++)
//	{
//		printf("value:%d index:%d\n", table[i], i);
//	}

}

treeNode* makeTree(uint32_t *table)
{
	queue *j = newQueue(256);

	for (int i = 0; i < 256; i++)
	{
		if (table[i] > 0)
		{
			treeNode *h = newNode((uint8_t) i, true, table[i]);
			leafcount += 1;
			enqueue(j, h);
		}
	}

	treeNode *a = NULL;
	treeNode *b = NULL;
	treeNode *c = NULL;
	while (1)
	{
		if (emptyQ(j) == true)
		{
			break;
		}

		dequeue(j, &a);

		if (emptyQ(j) == true)
		{
			break;
		}

		dequeue(j, &b);

		c = join(a, b);

		enqueue(j, c);
	}
//	delQueue(j);
	return a;
}

//put tree into the encoded file
void dumpTree(treeNode *t, int file)
{
	char interior[1] = {'I'};
	if (t->leaf == true)
	{
		char leafbuf[2] = {'L', t->symbol};
		write(file, leafbuf, 2);
		return;
	}
	else
	{
		dumpTree(t->left, file);

		dumpTree(t->right, file);

                write(file, interior, 1);
	}
	return;
}


//the bits of the encoded characters
void buildCode(treeNode *t, code s, code table[256])
{
	uint32_t useless;
	if (t->leaf == true)
	{
		table[t->symbol] = s;
	//	popCode(&s, &useless);
		return;
	}
	else
	{
		pushCode(&s, 0);
		buildCode(t->left, s, table);
		popCode(&s, &useless);		

		pushCode(&s, 1);
		buildCode(t->right, s, table);
		popCode(&s, &useless);
	}
//	popCode(&s, &useless);
        
	return;
}

bitV *codeToBit(code s)
{
    //    printf("Code length in c2b: %d\n", s.l);
	bitV *a = newVec(s.l);
	uint32_t cont = 0;
	for (int32_t i = (s.l)-1; i >= 0; i--)
	{
		popCode(&s, &cont);
		if (cont > 0)
		{
			setBit(a, i);
		}
	}
	return a;
}

int main(int argc, char **argv)
{
	//get opt variables
	int option;
	opterr = 0;
	bool verbose = false;
	bool inFile = false;
	bool outFile = false;
	int input;
        char *read2;
	FILE *fileForLen;
	int output;
	//exec variables
	uint32_t *histogram = calloc(256, sizeof(uint32_t));
	code stack = newCode();
	code codeList[256];
	for (int i = 0; i < 256; i++)
	{
		codeList[i] = newCode();
	}

	while ((option = getopt(argc, argv, "vi:o:")) != -1)
	{
		switch (option)
		{
			case 'v':
			{
				verbose = true;
				break;
			}
			case 'i':
			{
				if (inFile)
				{
					fprintf(stderr, "[ARGUMENT ERROR] input file already set\n");
					return 3;
				}
				inFile = true;
				input = open(optarg, O_RDONLY);
				if (input < 0)
				{
					printf("Cannot find input file\n");
					return 0;
				}
                                read2 = malloc(strlen(optarg)+1);
                                strcpy(read2,optarg);
				fileForLen = fopen(optarg, "r");
				break;
			}
			case 'o':
			{
				if (outFile)
				{
					fprintf(stderr, "[ARGUMENT ERROR] output file already set\n");
					return 3;
				}
				outFile = true;

				FILE* hold = fopen(optarg, "w");
				fclose(hold);

				output = open(optarg, O_RDWR);
				break;
			}
			case '?':
			{
				fprintf(stderr, "[ARGUMENT ERROR] unknown arguments\n");
				return 1;
			}
			default:
			{
				fprintf(stderr, "u fucked up boy\n");
				return 2;
			}
		}
	}

// start of program run

	//MAKE HISTOGRAM
	if (inFile == false)
	{
		printf("no input file\n");
		return 1;
	}
	makeHist(input, histogram);
	//END HISTOGRAM CONSTRUCTION

	//MAKE BINARY TREE FROM HISTOGRAM
	treeNode *a = makeTree(histogram);
	//END MAKE TREE

	//BUILD THE CODE!
	buildCode(a, stack, codeList);
  //      for (int i = 0; i < 256; i++)
      //  {
    //        printf("%d\n", codeList[i].l);
      //  }
	//FINISH

	//WRITE MAGIC NUMBER
	uint32_t magic[1] = {0xdeadd00d};
	ssize_t bytesWritten;
	
	if (outFile)
	{
		bytesWritten = write(output, magic, sizeof(uint32_t));
	}
	else
	{
		bytesWritten = write(1, magic, sizeof(uint32_t));
	}
	//MAGIC NUMBER WRITTEN

	//WRITE FILE SIZE
	fseek(fileForLen, 0L, SEEK_END);
	uint64_t sz[1] = {ftell(fileForLen)};
	rewind(fileForLen);
	if (outFile)
	{
		bytesWritten = write(output, sz, 8);
	}
	else
	{
		bytesWritten = write(1, sz, 8);
	}
	//FILE SIZE WRITTEN

	//WRITE TREE SIZE
//	printf("There are %d leaves\n", leafcount);
	leafcount = ((leafcount) * 3) - 1;
	uint16_t hold2[1] = {leafcount};
	if (outFile)
	{
		bytesWritten = write(output, hold2, sizeof(uint16_t));
	}
	else
	{
		bytesWritten = write(1, hold2, sizeof(uint16_t));
	}
	//TREE SIZE WRITTEN

	//WRITE TREE
	dumpTree(a, output);
	//TREE WRITTEN

	//ENCODE FILE
        int input2;
	input2 = open(read2, O_RDONLY);
	ssize_t readthru2;
	uint8_t rt2buf[1];
	readthru2 = read(input2, rt2buf, 1);
	bitV *encodedText = codeToBit(codeList[rt2buf[0]]);
  //      printVec(encodedText);
  //      printf("length of the first code in bv: %d\n", encodedText->l);

	while (readthru2 == 1)
	{
		readthru2 = read(input2, rt2buf, 1);
		appendVec(encodedText, codeToBit(codeList[rt2buf[0]]));
//		printVec(encodedText);
//		printf("after run of loop code length is: %d\n", encodedText->l);
	}
            
//	printf("second%d\n", encodedText->l);
	
//	printf("bv to be inserted");
//	printVec(encodedText);

	

	for (uint32_t i = 0; i < encodedText->l; i++)
	{
//		printf("final bv");
//		printVec(encodedText);
	//	rt2buf[0] = valBit(encodedText, i);
//		printf("digit being inserted into output%d\n", rt2buf[0]);
		if (outFile)
		{
			write(output, encodedText->v, ((encodedText->l)/8)+1);
		}
		else
		{
			write(1, encodedText->v, ((encodedText->l)/8)+1);
		}
	}
	if (outFile == false)
	{
		char hell = '\n';
		write(1, &hell, 1);
	}

	if (verbose)
	{
		printf("\nMagic num: %x | fileSize: %lu (bits) | treeSize: %d\n", magic[0], sz[0] *8, hold2[0]);	
	}
	close(input);

	if (outFile)
	{
		close(output);
	}

	delVec(encodedText);
	free(histogram);		
	free(read2);
	//DELETE THIS
//	output ++;
	bytesWritten ++;
	//DELETE THIS
	return 0;
}
