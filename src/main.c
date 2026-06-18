#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "heap.h"

int main(int argc, char** argv){


    if(argc < 3){
        printf("Usage: ./huffman <in_filename> <out_filename>\n");
        return -1;
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    if(!in){
        printf("Error opening input file!\n");
        return -1;
    }

    if(!out){
        printf("Error opening output file!\n");
        return -1;
    }

    char* txt;
    long size;

    //determine input size to allocate char array
    fseek(in, 0L, SEEK_END);
    size = ftell(in);
    rewind(in);

    txt = (char*) malloc((size+1)*sizeof(char)); //this is where the contents of the file will be stored
    if(!txt){
        printf("MemAlloc failed!\n");
        fclose(in);
        fclose(out);
        free(txt);
        return -1;
    }

    //read file into char array
    if(fread(txt, size, 1, in) != 1){
        printf("File reading failed!\n");
        fclose(in);
        fclose(out);
        free(txt);
        return -1;
    }

    txt[size] = '\0';
    /*huffman code here*/

    word_t** words_list = findWordFreq(txt); //find freq of all words and store it in a word struct hash table
    initHeap(1024); //init a minHeap with a capacity of 1024 entries (more than enough for starters)
    //add every {word,freq} pair to minHeap
    for(int i=0;i<HASH_SZ;i++){
        word_t* chain = words_list[i];
        while(chain){
            insertMin(chain->word, chain->freq);
            chain = chain->next;
        }
    }

    printHeap(); //for error checking the heap


    fclose(in);
    fclose(out);
    free(txt);

    return 0;
}