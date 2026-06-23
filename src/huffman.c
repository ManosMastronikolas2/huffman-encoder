#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "huffman.h"
#include "heap.h"



letter_t* freq_table[HASH_SZ]; //hash table to store {letter, freq} pairs


int hash(char c){
    return ((int)c)%HASH_SZ;
}

//initializes freq table
void initFreqTable(void){

    for(int i=0;i<HASH_SZ;i++) freq_table[i] = NULL;

}

//updates the frequency of a letter in the hash table
void updLetterFreq(char c){

    int hash_val = hash(c);

    letter_t* chain = freq_table[hash_val];

    while(chain && chain->letter != c) chain = chain->next;

    if(!chain){ //if letter not found, insert

        letter_t* new = (letter_t*) malloc(sizeof(letter_t));
        assert(new);

        new->letter = c;
        new->freq = 1;
        new->next = freq_table[hash_val];
        new->lc = NULL;
        new->rc = NULL;
        freq_table[hash_val] = new;

        return;

    }
    
    chain->freq++;

}

//for debugging
void printFreqTable(){

    printf("---------------FREQTABLE-----------------\n");

    for(int i=0;i<HASH_SZ;i++){
        letter_t* chain = freq_table[i];
        while(chain){
            printf("%c : %zu\n", chain->letter, chain->freq);
            chain = chain->next;
        }
    }
}

void encode(FILE* in){

    char c;

    initHeap(1024);

    //calculate each letter's frequency
    while((c=fgetc(in)) != EOF){
        updLetterFreq(c);
    }
    
    //construct minHeap with {letter, frequency} entries
    for(int i=0;i<HASH_SZ;i++){
        letter_t* chain = freq_table[i];
        while(chain){
            insertMin(chain->letter, chain->freq, NULL, NULL);
            chain = chain->next;
        }
    }

    //construct tree

   // while(){}

}