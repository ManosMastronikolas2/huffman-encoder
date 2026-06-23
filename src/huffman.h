#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#define HASH_SZ 256

typedef struct letter{
	char letter;
	size_t freq;
	struct letter* next;
}letter_t;

//returns the encoding tree
void encode(FILE*);
//prints frequency table
void printFreqTable();

#endif