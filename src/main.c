#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

//TODO: Make this for general binary files, not just text
int main(int argc, char** argv){


    if(argc < 3){
        printf("Usage: ./huffman <in_filename> <out_filename>\n");
        return -1;
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    if(!in){
        printf("Error opening input file %s !\n", argv[1]);
        return -1;
    }

    if(!out){
        printf("Error opening output file %s !\n", argv[2]);
        return -1;
    }

    encode(in,out);


    fclose(in);
    fclose(out);

    return 0;
}