#ifndef H_TYPES
#define H_TYPES

#include <stdio.h>

#define DOUBLE_SIZE 8
#define INTEGER_SIZE 8
#define STRING_ID 2

#pragma pack(push, 2)
typedef struct {

	short signature;
	size_t version;

	size_t consts_count;
	size_t consts_size;

} header;
#pragma pack(pop)

typedef enum {

	//==========
	//INVALID
	//==========

	//===LOAD===
	//=====2====

	OP_DLOAD = 2,
	OP_ILOAD,
	OP_SLOAD,

	//=====5====

	OP_DLOAD0,
	OP_ILOAD0,
	OP_SLOAD0,

	//=====8====

	OP_DLOAD1,
	OP_ILOAD1,

	OP_DLOADM1,
	OP_ILOADM1,

	//==========

	//===ADD====
	//====12====

	OP_DADD,
	OP_IADD,

	//===SUB====
	//====14====

	OP_DSUB,
	OP_ISUB,

	//===MUL====
	//====16====

	OP_DMUL,
	OP_IMUL,

	//===DIV====
	//====18====

	OP_DDIV,
	OP_IDIV,

	//===MOD====
	//====20====

	OP_IMOD,

	//===NEG====
	//====21====

	OP_DNEG,
	OP_INEG,

	//OR/AND/XOR
	//====23====

	OP_IAOR,
	OP_IAAND,
	OP_IAXOR,

	//==========

	//===PRINT==
	//====30====

	OP_DPRINT = 30,
	OP_IPRINT,
	OP_SPRINT,

	//===CONV===
	//====33====

	OP_I2D,
	OP_D2I,
	OP_S2I,

	//===STACK==
	//====36====

	OP_SWAP,
	OP_POP,

	//===VARS====
	//===LOAD===
	//====40====

	//==DOUBLE==

	OP_LOADDVAR0 = 40,
	OP_LOADDVAR1,
	OP_LOADDVAR2,
	OP_LOADDVAR3,

	//===INT====
	//====44====

	OP_LOADIVAR0,
	OP_LOADIVAR1,
	OP_LOADIVAR2,
	OP_LOADIVAR3,

	//===STR====
	//====48====

	OP_LOADSVAR0,
	OP_LOADSVAR1,
	OP_LOADSVAR2,
	OP_LOADSVAR3,

	//===STORE==
	//====52====

	//==DOUBLE==

	OP_STOREDVAR0,
	OP_STOREDVAR1,
	OP_STOREDVAR2,
	OP_STOREDVAR3,

	//===INT====
	//====56====

	OP_STOREIVAR0,
	OP_STOREIVAR1,
	OP_STOREIVAR2,
	OP_STOREIVAR3,

	//===STR====
	//====60====

	OP_STORESVAR0,
	OP_STORESVAR1,
	OP_STORESVAR2,
	OP_STORESVAR3,

	//===LOAD===
	//====64====

	OP_LOADDVAR,
	OP_LOADIVAR,
	OP_LOADSVAR,

	//===STOR===
	//====67====

	OP_STOREDVAR,
	OP_STOREIVAR,
	OP_STORESVAR,

	//===LOAD===
	//====70====

	OP_LOADCTXDVAR,
	OP_LOADCTXIVAR,
	OP_LOADCTXSVAR,

	//===STOR===
	//====73====

	OP_STORECTXDVAR,
	OP_STORECTXIVAR,
	OP_STORECTXSVAR,

	//===========

	//===CMP====
	//====80====

	OP_DCMP = 80,
	OP_ICMP,

	//===JMP====
	//====82====

	OP_JA,
	OP_LABEL,
	OP_MAIN,

	//===IF=====
	//====85====

	// '!=' '=='

	OP_IFICMPNE,
	OP_IFICMPE,

	//====87====
	//='>' '>='=

	OP_IFICMPG,
	OP_IFICMPGE,

	//====89====
	//='<' '<='=

	OP_IFICMPL,
	OP_IFICMPLE,

	//==OTHER===
	//====91====

	OP_DUMP,
	OP_STOP,

	//==FUNCS===
	//====93====

	OP_CALL,
	OP_CALLNATIVE,

	//====95====

	OP_RETURN,
	OP_BREAK

} op_type;

typedef enum {

	ERROR = 1,

	//INPUT FILE ERROR

	INPUT_NF,
	INPUT_NOP,
	INPUT_INC,

	//STACK PRINT INFO

	STACK_ND, // Not declared
	STACK_TG, // Too great

	//UNKNOWN CMD

	UNKNWN_CMD,

} error_type;

#endif