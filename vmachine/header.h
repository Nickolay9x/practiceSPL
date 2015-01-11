#include "types.h"
#include "regs.h"
#include "list.h"
#include "str.h"


#ifndef H_HEADER
#define H_HEADER

//File with asm code

FILE* input;

//Byte code array

BYTE* bcode_array;

//Registers

reg32* registers;
reg16* ip_reg;

#endif