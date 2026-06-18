#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "huffman.h"


int hash(char *word){

    int sum=0;
    int i=0;
    while(word[i]!='\0'){
        sum += (int) word[i];
        i++;
    }

    return sum%HASH_SZ;
}



//returns a list with word_t structs for all the distinct words in the string
word_t** findWordFreq(char* str){

    const char *delimiters = " \t\r\n,.!?;:\"()[]{}";
    word_t** hashmap = (word_t**) malloc(HASH_SZ*sizeof(word_t*));

    for(int i=0;i<HASH_SZ;i++) hashmap[i] = NULL;

    char* word = strtok(str, delimiters);
    while(word){
        for(size_t i=0;i<strlen(word);i++) word[i] = (char)tolower((unsigned char)word[i]);; 
        
        int hashval = hash(word);
        word_t* chain = hashmap[hashval];
        while(chain && strcmp(chain->word, word)) chain = chain->next;

        if(!chain){
            word_t* new = (word_t*) malloc(sizeof(word_t));
            new->word = strdup(word);
            new->freq = 1;

            new->next = hashmap[hashval];
            hashmap[hashval] = new;
        }else{
            chain->freq++;
        }


        word = strtok(NULL, delimiters);
    }


    return hashmap;
}
