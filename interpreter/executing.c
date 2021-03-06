#include "main_variables.h"
#include "types.h"
#include "executing.h"

#include <stdlib.h>
#include <string.h>

void error(size_t code, unsigned short index) {

	switch(code) {

	case ERROR:
		printf("\n\nERROR DURING EXECUTING THIS PROGRAM\n");
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
		break;

	case FREEZE:
		printf("\nPROGRAM FROZEN. IP: %d\nPRESS ANY KEY TO CONTINUE\n", index);
		break;

	case ID_OUT_OF_BOUNDS:
		printf("ID IS OUT OF BOUNDS. USE LOAD/STORECTX. IP: %d\n", index);
		break;

	}

}

//LOAD ON TOS AND ARIPMETIC COMMANDS

	void load_cmds() {

		short temp;

		switch(bcode_array[ip]) {

		// D/I/SLOAD

		case OP_DLOAD:
			memcpy_s(&(*(stack + sp)), STACK_ELEMENT_SIZE, &(*(bcode_array + ip + 1)), STACK_ELEMENT_SIZE);

			sp += STACK_ELEMENT_SIZE;
			ip += STACK_ELEMENT_SIZE;

			break;

		case OP_ILOAD:
			memcpy_s(&(*(stack + sp)), STACK_ELEMENT_SIZE, &(*(bcode_array + ip + 1)), STACK_ELEMENT_SIZE);

			sp += STACK_ELEMENT_SIZE;
			ip += STACK_ELEMENT_SIZE;

			break;

		case OP_SLOAD:
			temp = *((short*)(bcode_array + ip + 1));
			*((__int64*)(stack + sp)) = (__int64)temp;

			sp += STACK_ELEMENT_SIZE;
			ip += STRING_ID;

			break;

		// D/I/SLOAD0

		case OP_DLOAD0:
			*((double*)(stack + sp)) = (double)0.0;
			sp =+ STACK_ELEMENT_SIZE;

			break;

		case OP_ILOAD0:
			*((__int64*)(stack + sp)) = (__int64)0;
			sp += STACK_ELEMENT_SIZE;

			break;

		case OP_SLOAD0:
			*((__int64*)(stack + sp)) = (__int64)0;
			sp += STACK_ELEMENT_SIZE;

			break;

		//D/ILOAD1

		case OP_DLOAD1:
			*((double*)(stack + sp)) = (double)1.0;
			sp =+ STACK_ELEMENT_SIZE;

			break;

		case OP_ILOAD1:
			*((__int64*)(stack + sp)) = (__int64)1;
			sp += STACK_ELEMENT_SIZE;

			break;

		//D/ILOADM1

		case OP_DLOADM1:
			*((double*)(stack + sp)) = (double)-1.0;
			sp =+ STACK_ELEMENT_SIZE;

			break;

		case OP_ILOADM1:
			*((__int64*)(stack + sp)) = (__int64)-1;
			sp += STACK_ELEMENT_SIZE;

			break;

		default:
			break;

		}

		ip++;

	}

	void ariphmetic_cmds() {

		double dtemp;
		__int64 itemp;


		switch(bcode_array[ip]) {

		//ADD

		case OP_DADD:
			dtemp = *((double*)(stack + sp - STACK_ELEMENT_SIZE)) + *((double*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((double*)(stack + sp)) = dtemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		case OP_IADD:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) + *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		//SUB

		case OP_DSUB:
			dtemp = *((double*)(stack + sp - STACK_ELEMENT_SIZE)) - *((double*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((double*)(stack + sp)) = dtemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		case OP_ISUB:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) - *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		//MUL

		case OP_DMUL:
			dtemp = *((double*)(stack + sp - STACK_ELEMENT_SIZE)) * *((double*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((double*)(stack + sp)) = dtemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		case OP_IMUL:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) * *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		//DIV

		case OP_DDIV:
			dtemp = *((double*)(stack + sp - STACK_ELEMENT_SIZE)) / *((double*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((double*)(stack + sp)) = dtemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		case OP_IDIV:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) / *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		//MOD(%)

		case OP_IMOD:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) % *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		//NEGATIVE(-1 * n)

		case OP_DNEG:
			*((double*)(stack + sp - STACK_ELEMENT_SIZE)) *=  -1.0;

			break;

		case OP_INEG:
			*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) *=  -1;

			break;

		//LOGIC OPERATIONS

		case OP_IAOR:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) | *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		case OP_IAAND:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) & *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		case OP_IAXOR:
			itemp = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) ^ *((__int64*)(stack + sp - (2 * STACK_ELEMENT_SIZE)));

			sp -= 2 * STACK_ELEMENT_SIZE;

			*((__int64*)(stack + sp)) = itemp;
			sp += STACK_ELEMENT_SIZE;

			break;

		//OTHER

		default:
			break;

		}

		ip++;

	}

//PRINT TOS

	void print_cmds() {

		switch(bcode_array[ip]) {

		case OP_DPRINT:
			sp -= STACK_ELEMENT_SIZE;
			printf("\nPOP AND PRINT DOUBLE FROM TOS: %f\n", *((double*)(stack + sp)));

			break;

		case OP_IPRINT:
			sp -= STACK_ELEMENT_SIZE;
			printf("\nPOP AND PRINT INTEGER FROM TOS: %d\n", *((__int64*)(stack + sp)));

			break;

		case OP_SPRINT:
			sp -= STACK_ELEMENT_SIZE;
			printf("\nPOP AND PRINT CONSTANT STRING: %s\n", const_str[*((__int64*)(stack + sp))]);

			break;
	

		default:
			break;

		}

		ip++;

	}

//CONVERT TOS

	void convert_cmds() {

		switch(bcode_array[ip]) {

		case OP_I2D:
			*((double*)(stack + sp - STACK_ELEMENT_SIZE)) =  (double)*((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

			break;

		case OP_D2I:
			*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) =  (__int64)*((double*)(stack + sp - STACK_ELEMENT_SIZE));

			break;

		case OP_S2I:
			*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) = atoi(const_str[*((__int64*)(stack + sp - STACK_ELEMENT_SIZE))]);

			break;
	

		default:
			break;

		}

		ip++;

	}

//STACK FUNCTIONS

	void stack_cmds() {

		switch(bcode_array[ip]) {

		case OP_SWAP:
			*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) ^= *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE)); // a = a ^ b
			*((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE)) ^= *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)); // b = b ^ a
			*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) ^= *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE)); // a = a ^ b

			break;

		case OP_POP:
			sp -= STACK_ELEMENT_SIZE;

			break;


		default: 
			break;

		}

		ip++;

	}

//VARIABLES

	//QUICK VARIABLES

		void quick_loadvar_cmds(stack_func **head) {

			switch(bcode_array[ip]) {

			//DOUBLE

			case OP_LOADDVAR0:
				*((double*)(stack + sp)) = *((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 12)));

				break;

			case OP_LOADDVAR1:
				*((double*)(stack + sp)) = *((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 11)));

				break;

			case OP_LOADDVAR2:
				*((double*)(stack + sp)) = *((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 10)));

				break;

			case OP_LOADDVAR3:
				*((double*)(stack + sp)) = *((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 9)));

				break;

			//INTEGER

			case OP_LOADIVAR0:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 8)));

				break;

			case OP_LOADIVAR1:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 7)));

				break;

			case OP_LOADIVAR2:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 6)));

				break;

			case OP_LOADIVAR3:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 5)));

				break;

			//STRING

			case OP_LOADSVAR0:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 4)));

				break;

			case OP_LOADSVAR1:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 3)));

				break;

			case OP_LOADSVAR2:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 2)));

				break;

			case OP_LOADSVAR3:
				*((__int64*)(stack + sp)) = *((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 1)));

				break;



			default: 
				break;

			}

			ip++;
			sp += STACK_ELEMENT_SIZE;

		}

		void quick_storevar_cmds(stack_func **head) {

			switch(bcode_array[ip]) {

			//DOUBLE

			case OP_STOREDVAR0:
				*((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 12))) = *((double*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STOREDVAR1:
				*((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 11))) = *((double*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_LOADDVAR2:
				*((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 10))) = *((double*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STOREDVAR3:
				*((double*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 9))) = *((double*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			//INTEGER

			case OP_STOREIVAR0:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 8))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STOREIVAR1:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 7))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STOREIVAR2:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 6))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STOREIVAR3:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 5))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			//STRING

			case OP_STORESVAR0:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 4))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STORESVAR1:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 3))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STORESVAR2:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 2))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;

			case OP_STORESVAR3:
				*((__int64*)(stack + bp - (*head)->sizeof_local - (STACK_ELEMENT_SIZE * 1))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));

				break;


			default: 
				break;

			}

			ip++;
			sp -= STACK_ELEMENT_SIZE;

		}

	//LOAD/STORE VARIABLES

		void loadvar_cmds(stack_func **head) {

			unsigned short sizeof_func;
			unsigned short offset;

			switch(bcode_array[ip]) {

			case OP_LOADDVAR:
				offset = *((unsigned short*)(bcode_array + ip + 1));

				if( (offset > 0) && (offset <= ( ((*head)->sizeof_base_part / 8) + (*head)->sizeof_args + 1) ) )
					*((double*)(stack + sp)) = *((double*)( stack + bp - (offset * STACK_ELEMENT_SIZE) ));
				else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp -= STACK_ELEMENT_SIZE;

				}

				break;

			case OP_LOADIVAR:
				offset = *((unsigned short*)(bcode_array + ip + 1));

				if( (offset > 0) && (offset <= ( ((*head)->sizeof_base_part / 8) + (*head)->sizeof_args + 1) ) )
					*((__int64*)(stack + sp)) = *((__int64*)( stack + bp - (offset * 8) ));
				else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp -= STACK_ELEMENT_SIZE;

				}

				break;

			case OP_LOADSVAR:
				offset = *((unsigned short*)(bcode_array + ip + 1));

				if( (offset > 0) && (offset <= ( ((*head)->sizeof_base_part / 8) + (*head)->sizeof_args + 1) ) )
					*((__int64*)(stack + sp)) = *((__int64*)( stack + bp - (offset * 8) ));
				else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp -= STACK_ELEMENT_SIZE;

				}

				break;

			default: 
				break;

			}

			ip++;
			ip += LABEL_SIZE;

			sp += STACK_ELEMENT_SIZE;

		}

		void storevar_cmds(stack_func **head) {

			unsigned short sizeof_func;
			unsigned short offset;

			switch(bcode_array[ip]) {

			case OP_STOREDVAR:
				offset = *((unsigned short*)(bcode_array + ip + 1));

				if( (offset > 0) && (offset <= ( ((*head)->sizeof_base_part / 8) + (*head)->sizeof_args + 1) ) )

				if( (offset > 0) && (offset <= ((*head)->sizeof_base_part / 8)) )
					*((double*)( stack + bp - (offset * 8) )) = *((double*)(stack + sp - STACK_ELEMENT_SIZE));
				else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp += STACK_ELEMENT_SIZE;

				}

				break;

			case OP_STOREIVAR:
				offset = *((unsigned short*)(bcode_array + ip + 1));

				if( (offset > 0) && (offset <= ( ((*head)->sizeof_base_part / 8) + (*head)->sizeof_args + 1) ) )
					*((__int64*)( stack + bp - (offset * 8) )) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));
				else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp += STACK_ELEMENT_SIZE;

				}

				break;

			case OP_STORESVAR:
				offset = *((unsigned short*)(bcode_array + ip + 1));

				if( (offset > 0) && (offset <= ( ((*head)->sizeof_base_part / 8) + (*head)->sizeof_args + 1) ) )
					*((__int64*)( stack + bp - (offset * 8) )) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE));
				else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp += STACK_ELEMENT_SIZE;

				}

				break;

			default: 
				break;

			}

			ip++;
			ip += LABEL_SIZE;

			sp -= STACK_ELEMENT_SIZE;

		}

	//LOAD/STORE FOR CYCLES

		void cycle_load_cmds(stack_func **head) {

			unsigned short offset;

			switch(bcode_array[ip]) {

			case OP_LOADCTXDVAR: // context, id
				if( (*((unsigned short*)(bcode_array + ip + 1)) > 0) && (*((unsigned short*)(bcode_array + ip + 1)) < sizeof_stack(head)) ) {

					offset = get_offset( head, *((unsigned short*)(bcode_array + ip + 1)), *((unsigned short*)(bcode_array + ip + 3)) );
					*((double*)(stack + sp)) = *((double*)(stack + sp - offset));

				} else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp -= STACK_ELEMENT_SIZE;

				}

				break;

			case OP_LOADCTXIVAR:
				if( (*((unsigned short*)(bcode_array + ip + 1)) > 0) && (*((unsigned short*)(bcode_array + ip + 1)) < sizeof_stack(head)) ) {

					offset = get_offset( head, *((unsigned short*)(bcode_array + ip + 1)), *((unsigned short*)(bcode_array + ip + 3)) );
					*((__int64*)(stack + sp)) = *((__int64*)(stack + sp - offset));

				} else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp -= STACK_ELEMENT_SIZE;

				}

				break;

			case OP_LOADCTXSVAR:
				if( (*((unsigned short*)(bcode_array + ip + 1)) > 0) && (*((unsigned short*)(bcode_array + ip + 1)) < sizeof_stack(head)) ) {

					offset = get_offset( head, *((unsigned short*)(bcode_array + ip + 1)), *((unsigned short*)(bcode_array + ip + 3)) );
					*((__int64*)(stack + sp)) = *((__int64*)(stack + sp - offset));

				} else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp -= STACK_ELEMENT_SIZE;

				}

				break;

			default: 
				break;

			}

			sp += STACK_ELEMENT_SIZE;

			ip++;
			ip += 4;

		}

		void cycle_store_cmds(stack_func **head) {

			unsigned short offset;

			switch(bcode_array[ip]) {

			case OP_STORECTXDVAR:
				if( (*((unsigned short*)(bcode_array + ip + 1)) > 0) && (*((unsigned short*)(bcode_array + ip + 1)) < sizeof_stack(head)) ) {

					offset = get_offset( head, *((unsigned short*)(bcode_array + ip + 1)), *((unsigned short*)(bcode_array + ip + 3)) );
					*((double*)(stack + sp - offset)) = *((double*)(stack + sp));

				} else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp += STACK_ELEMENT_SIZE;

				}

				break;

			case OP_STORECTXIVAR:
				if( (*((unsigned short*)(bcode_array + ip + 1)) > 0) && (*((unsigned short*)(bcode_array + ip + 1)) < sizeof_stack(head)) ) {

					offset = get_offset( head, *((unsigned short*)(bcode_array + ip + 1)), *((unsigned short*)(bcode_array + ip + 3)) );
					*((__int64*)(stack + sp - offset)) = *((__int64*)(stack + sp));

				} else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp += STACK_ELEMENT_SIZE;

				}

				break;

			case OP_STORECTXSVAR:
				if( (*((unsigned short*)(bcode_array + ip + 1)) > 0) && (*((unsigned short*)(bcode_array + ip + 1)) < sizeof_stack(head)) ) {

					offset = get_offset( head, *((unsigned short*)(bcode_array + ip + 1)), *((unsigned short*)(bcode_array + ip + 3)) );
					*((__int64*)(stack + sp - offset)) = *((__int64*)(stack + sp));

				} else {

					error(ID_OUT_OF_BOUNDS, ip);
					sp += STACK_ELEMENT_SIZE;

				}

				break;

			default: 
				break;

				sp -= STACK_ELEMENT_SIZE;

				ip++;
				ip += 4;

			}

		}

//CMP, JMP, LABEL, IF*

	void cmp_cmds() {

		switch(bcode_array[ip]) {

		case OP_DCMP:
			sp -= STACK_ELEMENT_SIZE;
			*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) = (*((double*)(stack + sp)) > *((double*)(stack + sp - STACK_ELEMENT_SIZE))) ? (__int64)1 : ( (*((double*)(stack + sp)) == *((double*)(stack + sp - STACK_ELEMENT_SIZE))) ? (__int64)0 : (__int64)-1);

			break;

		case OP_ICMP:
			sp -= STACK_ELEMENT_SIZE;
			*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) = (*((__int64*)(stack + sp)) > *((__int64*)(stack + sp - STACK_ELEMENT_SIZE))) ? (__int64)1 : ( (*((__int64*)(stack + sp)) == *((__int64*)(stack + sp - STACK_ELEMENT_SIZE))) ? (__int64)0 : (__int64)-1);

			break;

		default: 
			break;

		}

	}

	void lbl_cmds(stack_func **head) {

		switch(bcode_array[ip]) {

		case OP_JA:
			ip = *((unsigned short*)(bcode_array + ip + 1)) - 1;

			break;

		case OP_LABEL:
			ip += LABEL_SIZE;

			break;

		case OP_MAIN:
			sp += STACK_ELEMENT_SIZE; // Return value

			*((__int64*)(stack + sp)) = (__int64)0;
			*((__int64*)(stack + sp + (STACK_ELEMENT_SIZE * 1))) = (unsigned __int64)sp;
			*((__int64*)(stack + sp + (STACK_ELEMENT_SIZE * 2))) = (unsigned __int64)ip;
			sp += STACK_ELEMENT_SIZE * 3;

			ip++;
			push(*((unsigned short*)(bcode_array + ip)), *((unsigned short*)(bcode_array + ip + sizeof((*head)->sizeof_args))), head);

			ip += sizeof((*head)->sizeof_args) + sizeof((*head)->sizeof_local) - 1;
			sp += (STACK_ELEMENT_SIZE * 12) + ((*head)->sizeof_local * 8); // LOCAL VARIABLES AND D/I/SVAR[0-3]
			bp = sp;

			break;

		default: 
			break;

		}

		ip++;

	}

	void if_cmds() {

		switch(bcode_array[ip]) {

		// '!=' '=='

		case OP_IFICMPNE:
			ip = (*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) != *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE))) ? *((unsigned short*)(bcode_array + ip + 1)) - 1 : ip;

			break;

		case OP_IFICMPE:
			ip = (*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) == *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE))) ? *((unsigned short*)(bcode_array + ip + 1)) - 1 : ip;

			break;

		//='>' '>='=

		case OP_IFICMPG:
			ip = (*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) > *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE))) ? *((unsigned short*)(bcode_array + ip + 1)) - 1 : ip;

			break;

		case OP_IFICMPGE:
			ip = (*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) >= *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE))) ? *((unsigned short*)(bcode_array + ip + 1)) - 1 : ip;

			break;


		//='<' '<='=

		case OP_IFICMPL:
			ip = (*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) < *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE))) ? *((unsigned short*)(bcode_array + ip + 1)) - 1 : ip;

			break;

		case OP_IFICMPLE:
			ip = (*((__int64*)(stack + sp - STACK_ELEMENT_SIZE)) <= *((__int64*)(stack + sp - 2 * STACK_ELEMENT_SIZE))) ? *((unsigned short*)(bcode_array + ip + 1)) - 1 : ip;

			break;


		default: 
			break;

		}

		ip++;

	}

//OTHER FUNCTIONS(CALL, STOP, DUMP, BREAK)

	void other_cmds(stack_func **head, unsigned char *breakexec) {

		size_t i;

		switch(bcode_array[ip]) {

		//FOR DEBUG

		case OP_DUMP:
			printf("\nDUMP TOS(DOUBLE): %f\n", *((double*)(stack + sp - STACK_ELEMENT_SIZE)));
			printf("\nDUMP TOS(INTEGER): %f\n", *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)));

			break;

		case OP_STOP:
			error(FREEZE, ip);

			for(i = 0; i < 1000; i++)
				printf("%d ", stack[i]);

			_getch();

			break;

		case OP_BREAK:
			break;

		//FOR FUNCTIONS

		case OP_CALL:
			sp += STACK_ELEMENT_SIZE; // Return value
			*((unsigned __int64*)(stack + sp)) = (unsigned __int64)bp;
			*((unsigned __int64*)(stack + sp + STACK_ELEMENT_SIZE)) = (unsigned __int64)sp;
			*((unsigned __int64*)(stack + sp + STACK_ELEMENT_SIZE * 2)) = (unsigned __int64)(ip + 2);

			ip = *((unsigned short*)(bcode_array + ip + 1));
			push(*((unsigned short*)(bcode_array + ip + 3)), *((unsigned short*)(bcode_array + ip + 3 + 2)), head);
			sp += STACK_ELEMENT_SIZE * 3;

			ip += 1 + 2 + 4 - 1; //sizeof(OP_FUNC) + sizeof(CURRENT_IP) + sizeof(local) + sizeof(args)
			sp += (STACK_ELEMENT_SIZE * 12) + ((*head)->sizeof_local * 8); // LOCAL VARIABLES AND D/I/SVAR[0-3]
			bp = sp;

			break;

		case OP_CALLNATIVE:
			break;

		case OP_FUNC:
			break;

		case OP_RETURN:

			if(sp != bp)
				*((__int64*)(stack + bp - ((*head)->sizeof_local * STACK_ELEMENT_SIZE) - (STACK_ELEMENT_SIZE * 12) - (STACK_ELEMENT_SIZE * 4))) = *((__int64*)(stack + sp - STACK_ELEMENT_SIZE)); // TOS as a return value
			else
				*((__int64*)(stack + bp - ((*head)->sizeof_local * STACK_ELEMENT_SIZE) - (STACK_ELEMENT_SIZE * 12) - (STACK_ELEMENT_SIZE * 2))) -= STACK_ELEMENT_SIZE; // void function

			sp = bp - (STACK_ELEMENT_SIZE * 12) - ((*head)->sizeof_local * 8) - STACK_ELEMENT_SIZE; // sp -> ip

			ip = (unsigned short)*((__int64*)(stack + sp - (STACK_ELEMENT_SIZE * 0)));
			bp = (unsigned short)*((__int64*)(stack + sp - (STACK_ELEMENT_SIZE * 2)));
			sp = (unsigned short)*((__int64*)(stack + sp - (STACK_ELEMENT_SIZE * 1)));

			pop(head, breakexec);

			break;


		default: 
			break;

		}

		ip++;

	}

size_t execute(size_t last_cmd, unsigned char *er_flag) {

	unsigned char breakpoint;

	stack_func *head;

	ip = main_id; // START POINT. 

	sp = 0;
	bp = 0;

	breakpoint = 0;

	head = NULL;

	while(!breakpoint) {

		//printf("%d ", bcode_array[ip]);

//=========SWITCH=============

	//LOAD ON TOS AND ARIPMETIC COMMANDS

		if((bcode_array[ip] >= OP_DLOAD) && (bcode_array[ip] < OP_DADD)) { load_cmds(); continue; }
		if((bcode_array[ip] > OP_ILOADM1) && (bcode_array[ip] < OP_DPRINT)) { ariphmetic_cmds(); continue; }
	
	//PRINT TOS

		if((bcode_array[ip] > OP_IAXOR) && (bcode_array[ip] < OP_I2D)) { print_cmds(); continue; }

	//CONVERT TOS
	
		if((bcode_array[ip] > OP_SPRINT) && (bcode_array[ip] < OP_SWAP)) { convert_cmds(); continue; }

	//STACK FUNCTIONS

		if((bcode_array[ip] > OP_S2I) && (bcode_array[ip] < OP_LOADDVAR0)) { stack_cmds(); continue; }

	//======VARIABLES=====

		//QUICK VARIABLES

			if((bcode_array[ip] > OP_POP) && (bcode_array[ip] < OP_STOREDVAR0)) { quick_loadvar_cmds(&head); continue; }
			if((bcode_array[ip] > OP_LOADSVAR3) && (bcode_array[ip] < OP_LOADDVAR)) { quick_storevar_cmds(&head); continue; }

		//LOAD/STORE VARIABLES

			if((bcode_array[ip] > OP_STORESVAR3) && (bcode_array[ip] < OP_STOREDVAR)) { loadvar_cmds(&head); continue; }
			if((bcode_array[ip] > OP_LOADSVAR) && (bcode_array[ip] < OP_LOADCTXDVAR)) { storevar_cmds(&head); continue; }

		//LOAD/STORE FOR CYCLES

			if((bcode_array[ip] > OP_STORESVAR) && (bcode_array[ip] < OP_STORECTXDVAR)) { cycle_load_cmds(&head); continue; }
			if((bcode_array[ip] > OP_LOADCTXSVAR) && (bcode_array[ip] < OP_DCMP)) { cycle_store_cmds(&head); continue; }

	//====================

	//CMP, JMP, LABEL, IF*

		if((bcode_array[ip] > OP_STORECTXSVAR) && (bcode_array[ip] < OP_JA)) { cmp_cmds(); continue; } 
		if((bcode_array[ip] > OP_ICMP) && (bcode_array[ip] < OP_IFICMPNE)) { lbl_cmds(&head); continue; }
		if((bcode_array[ip] > OP_MAIN) && (bcode_array[ip] < OP_DUMP)) { if_cmds(); continue; }

	//OTHER FUNCTIONS(CALL, STOP, DUMP, BREAK)

		if((bcode_array[ip] > OP_IFICMPLE) && (bcode_array[ip] < OP_BREAK + 1)) { other_cmds(&head, &breakpoint); continue; }

	//ELSE

		if((bcode_array[ip] > OP_BREAK) && (bcode_array[ip] < OP_DLOAD)) {
			
			error(UNKNWN_CMD, ip);
			(*er_flag) = 1;

			ip++;

		}

//============================

		if(ip >= last_cmd) breakpoint = 1;

	}

	if((*er_flag)) error(ERROR, 0);

	return (!(*er_flag)) ? EXIT_SUCCESS : ERROR;

}