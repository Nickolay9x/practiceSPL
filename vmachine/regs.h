#include "types.h"

#ifndef H_REGS
#define H_REGS

//2 bytes register struct

typedef struct {

	char* name;
	WORD code;

} reg16;

//4 bytes register struct

typedef struct {

	char* name;
	WORD code;

	reg16 high_reg;

} reg32;

void init_regs(reg32** gpr, reg16* ip);

#endif