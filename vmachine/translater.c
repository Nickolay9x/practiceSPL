#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "header.h"
#include "translater.h"

//=======FUNCS TO CHECK LEXEMS=========

//=======1 - TRUE; 0 - FALSE===========

unsigned short is_reg(char *reg) {

	size_t i;

	for(i = 0; i < 4; i++) {

		if(!strcmp(reg, registers[i].name) || !strcmp(reg, registers[i].high_reg.name) || !strcmp(reg, registers[i].low_reg.name)) {

			return 1;

		}

	}

	return 0;

}

unsigned short is_number(char *num) {

	size_t i, len;

	len = 0;

	if(num[0] == 45)
		len++;

	for(i = 0; i < strlen(num); i++) {

		if((num[i] >= 48) && (num[i] <= 57))
			len++;

	}

	return ((strlen(num)) == len) ? 1 : 0;

}

unsigned short is_memory(char *addr) {

	char* reg_part;
	size_t i;

	if( (addr[0] == 91) && (addr[strlen(addr) - 1] == 93) ) {

		reg_part = (char*)malloc(strlen(addr) - 2);

		for(i = 1; i < strlen(addr) - 1; i++) {

			reg_part[i - 1] = addr[i];

		}

		reg_part[i - 1] = '\0';

		if(strlen("ebx") == strlen(reg_part)) {

			return is_reg(reg_part) ? 1 : 0;

		} else {

			return 0;

		}

	} else {

		return 0;

	}

}

//==1, 2, 5, 6, 7 CORRECT COMBINATION==

size_t check_one_argument(char* arg1) {

	if(is_reg(arg1)) return 1;
	if(is_number(arg1) && ((unsigned int)atoi(arg1) < 65536)) return 2;
	return is_memory(arg1) ? 5 : ARG1_ERROR;

}

size_t check_two_arguments(char* arg1, char* arg2) {

	if(is_reg(arg1)) {

		if(is_reg(arg2)) return (strlen(arg1) == strlen(arg2)) ? 1 : ARG2_ERROR;

		if(is_number(arg2)) {

			if(strlen(arg1) == 2) {
				
				return ((atoi(arg2) <= 65535) && (atoi(arg2) >= 0)) ? 2 : ARG2_ERROR;

			} else {
				
				return ((atoi(arg2) <= 2147483647) && (atoi(arg2) >= -2147483647)) ? 2 : ARG2_ERROR;

			}

		}

		return is_memory(arg2) ? 5 : ARG2_ERROR;

	} 

	if(is_memory(arg1)) {

		if(is_reg(arg2)) return 6;
		return is_number(arg2) ? 7 : ARG2_ERROR;

	}

	return ARG1_ERROR;

}

size_t check_two_arguments_shift(char* arg1, char* arg2) {

	if(is_reg(arg1)) {

		return (!strcmp(arg2, "cl")) ? 1 : ARG2_ERROR;

	}

	return ARG1_ERROR;

}

//=====================================

//======FUNCS TO GET LEXEMS CODE=======

unsigned char get_reg_code(char *reg) {

	size_t i;

	for(i = 0; i < 5; i++) {

		if(!strcmp(reg, registers[i].name)) {

			return registers[i].code;

		}

	}

	for(i = 0; i < 5; i++) {

		if(!strcmp(reg, registers[i].high_reg.name)) {

			return registers[i].high_reg.code;

		}

	}

	for(i = 0; i < 5; i++) {

		if(!strcmp(reg, registers[i].low_reg.name)) {

			return registers[i].low_reg.code;

		}

	}

	return 77;

}

unsigned char get_addr_code(char *addr) {

	char* reg_part;
	size_t i;

	reg_part = (char*)malloc(strlen(addr) - 2);

	for(i = 1; i < strlen(addr) - 1; i++) {

		reg_part[i - 1] = addr[i];

	}

	reg_part[i - 1] = '\0';

	return get_reg_code(reg_part);

}

//=======FUNC TO PRINT ERRORS==========

void error(size_t code, short line, char *lexeme) {

	switch(code) {

	case CMD_ERROR:
		printf("ERROR:\tUNKNOWN COMMAND %s at (%d) line\n", lexeme, line);
		break;

	case ARG1_ERROR:
		if(!lexeme)
			printf("ERROR:\tILLEGAL AGRUMENT 1 EMPTY at (%d) line\n", line);
		else
			printf("ERROR:\tILLEGAL AGRUMENT 1 %s at (%d) line\n", lexeme, line);
		break;

	case ARG2_ERROR:
		if(!lexeme)
			printf("ERROR:\tILLEGAL AGRUMENT 2 EMPTY at (%d) line\n", line);
		else
			printf("ERROR:\tILLEGAL AGRUMENT 2 %s at (%d) line\n", lexeme, line);
		break;

	case DSTACK_NF:
		printf("WARNING: STACK NOT DECLARE. DEFAULT VALUE: 250\n");
		break;

	case DSTACK_TG:
		printf("WARNING: STACK CAN NOT BE MORE THAN 64 000. NOW DEFAULT VALUE: 250\n");
		break;

	case LABEL_AGAIN:
		printf("ERROR: %s LABEL HAS ALREADY TRANSLATED AND USED EARLY. (%d)\n", lexeme, line);
		break;

	case LABEL_NF:
		printf("ERROR: %s LABEL IS NOT FOUND. (%d)\n", lexeme, line);
		break;

	}

}

//=======FUNCS TO PUT OPCODES==========

void put_opc_cmd(unsigned char code, unsigned char **bcode_array, unsigned short *iter) {

	(*bcode_array)[*iter] = code;
	(*iter)++;

}

void put_opc_reg(char *reg, unsigned char **bcode_array, unsigned short *iter) {

	(*bcode_array)[*iter] = get_reg_code(reg);
	(*iter)++;

}

void put_opc_num_8(char *num, unsigned char **bcode_array, unsigned short *iter) {

	(*bcode_array)[*iter] = (char)atoi(num);
	(*iter)++;

}

void put_opc_num_16(char *num, unsigned char **bcode_array, unsigned short *iter) {

	*((unsigned short*)(*bcode_array + *iter)) = (unsigned short)atoi(num);
	(*iter) += 2;

}

void put_opc_num_32(char *num, unsigned char **bcode_array, unsigned short *iter) {

	int a = atoi(num);
	*((int*)(*bcode_array + *iter)) = atoi(num);
	(*iter) += 4;

}

void put_opc_addr(char *addr, unsigned char **bcode_array, unsigned short *iter) {

	(*bcode_array)[*iter] = get_addr_code(addr);
	(*iter)++;

}

//====FUNCS TO TRANSLATE COMMANDS======

void translate_dstack(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 2:

		if(atoi((*cur_line)->arg1) <= 64000) {

			put_opc_num_16((*cur_line)->arg1, bcode_array, num);

		} else {

			error(DSTACK_TG, line, (*cur_line)->arg1);
			(*flag) = ERROR;
			put_opc_num_16("250", bcode_array, num);

		}

		break;

	default:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;

		error(DSTACK_NF, line, (*cur_line)->arg1);
		put_opc_num_16("250", bcode_array, num);

		break;

	}

}

void translate_mov(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_MOV_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_MOV_2, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		if(strlen((*cur_line)->arg1) == 2) {

			put_opc_num_16((*cur_line)->arg2, bcode_array, num);

		} else {

			put_opc_num_32((*cur_line)->arg2, bcode_array, num);

		}
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_MOV_3, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_addr((*cur_line)->arg2, bcode_array, num);
		break;

	case 6:
		put_opc_cmd(OP_MOV_4, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 7:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_add(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_ADD_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_ADD_2, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);

		if(strlen((*cur_line)->arg1) == 2) {

			put_opc_num_16((*cur_line)->arg2, bcode_array, num);

		} else {

			put_opc_num_32((*cur_line)->arg2, bcode_array, num);

		}

		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_ADD_3, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_addr((*cur_line)->arg2, bcode_array, num);
		break;

	case 6:
		put_opc_cmd(OP_ADD_4, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 7:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_sub(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_SUB_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_SUB_2, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		
		if(strlen((*cur_line)->arg1) == 2) {

			put_opc_num_16((*cur_line)->arg2, bcode_array, num);

		} else {

			put_opc_num_32((*cur_line)->arg2, bcode_array, num);

		}

		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_SUB_3, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_addr((*cur_line)->arg2, bcode_array, num);
		break;

	case 6:
		put_opc_cmd(OP_SUB_4, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 7:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_mul(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_MUL_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_MUL_2, bcode_array, num);
		put_opc_num_32((*cur_line)->arg1, bcode_array, num);

		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_MUL_3, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		break;

	}

}

void translate_div(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_DIV_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_DIV_2, bcode_array, num);
		put_opc_num_32((*cur_line)->arg1, bcode_array, num);
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_DIV_3, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		break;

	}

}

void translate_inc(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_INC_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		break;

	case 2:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_INC_2, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		break;

	}

}

void translate_dec(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_DEC_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		break;

	case 2:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_DEC_2, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		break;

	}

}

void translate_ror(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_ROR, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_rol(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_ROL, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_shr(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_SHR, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_shl(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_SHL, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_push(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:

		if(strlen((*cur_line)->arg1) == 2) {

			error(ARG1_ERROR, line, (*cur_line)->arg1);
			(*flag) = ERROR;
			break;

		}

		put_opc_cmd(OP_PUSH_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_PUSH_2, bcode_array, num);
		put_opc_num_32((*cur_line)->arg1, bcode_array, num);
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_PUSH_3, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		break;

	}

}

void translate_pop(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:

		if(strlen((*cur_line)->arg1) == 2) {

			error(ARG1_ERROR, line, (*cur_line)->arg1);
			(*flag) = ERROR;
			break;

		}

		put_opc_cmd(OP_POP_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		break;

	case 2:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_POP_2, bcode_array, num);
		put_opc_addr((*cur_line)->arg1, bcode_array, num);
		break;

	}

}

void translate_label(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag, label_list **labels) {

	label_list *iterator = (*labels);
	char *temp = (char*)malloc(15);

	switch(code) {

	case 0:
		error(LABEL_AGAIN, line, (*cur_line)->cmd);
		(*flag) = ERROR;
		break;

	default:
		while(iterator) {

			if(!strcmp(iterator->label.name, (*cur_line)->cmd) && !iterator->label.translated) {

				iterator->label.translated = 1;
				put_opc_cmd(OP_LABEL, bcode_array, num);
				_itoa_s(iterator->label.addr, temp, 15, 10);
				put_opc_num_16(temp, bcode_array, num);
				break;

			}

			iterator = iterator->next;

		}

	}

}

void translate_jmp(char *lbl_name, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag, label_list **labels, char op_code) {

	label_list *iterator = (*labels);
	char *temp = (char*)malloc(15);

	switch(code) {

	case 0:
		error(LABEL_NF, line, lbl_name);
		(*flag) = ERROR;
		break;

	default:
		while(iterator) {

			if(!strcmp(iterator->label.name, lbl_name)) {

				put_opc_cmd(op_code, bcode_array, num);
				_itoa_s(iterator->label.addr, temp, 15, 10);
				put_opc_num_16(temp, bcode_array, num);
				break;

			}

			iterator = iterator->next;

		}

	}

}

void translate_cmp(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_CMP_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_CMP_2, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		
		if(strlen((*cur_line)->arg1) == 2) {

			put_opc_num_16((*cur_line)->arg2, bcode_array, num);

		} else {

			put_opc_num_32((*cur_line)->arg2, bcode_array, num);

		}

		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 5:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 6:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 7:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	}

}

void translate_int(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 2:

		if((atoi((*cur_line)->arg1) > 255) || (atoi((*cur_line)->arg1) < 1)) {

			error(ARG1_ERROR, line, (*cur_line)->arg1);
			(*flag) = ERROR;
			break;

		}

		put_opc_cmd(OP_INT, bcode_array, num);
		put_opc_num_8((*cur_line)->arg1, bcode_array, num);
		break;

	default:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	}

}

void translate_ret(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	put_opc_cmd(OP_RET, bcode_array, num);

}

void translate_and(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_AND_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_AND_2, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		
		if(strlen((*cur_line)->arg1) == 2) {

			put_opc_num_16((*cur_line)->arg2, bcode_array, num);

		} else {

			put_opc_num_32((*cur_line)->arg2, bcode_array, num);

		}

		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_AND_3, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_addr((*cur_line)->arg2, bcode_array, num);
		break;

	case 6:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 7:
		error(ARG1_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_or(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_OR_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_OR_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		
		if(strlen((*cur_line)->arg1) == 2) {

			put_opc_num_16((*cur_line)->arg2, bcode_array, num);

		} else {

			put_opc_num_32((*cur_line)->arg2, bcode_array, num);

		}

		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_OR_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_addr((*cur_line)->arg2, bcode_array, num);
		break;

	case 6:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 7:
		error(ARG1_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_xor(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_XOR_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_XOR_2, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		
		if(strlen((*cur_line)->arg1) == 2) {

			put_opc_num_16((*cur_line)->arg2, bcode_array, num);

		} else {

			put_opc_num_32((*cur_line)->arg2, bcode_array, num);

		}

		break;

	case 3:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(ARG2_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	case 5:
		put_opc_cmd(OP_XOR_3, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_addr((*cur_line)->arg2, bcode_array, num);
		break;

	case 6:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 7:
		error(ARG1_ERROR, line, (*cur_line)->arg2);
		(*flag) = ERROR;
		break;

	}

}

void translate_not(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_NOT, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		break;

	default:
		error(ARG1_ERROR, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	}

}