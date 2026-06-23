#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heap.h"

typedef struct heap{
    letter_t* arr; //TODO: Convert to void* so it is not tied to huffman.h
    size_t curr_size;
    size_t capacity;
} heap_t;

heap_t* heap = NULL;
//initialize an array heap with given capacity
void initHeap(size_t capacity){

    heap = (heap_t*) malloc(sizeof(heap_t));
    assert(heap);
    heap->capacity = capacity;
    heap->curr_size = 0;
    heap->arr = (letter_t*) malloc(sizeof(letter_t)*capacity);
    for(size_t i=0;i<capacity;i++){
        heap->arr[i].next = NULL;
        heap->arr[i].lc = NULL;
        heap->arr[i].rc = NULL;
    }
    assert(heap->arr);
}

//inserts a new word into the minHeap that is given as an argument
void insertMin(char letter, size_t freq, letter_t* lc, letter_t* rc){

    assert(heap);

    if(heap->curr_size >= heap->capacity){

        //allocate new, bigger heap, instead of reallocating existing one, to avoid nullptr in case of memory exhaustion
        heap->capacity *= 2;
        letter_t* new = (letter_t*) malloc(sizeof(letter_t)*heap->capacity);
        assert(new);

        memcpy(new, heap->arr, heap->curr_size*sizeof(letter_t));
        
        free(heap->arr);

        heap->arr = new;
    }

    //insert at the bottom of the heap
    size_t curr = heap->curr_size;
    heap->arr[curr].letter = letter;
    heap->arr[curr].freq = freq;
    heap->arr[curr].lc = lc;
    heap->arr[curr].rc = rc;
    heap->curr_size++;


    //bubble up if needed
    size_t parent = (curr-1)/2;
    while(curr>0 && heap->arr[curr].freq < heap->arr[parent].freq){

        letter_t tmp = heap->arr[curr];
        heap->arr[curr] = heap->arr[parent];
        heap->arr[parent] = tmp;

        curr = parent;
        parent = (curr-1)/2;
    }

}

//print heap
void printHeap(){
    printf("---------------HEAP-----------------\n");
    for(size_t i = 0; i < heap->curr_size; i++){
        printf("%c : %zu\n", heap->arr[i].letter, heap->arr[i].freq);
    }
}

letter_t* extractMin(){

    if(heap->curr_size == 0) return NULL;
    
    letter_t* min = (letter_t*) malloc(sizeof(letter_t));
    min->freq = heap->arr[0].freq;
    min->letter = heap->arr[0].letter;
    min->next = NULL;
    min->lc = NULL;
    min->rc = NULL;


    heap->arr[0] = heap->arr[heap->curr_size-1];
    heap->curr_size--;

    size_t curr = 0;
    size_t left = 2 * curr + 1;
    size_t right = 2 * curr + 2;
    
    while(left < heap->curr_size) {
        size_t smallest = curr;

        if(heap->arr[left].freq < heap->arr[smallest].freq) smallest = left;

        if(right < heap->curr_size && heap->arr[right].freq < heap->arr[smallest].freq) smallest = right;

        if(smallest == curr) break; 

        letter_t tmp = heap->arr[curr];
        heap->arr[curr] = heap->arr[smallest];
        heap->arr[smallest] = tmp;

        curr = smallest;
        left = 2 * curr + 1;
        right = 2 * curr + 2;
    }


    return min;
}