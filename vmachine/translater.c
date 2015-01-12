#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "header.h"

//=======FUNCS TO CHECK LEXEMS=========

//=======1 - TRUE; 0 - FALSE===========

unsigned short is_reg(char *reg) {

	size_t i;

	for(i = 0; i < 5; i++) {

		if(!strcmp(reg, registers[i].name)) {

			return 1;

		}

	}

	for(i = 0; i < 5; i++) {

		if(!strcmp(reg, registers[i].high_reg.name)) {

			return 1;

		}

	}

	return 0;

}

unsigned short is_number(char *num) {

	size_t i, len;

	len = 0;

	for(i = 0; i < strlen(num); i++) {

		if((num[i] >= 48) && (num[i] <= 57))
			len++;

	}

	if(strlen(num) == len) {

		if(atoi(num) > 32767) {

			return 0;

		}

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

		return is_reg(reg_part) ? 1 : 0;

	} else {

		return 0;

	}

}

//==1, 2, 5, 6, 7 CORRECT COMBINATION==

size_t check_two_arguments(char* arg1, char* arg2) {

	if(is_reg(arg1)) {

		if(is_reg(arg2)) return (strlen(arg1) != strlen(arg2)) ? ARG2_ERROR : 1;
		if(is_number(arg2)) return 2;
		return is_memory(arg2) ? 5 : ARG2_ERROR;

	} 

	if(is_memory(arg1)) {

		if(is_reg(arg2)) return 6;
		return is_number(arg2) ? 7 : ARG2_ERROR;

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

void error(size_t code, size_t line, char *lexeme) {

	switch(code) {

	case 2:
		printf("ERROR:\tUNKNOWN COMMAND %s\tat (%d) line\n", lexeme, line);
		break;

	case 3:
		if(!lexeme)
			printf("ERROR:\tILLEGAL AGRUMENT 1 EMPTY\tat (%d) line\n", line);
		else
			printf("ERROR:\tILLEGAL AGRUMENT 1 %s\tat (%d) line\n", lexeme, line);
		break;

	case 4:
		if(!lexeme)
			printf("ERROR:\tILLEGAL AGRUMENT 2 EMPTY\tat (%d) line\n", line);
		else
			printf("ERROR:\tILLEGAL AGRUMENT 2 %s\tat (%d) line\n", lexeme, line);
		break;

	}

}

//=======FUNCS TO PUT OPCODES==========

void put_opc_cmd(unsigned char code, unsigned char **bcode_array, size_t *iter) {

	(*bcode_array)[*iter] = code;
	(*iter)++;

}

void put_opc_reg(char *reg, unsigned char **bcode_array, size_t *iter) {

	(*bcode_array)[*iter] = get_reg_code(reg);
	(*iter)++;

}

void put_opc_num(char *num, unsigned char **bcode_array, size_t *iter) {

	short a = atoi(num);
	*((short*)(*bcode_array + *iter)) = atoi(num);
	(*iter)++;

}

void put_opc_addr(char *addr, unsigned char **bcode_array, size_t *iter) {

	(*bcode_array)[*iter] = get_addr_code(addr);
	(*iter)++;

}

//====FUNCS TO TRANSLATE COMMANDS======

void translate_mov(list **cur_line, unsigned char **bcode_array, size_t *num, size_t code, size_t line, unsigned char *flag) {

	switch(code) {

	case 1:
		put_opc_cmd(OP_MOV_1, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_reg((*cur_line)->arg2, bcode_array, num);
		break;

	case 2:
		put_opc_cmd(OP_MOV_2, bcode_array, num);
		put_opc_reg((*cur_line)->arg1, bcode_array, num);
		put_opc_num((*cur_line)->arg2, bcode_array, num);
		break;

	case 3:
		error(code, line, (*cur_line)->arg1);
		(*flag) = ERROR;
		break;

	case 4:
		error(code, line, (*cur_line)->arg2);
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