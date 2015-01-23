#ifndef H_TRANSLATER
#define H_TRANSLATER

#include "label.h"

//=======FUNCS TO CHECK LEXEMS=========

unsigned short is_reg(char *reg);
unsigned short is_number(char *num);
unsigned short is_memory(char *addr);

size_t check_one_argument(char* arg1);
size_t check_two_arguments(char* arg1, char* arg2);
size_t check_two_arguments_shift(char* arg1, char* arg2); // For shift becase there can be ebx, <bh/ebx>

//======FUNCS TO GET LEXEMS CODE=======

unsigned char get_reg_code(char *reg);
unsigned char get_addr_code(char *addr);

//=======FUNC TO PRINT ERRORS==========

void error(size_t code, short line, char *lexeme);

//=======FUNCS TO PUT OPCODES==========

void put_opc_cmd(unsigned char code, unsigned char **bcode_array, unsigned short *iter);
void put_opc_reg(char *reg, unsigned char **bcode_array, unsigned short *iter);
void put_opc_num_16(char *num, unsigned char **bcode_array, unsigned short *iter);
void put_opc_num_32(char *num, unsigned char **bcode_array, unsigned short *iter);
void put_opc_addr(char *addr, unsigned char **bcode_array, unsigned short *iter);

//=====================================
//====FUNCS TO TRANSLATE COMMANDS======
//=====================================

void translate_dstack(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_mov(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//=============ARITHMETIC==============

void translate_add(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_sub(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_mul(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_div(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//=============INC DEC=================

void translate_inc(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_dec(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//===============SHIFT=================

void translate_ror(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_rol(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_shr(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_shl(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//===============STACK=================

void translate_push(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_pop(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//=====================================
//===============LABEL=================

void translate_label(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag, label_list **labels);

//===============JUMP==================

void translate_jmp(char *lbl_name, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag, label_list **labels, char op_code);

//==============COMPARE================

void translate_cmp(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//=============INTERRUPT===============

void translate_int(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//===============FUNCS=================

void translate_ret(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//===============LOGIC=================

void translate_and(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_or(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_xor(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);
void translate_not(list **cur_line, unsigned char **bcode_array, unsigned short *num, size_t code, short line, unsigned char *flag);

//=====================================

#endif