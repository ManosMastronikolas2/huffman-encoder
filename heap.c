#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heap.h"

typedef struct heap{
    word_t* arr;
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
    heap->arr = (word_t*) malloc(sizeof(word_t)*capacity);
    assert(heap->arr);
}

//inserts a new word into the minHeap that is given as an argument
void insertMin(char* word, size_t freq){

    assert(heap);

    if(heap->curr_size >= heap->capacity){

        //allocate new, bigger heap, instead of reallocating existing one, to avoid nullptr in case of memory exhaustion
        heap->capacity *= 2;
        word_t* new = (word_t*) malloc(sizeof(word_t)*heap->capacity);
        assert(new);

        memcpy(new, heap->arr, heap->curr_size*sizeof(word_t));
        
        free(heap->arr);

        heap->arr = new;
    }

    //insert at the bottom of the heap
    size_t curr = heap->curr_size;
    heap->arr[curr].word = strdup(word);
    heap->arr[curr].freq = freq;
    heap->curr_size++;


    //bubble up if needed
    size_t parent = (curr-1)/2;
    while(curr>0 && heap->arr[curr].freq < heap->arr[parent].freq){

        word_t tmp = heap->arr[curr];
        heap->arr[curr] = heap->arr[parent];
        heap->arr[parent] = tmp;

        curr = parent;
        parent = (curr-1)/2;
    }

}

//print heap
void printHeap(){
    for(size_t i = 0; i < heap->curr_size; i++){
        printf("%s : %zu\n", heap->arr[i].word, heap->arr[i].freq);
    }
}

word_t* extractMin(){

    if(heap->curr_size == 0) return NULL;
    
    word_t* min = (word_t*) malloc(sizeof(word_t));
    min->freq = heap->arr[0].freq;
    min->word = heap->arr[0].word;

    



    return min;
}