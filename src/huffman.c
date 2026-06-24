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

//traverse huffman tree and build codes
void buildCodes(letter_t* root, char* code, int depth, char codes[256][256] ){

    if(!root) return;

    if(root->letter != '\0'){
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->letter], code);
        return;
    }

    code[depth] = '0';
    buildCodes(root->lc, code, depth + 1, codes);

    code[depth] = '1';
    buildCodes(root->rc, code, depth + 1, codes);
}

void encode(FILE* in, FILE* out){

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

    letter_t* l, *r;
    while(getSize()>1){

        l = extractMin();
        r = extractMin();

        insertMin('\0', l->freq+r->freq, l, r);

    }

    letter_t* root = extractMin();

    assert(root);

    char codes[256][256] = {0};
    char letter_code[256] = {0};
    buildCodes(root, letter_code, 0, codes);


    printf("---------------ENCODED FILE-----------------\n");
    //output encoded file
    rewind(in);
    while((c=fgetc(in)) != EOF){
        fputs(codes[(unsigned int)c], out);
        printf("%s", codes[(unsigned int)c]);
    }

}