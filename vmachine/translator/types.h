#ifndef H_TYPES
#define H_TYPES
#define BCODE_SIZE 5000

typedef enum {

	OP_MOV_1 = 1,
	OP_MOV_2,
	OP_MOV_3,
	OP_MOV_4,

	//==ARITHMETIC==
	//======5=======

	OP_ADD_1,
	OP_ADD_2,
	OP_ADD_3,
	OP_ADD_4,

	//======9=======

	OP_SUB_1,
	OP_SUB_2,
	OP_SUB_3,
	OP_SUB_4,

	//======13======

	OP_MUL_1,
	OP_MUL_2,
	OP_MUL_3,

	//======16======

	OP_DIV_1,
	OP_DIV_2,
	OP_DIV_3,

	//======19======

	OP_INC_1,
	OP_INC_2,

	//======21======

	OP_DEC_1,
	OP_DEC_2,

	//=====SHIFT====
	//======30======

	OP_ROR_1 = 30,
	OP_ROR_2,
	OP_ROL_1,
	OP_ROL_2,

	//======34======

	OP_SHR_1,
	OP_SHR_2,
	OP_SHL_1,
	OP_SHL_2,

	//=====STACK====
	//======40======

	OP_PUSH_1 = 40,
	OP_PUSH_2,

	OP_POP,

	//====LABELS====
	//======50======

	OP_JMP_1 = 50,
	OP_JMP_2,

	//======52======

	OP_JE_1,
	OP_JE_2,

	//======54======

	OP_JNE_1,
	OP_JNE_2,

	//======56======

	OP_JB_1,
	OP_JB_2,
	OP_JL_1,
	OP_JL_2,

	//======60======

	OP_JBE_1,
	OP_JBE_2,
	OP_JLE_1,
	OP_JLE_2,

	//======64======

	OP_JNB_1,
	OP_JNB_2,
	OP_JNL_1,
	OP_JNL_2,

	//======68======

	OP_CMP_1,
	OP_CMP_2,
	OP_CMP_3,

	//==INTERRUPT===
	//======75======

	OP_INT = 75,

	//====FUNCS=====
	//======80======

	OP_CALL_1 = 80,
	OP_CALL_2,
	OP_RET,

	//====LOGIC=====
	//======90======

	OP_AND_1 = 90,
	OP_AND_2,
	OP_AND_3,

	//======93======

	OP_OR_1,
	OP_OR_2,
	OP_OR_3,

	//======96======

	OP_XOR_1,
	OP_XOR_2,
	OP_XOR_3,

	//======99======

	OP_NOT

} op_type;

typedef enum {

	ERROR = 1,
	CMD_ERROR,
	ARG1_ERROR,
	ARG2_ERROR

} error_type;

typedef enum {

	INT_10 = 10,
	INT_16 = 16,
	INT_21 = 21

} int_type;

#endif