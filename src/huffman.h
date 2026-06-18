#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>

#define HASH_SZ 5

typedef struct word {
	char* word;
	size_t freq;
	struct word* next;
} word_t;

word_t** findWordFreq(char*);

#endif