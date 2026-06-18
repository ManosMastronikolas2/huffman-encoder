#ifndef HEAP_H
#define HEAP_H

#include "huffman.h"
#include <stdio.h>

//insert a value into the minHeap
void insertMin(char*, size_t);
//extract root from minHeap
word_t* extractMin();
//init heap
void initHeap(size_t);
//print heap
void printHeap();

#endif