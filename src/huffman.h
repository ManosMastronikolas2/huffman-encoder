#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#define HASH_SZ 256

typedef struct letter{
	char letter;
	size_t freq;
	struct letter* next;
}letter_t;

//inits freq table
void initFreqTable(void);
//updates the frequency of a letter
size_t updLetterFreq(char);
//prints table
void printFreqTable();

#endif