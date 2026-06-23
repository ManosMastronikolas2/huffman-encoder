#ifndef HEAP_H
#define HEAP_H

#include "huffman.h"
#include <stdio.h>

//insert a value into the minHeap
void insertMin(char, size_t, letter_t*, letter_t*);
//extract root from minHeap
letter_t* extractMin();
//init heap
void initHeap(size_t);
//print heap
void printHeap();

#endif