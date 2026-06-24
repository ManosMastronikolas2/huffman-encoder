#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#define HASH_SZ 256

typedef struct letter{
	char letter;
	size_t freq;
	struct letter* next; //used to build lists
    struct letter* lc;//used to build the tree
    struct letter* rc; 
}letter_t;


//takes input file, encodes it and outputs the encoded stream in out file
void encode(FILE*, FILE*);
//prints frequency table
void printFreqTable();

#endif