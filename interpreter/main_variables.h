#ifndef H_MAIN_VARIABLES
#define H_MAIN_VARIABLES

#include <stdio.h>

FILE *input_bcode;

unsigned char *bcode_array; //Bytecode
unsigned char *stack;

unsigned short main_id;
unsigned short count_of_funcs;

char **const_str;

unsigned short ip; //Instruction pointer 
unsigned short bp; //Base pointer
unsigned short sp; //Stack pointer

#endif