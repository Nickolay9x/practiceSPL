#include <malloc.h>
#include <stdio.h>
#include "regs.h"

//Init registers name and codes

void init_regs(reg32 **gpr, reg16 *ip, reg32 *esp) {

	// General Purpose Registers

	(*gpr)[0].high_reg.name = "ah";
	(*gpr)[0].high_reg.code = 10;
	(*gpr)[0].name = "eax";
	(*gpr)[0].code = 0;

	(*gpr)[1].high_reg.name = "bh";
	(*gpr)[1].high_reg.code = 11;
	(*gpr)[1].name = "ebx";
	(*gpr)[1].code = 1;
	
	(*gpr)[2].high_reg.name = "ch";
	(*gpr)[2].high_reg.code = 12;
	(*gpr)[2].name = "ecx";
	(*gpr)[2].code = 2;

	(*gpr)[3].high_reg.name = "dh";
	(*gpr)[3].high_reg.code = 13;
	(*gpr)[3].name = "edx";
	(*gpr)[3].code = 3;

	(*gpr)[4].high_reg.name = "navail";
	(*gpr)[4].high_reg.code = 14;
	(*gpr)[4].name = "esp";
	(*gpr)[4].code = 4;

	// IP

	ip->name = "ip";
	ip->code = 5;

}