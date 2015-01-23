#ifndef H_REGS
#define H_REGS
#include "types.h"

//2 bytes register struct

typedef struct {

	char* name;
	unsigned char code;

} reg16;

//4 bytes register struct

typedef struct {

	char* name;
	unsigned char code;

	reg16 high_reg;
	reg16 low_reg;

} reg32;

void init_regs(reg32 **gpr, reg16 *ip);

#endif
