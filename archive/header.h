#ifndef H_HEADER
#define H_HEADER
#include "regs.h"
#include "str.h"


//File with asm code

FILE* input_file;

//Byte code array

unsigned char* bcode_array;

//Registers

reg32* registers;
reg16* ip_reg;
reg32* esp_reg;

#endif
