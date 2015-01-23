#ifndef H_TYPES
#define H_TYPES
#define BCODE_SIZE 5000
#define BCODE_FILE "main"

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

	OP_ROR = 30,
	OP_ROL,

	//======32======

	OP_SHR,
	OP_SHL,

	//=====STACK====
	//======40======

	OP_PUSH_1 = 40,
	OP_PUSH_2,
	OP_PUSH_3,

	OP_POP_1,
	OP_POP_2,

	//=====LABEL====
	//======50======

	OP_LABEL = 50,

	//=====JMP======
	//======51======

	OP_JMP,

	//======52======

	OP_JE,

	//======53======

	OP_JNE,

	//======54======

	OP_JB,
	OP_JL,

	//======56======

	OP_JBE,
	OP_JLE,

	//======58======

	OP_JNB,
	OP_JNL,

	//======CMP=====
	//======60======

	OP_CMP_1,
	OP_CMP_2,

	//==MAIN LABEL==
	//======62======

	OP_MAIN,

	//==INTERRUPT===
	//======70======

	OP_INT = 70,

	//====FUNCS=====
	//======80======

	OP_CALL = 80,
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

	OP_NOT,
	
	//======100=====

	OP_DSTACK,
	OP_DCODE,

} op_type;

typedef enum {

	ERROR = 1,
	CMD_ERROR,
	ARG1_ERROR,
	ARG2_ERROR,
	DSTACK_NF,
	DSTACK_TG,
	LABEL_AGAIN,
	LABEL_NF,
	DCODE_NF,
	DCODE_AGAIN,
	MAIN_NF

} error_type;

typedef enum {

	INT_10 = 10,
	INT_16 = 16,
	INT_21 = 21

} int_type;

#endif