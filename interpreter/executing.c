#include "main_variables.h"
#include "types.h"
#include "executing.h"

#include <stdlib.h>

void error(size_t code, unsigned short index) {

	switch(code) {

	case ERROR:
		printf("ERROR DURING EXECUTING THIS PROGRAM\n");
		break;

	case INPUT_NF:
		printf("FIRST AGRUMENT MUST BE BYTECODE FILE\n");
		break;

	case INPUT_NOP:
		printf("FILE COULD NOT OPEN\n");
		break;

	case INPUT_INC:
		printf("FILE IS NOT A PROGRAM\n");
		break;

	case STACK_ND:
		printf("STACK IS NOT DECLARED. DEFAULT VALUE: 500 B\n");
		break;

	case STACK_TG:
		printf("STACK MORE THAN 64 KB. DEFAULT VALUE: 500 B\n");
		break;

	case UNKNWN_CMD:
		printf("UNKNOWN COMMAND. IP: %d\n", index);

	}

}

//LOAD ON TOS AND ARIPMETIC COMMANDS

	void load_cmds() {

		switch(bcode_array[ip]) {

		// D/I/SLOAD

		case OP_DLOAD:
			break;

		case OP_ILOAD:
			break;

		case OP_SLOAD:
			break;

		// D/I/SLOAD0

		case OP_DLOAD0:
			break;

		case OP_ILOAD0:
			break;

		case OP_SLOAD0:
			break;

		//D/ILOAD1

		case OP_DLOAD1:
			break;

		case OP_ILOAD1:
			break;

		//D/ILOADM1

		case OP_DLOADM1:
			break;

		case OP_ILOADM1:
			break;

		default:
			break;

		}

	}

	void ariphmetic_cmds() {

		switch(bcode_array[ip]) {

		//ADD

		case OP_DADD:
			break;

		case OP_IADD:
			break;

		//SUB

		case OP_DSUB:
			break;

		case OP_ISUB:
			break;

		//MUL

		case OP_DMUL:
			break;

		case OP_IMUL:
			break;

		//DIV

		case OP_DDIV:
			break;

		case OP_IDIV:
			break;

		//MOD(%)

		case OP_IMOD:
			break;

		//NEGATIVE(-1 * n)

		case OP_DNEG:
			break;

		case OP_INEG:
			break;

		//LOGIC OPERATIONS

		case OP_IAOR:
			break;

		case OP_IAAND:
			break;

		case OP_IAXOR:
			break;

		//OTHER

		default:
			break;

		}

	}

//PRINT TOS

	void print_cmds() {

		switch(bcode_array[ip]) {

		case OP_DPRINT:
			break;

		case OP_IPRINT:
			break;

		case OP_SPRINT:
			break;
	

		default:
			break;

		}

	}

//CONVERT TOS

	void convert_cmds() {

		switch(bcode_array[ip]) {

		case OP_I2D:
			break;

		case OP_D2I:
			break;

		case OP_S2I:
			break;
	

		default:
			break;

		}

	}

//STACK FUNCTIONS

	void stack_cmds() {

		switch(bcode_array[ip]) {

		case OP_SWAP:
			break;

		case OP_POP:
			break;


		default: 
			break;

		}

	}

//VARIABLES

	//QUICK VARIABLES

		void quick_loadvar_cmds() {

			switch(bcode_array[ip]) {

			//DOUBLE

			case OP_LOADDVAR0:
				break;

			case OP_LOADDVAR1:
				break;

			case OP_LOADDVAR2:
				break;

			case OP_LOADDVAR3:
				break;

			//INTEGER

			case OP_LOADIVAR0:
				break;

			case OP_LOADIVAR1:
				break;

			case OP_LOADIVAR2:
				break;

			case OP_LOADIVAR3:
				break;

			//STRING

			case OP_LOADSVAR0:
				break;

			case OP_LOADSVAR1:
				break;

			case OP_LOADSVAR2:
				break;

			case OP_LOADSVAR3:
				break;



			default: 
				break;

			}

		}

		void quick_storevar_cmds() {

			switch(bcode_array[ip]) {

			//DOUBLE

			case OP_STOREDVAR0:
				break;

			case OP_STOREDVAR1:
				break;

			case OP_LOADDVAR2:
				break;

			case OP_STOREDVAR3:
				break;

			//INTEGER

			case OP_STOREIVAR0:
				break;

			case OP_STOREIVAR1:
				break;

			case OP_STOREIVAR2:
				break;

			case OP_STOREIVAR3:
				break;

			//STRING

			case OP_STORESVAR0:
				break;

			case OP_STORESVAR1:
				break;

			case OP_STORESVAR2:
				break;

			case OP_STORESVAR3:
				break;



			default: 
				break;

			}

		}

	//LOAD/STORE VARIABLES

		void loadvar_cmds() {

			switch(bcode_array[ip]) {

			case OP_LOADDVAR:
				break;

			case OP_LOADIVAR:
				break;

			case OP_LOADSVAR:
				break;

			default: 
				break;

			}

		}

		void storevar_cmds() {

			switch(bcode_array[ip]) {

			case OP_STOREDVAR:
				break;

			case OP_STOREIVAR:
				break;

			case OP_STORESVAR:
				break;

			default: 
				break;

			}

		}

	//LOAD/STORE FOR CYCLES

		void cycle_load_cmds() {

			switch(bcode_array[ip]) {

			case OP_LOADCTXDVAR:
				break;

			case OP_LOADCTXIVAR:
				break;

			case OP_LOADCTXSVAR:
				break;

			default: 
				break;

			}

		}

		void cycle_store_cmds() {

			switch(bcode_array[ip]) {

			case OP_STORECTXDVAR:
				break;

			case OP_STORECTXIVAR:
				break;

			case OP_STORECTXSVAR:
				break;

			default: 
				break;

			}

		}

//CMP, JMP, LABEL, IF*

	void cmp_cmds() {

		switch(bcode_array[ip]) {

		case OP_DCMP:
			break;

		case OP_ICMP:
			break;

		default: 
			break;

		}

	}

	void lbl_cmds() {

		switch(bcode_array[ip]) {

		case OP_JA:
			break;

		case OP_LABEL:
			break;

		case OP_MAIN:
			break;

		default: 
			break;

		}

	}

	void if_cmds() {

		switch(bcode_array[ip]) {

		// '!=' '=='

		case OP_IFICMPNE:
			break;

		case OP_IFICMPE:
			break;

		//='>' '>='=

		case OP_IFICMPG:
			break;

		case OP_IFICMPGE:
			break;


		//='<' '<='=

		case OP_IFICMPL:
			break;

		case OP_IFICMPLE:
			break;


		default: 
			break;

		}

	}

//OTHER FUNCTIONS(CALL, STOP, DUMP, BREAK)

	void other_cmds() {

		switch(bcode_array[ip]) {

		//FOR DEBUG

		case OP_DUMP:
			break;

		case OP_STOP:
			break;

		case OP_BREAK:
			break;

		//FOR FUNCTIONS

		case OP_CALL:
			break;

		case OP_CALLNATIVE:
			break;

		case OP_RETURN:
			break;


		default: 
			break;

		}

	}

size_t execute(size_t last_cmd, unsigned char *er_flag) {

	unsigned char breakpoint;

	double dnumber;
	long long int inumber;
	char *string;

	ip = 0; // START POINT
	breakpoint = 0;

	while(!breakpoint) {

//=========SWITCH=============

	//LOAD ON TOS AND ARIPMETIC COMMANDS

		if((bcode_array[ip] >= OP_DLOAD) && (bcode_array[ip] < OP_DADD)) load_cmds();
		if((bcode_array[ip] > OP_ILOADM1) && (bcode_array[ip] < OP_DPRINT)) ariphmetic_cmds();
	
	//PRINT TOS

		if((bcode_array[ip] > OP_IAXOR) && (bcode_array[ip] < OP_I2D)) print_cmds();

	//CONVERT TOS
	
		if((bcode_array[ip] > OP_SPRINT) && (bcode_array[ip] < OP_SWAP)) convert_cmds();

	//STACK FUNCTIONS

		if((bcode_array[ip] > OP_S2I) && (bcode_array[ip] < OP_LOADDVAR0)) stack_cmds();

	//======VARIABLES=====

		//QUICK VARIABLES

			if((bcode_array[ip] > OP_POP) && (bcode_array[ip] < OP_STOREDVAR0)) quick_loadvar_cmds();
			if((bcode_array[ip] > OP_LOADSVAR3) && (bcode_array[ip] < OP_LOADDVAR)) quick_storevar_cmds();

		//LOAD/STORE VARIABLES

			if((bcode_array[ip] > OP_STORESVAR3) && (bcode_array[ip] < OP_STOREDVAR)) loadvar_cmds();
			if((bcode_array[ip] > OP_LOADSVAR) && (bcode_array[ip] < OP_LOADCTXDVAR)) storevar_cmds();

		//LOAD/STORE FOR CYCLES

			if((bcode_array[ip] > OP_STORESVAR) && (bcode_array[ip] < OP_STORECTXDVAR)) cycle_load_cmds();
			if((bcode_array[ip] > OP_LOADCTXSVAR) && (bcode_array[ip] < OP_DCMP)) cycle_store_cmds();

	//====================

	//CMP, JMP, LABEL, IF*

		if((bcode_array[ip] > OP_STORECTXSVAR) && (bcode_array[ip] < OP_JA)) cmp_cmds(); 
		if((bcode_array[ip] > OP_ICMP) && (bcode_array[ip] < OP_IFICMPNE)) lbl_cmds();
		if((bcode_array[ip] > OP_MAIN) && (bcode_array[ip] < OP_DUMP)) if_cmds();

	//OTHER FUNCTIONS(CALL, STOP, DUMP, BREAK)

		if((bcode_array[ip] > OP_IFICMPLE) && (bcode_array[ip] < OP_BREAK + 1)) other_cmds();

	//ELSE

		if((bcode_array[ip] > OP_BREAK) && (bcode_array[ip] < OP_DLOAD)) {
			
			error(UNKNWN_CMD, ip);
			(*er_flag) = 1;

		}

//============================

		ip++;

		if(ip >= last_cmd) breakpoint = 1;

	}

	if((*er_flag)) error(ERROR, 0);

	return (!(*er_flag)) ? EXIT_SUCCESS : ERROR;

}