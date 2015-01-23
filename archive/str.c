#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "str.h"
#include "translater.h"

short get_size_of_string(list **cur_line) {

	short count = 0;

	if(!strcmp((*cur_line)->cmd, "ret"))
		return 1;

	if(!strcmp((*cur_line)->cmd, ".stack"))
		return 2;

	if(!strcmp((*cur_line)->cmd, "int"))
		return 2;

	if((*cur_line)->cmd)
		count++;

	if((*cur_line)->arg1) {

		if(is_reg((*cur_line)->arg1)) {
		
			count++;

			if(strlen((*cur_line)->arg1) == 2) {

				if((*cur_line)->arg2) {
				
					if(is_reg((*cur_line)->arg2) || is_memory((*cur_line)->arg2)) {
		
						count++;

					}

					if(is_number((*cur_line)->arg2)) {

						count += 2;

					}

				}

				return count;

			} else {

				if((*cur_line)->arg2) {

					if(is_reg((*cur_line)->arg2) || is_memory((*cur_line)->arg2)) {
		
						count++;

					}

					if(is_number((*cur_line)->arg2)) {

						count += 4;

					}

				}

				return count;

			}

		}

		if(is_number((*cur_line)->arg1)) {
			
			count+=4;
			return count;

		}

		if(is_memory((*cur_line)->arg1)) {
			
			count++;
			if((*cur_line)->arg1) {

				return (is_reg((*cur_line)->arg2)) ? count + 1 : 0;

			} else {

				return count;

			}

		}

		if(!(*cur_line)->arg2) {

			count += 2;

		}

		return count;

	} else {

		return count;

	}

}

void tolower_case(char *str) {

	size_t len, i;

	len = strlen(str);

	for(i = 0; i < len; i++) {

		str[i] += ((str[i] >= 65) && (str[i] <= 90)) ? 32 : 0;

	}

}

//Parse string from file and add to list

void parse(char *str, size_t length, list **head) {

	//============DATA SEG===========

	size_t i, j;
	size_t f_pos, l_pos, len;
	size_t cnt;

	char *cmd, *arg1, *arg2;

	//===============================

	//==========INITIALIZE===========

	i = 0; j = 0; cnt = 0;

	cmd = NULL; arg1 = NULL; arg2 = NULL;

	//===============================

	//====GET CMD ARG1 and ARG2======

	while(str[i]) {

		//Skip spaces and other control chars

		if((str[i] <= 32) || str[i] == 44) {


			i++;
			continue;

		} else {

			if((i == 0) || (str[i - 1] <= 32)) f_pos = i;

			if((str[i + 1] <= 32) || (str[i + 1] == 44)) {
				
				l_pos = i;
				cnt++;

				//Get cmd

				if(cnt == 1) {

					len = l_pos - f_pos + 2;
					cmd = (char*)malloc(len);

					for(j = 0; j <= l_pos; j++) {

						cmd[j] = str[j + f_pos];

					}

					cmd[len - 1] = 0;

				}

				//---------

				//Get arg1

				if(cnt == 2) {

					len = l_pos - f_pos + 2;
					arg1 = (char*)malloc(len);

					for(j = 0; j <= l_pos; j++) {

						arg1[j] = str[j + f_pos];

					}

					arg1[len - 1] = 0;

					if(length == (l_pos + 2)) arg2 = NULL;

				}

				//---------

				//Get arg2

				if(cnt == 3) {

					len = l_pos - f_pos + 2;
					arg2 = (char*)malloc(len);

					for(j = 0; j <= l_pos; j++) {

						arg2[j] = str[j + f_pos];

					}

					arg2[len - 1] = 0;

				}

				//---------

			}

			i++;

		}

	}

	//===============================

	append(head, cmd, arg1, arg2);

}

//Analysis commands

unsigned char analysis(list **head, unsigned char **bcode_array) {

	//============DATA SEG===========

	size_t i, j;

	short n_line;
	unsigned short counter;

	size_t check_args;

	list *current_line;

	label_list *labels;

	unsigned char flag, stack;

	char *temp;

	//===============================

	//==========INITIALIZE===========

	i = 0; j = 0; 
	n_line = 0;
	counter = 0;

	current_line = (*head);

	labels = NULL;

	flag = 0;
	stack = 1;

	//===============================

	//=======FIRST ITERRATION========
	//==============LABELS===========

	while(current_line) {
		
		if(current_line->cmd) {

			if(!current_line->arg1 && !current_line->arg2 && strcmp(current_line->cmd, "ret")) {

				if(is_label(current_line->cmd)) {

					if(add_new_label(current_line->cmd, counter, &labels))
						counter += 3;

				}

			} else {

				counter += get_size_of_string(&current_line);

			}

		}

		current_line = current_line->next;

	}

	//===============================

	counter = 0;

	current_line = (*head);

	//=======SECOND ITERRATION=======

	while(current_line) {

		n_line++;
		//============.STACK=============

		if(!strcmp(current_line->cmd, ".stack") && (n_line == 1)) {

			stack = 0;

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_dstack(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;

				error(DSTACK_NF, n_line, current_line->cmd);
				put_opc_num_16("250", bcode_array, &counter);

				current_line = current_line->next;
				continue;

			}

		} else {

			if((n_line == 1) && (stack)) {

				error(DSTACK_NF, n_line, current_line->cmd);
				put_opc_num_16("250", bcode_array, &counter);

			}

		}

		//===============================
		//=============MOV===============

		if(!strcmp(current_line->cmd, "mov")) {

			if(current_line->arg2) {

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

				translate_mov(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================

		//============ARITHETIC=============

		//=============ADD===============

		if(!strcmp(current_line->cmd, "add")) {

			if(current_line->arg2) {

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

				translate_add(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============SUB===============

		if(!strcmp(current_line->cmd, "sub")) {

			if(current_line->arg2) {

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

				translate_sub(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============MUL===============

		if(!strcmp(current_line->cmd, "mul")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_mul(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============DIV===============

		if(!strcmp(current_line->cmd, "div")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_div(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============INC===============

		if(!strcmp(current_line->cmd, "inc")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_inc(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============DEC===============

		if(!strcmp(current_line->cmd, "dec")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_dec(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================

		//==================================
		//===============SHIFT==============

		//=============ROR===============

		if(!strcmp(current_line->cmd, "ror")) {

			if(current_line->arg2) {

				check_args = check_two_arguments_shift(current_line->arg1, current_line->arg2);

				translate_ror(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============ROL===============

		if(!strcmp(current_line->cmd, "rol")) {

			if(current_line->arg2) {

				check_args = check_two_arguments_shift(current_line->arg1, current_line->arg2);

				translate_rol(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============SHR===============

		if(!strcmp(current_line->cmd, "shr")) {

			if(current_line->arg2) {

				check_args = check_two_arguments_shift(current_line->arg1, current_line->arg2);

				translate_shr(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============SHL===============

		if(!strcmp(current_line->cmd, "shl")) {

			if(current_line->arg2) {

				check_args = check_two_arguments_shift(current_line->arg1, current_line->arg2);

				translate_shl(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================

		//==================================
		//===============STACK==============

		//=============PUSH==============

		if(!strcmp(current_line->cmd, "push")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_push(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============POP===============

		if(!strcmp(current_line->cmd, "pop")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_pop(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================

		//==================================
		//==============LABELS==============

		//=============LABEL=============

		if((!current_line->arg1 && !current_line->arg2) && is_label(current_line->cmd)) {

			check_args = find_label(current_line->cmd, &labels);

			translate_label(&current_line, bcode_array, &counter, check_args, n_line, &flag, &labels);

			current_line = current_line->next;
			continue;

		}

		//===============================
		//=============JMP===============

		if(!strcmp(current_line->cmd, "jmp")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JMP);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JE================

		if(!strcmp(current_line->cmd, "je")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JE);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JNE===============

		if(!strcmp(current_line->cmd, "jne")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JNE);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JB================

		if(!strcmp(current_line->cmd, "jb")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JB);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JL================

		if(!strcmp(current_line->cmd, "jl")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JL);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JBE===============

		if(!strcmp(current_line->cmd, "jbe")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JBE);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JLE===============

		if(!strcmp(current_line->cmd, "jle")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JLE);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JNB===============

		if(!strcmp(current_line->cmd, "jnb")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JNB);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============JNL===============

		if(!strcmp(current_line->cmd, "jnl")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_JNL);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============CMP===============

		if(!strcmp(current_line->cmd, "cmp")) {

			if(current_line->arg2) {

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

				translate_cmp(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================

		//==================================
		//=============INTERRUPT============

		if(!strcmp(current_line->cmd, "int")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_int(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//==================================
		//==============FUNCS===============
		
		//=============CALL==============

		if(!strcmp(current_line->cmd, "call")) {

			if(!current_line->arg2) {

				temp = (char*)malloc(strlen(current_line->arg1)+1);

				for(i = 0; i < strlen(current_line->arg1); i++) {

					temp[i] = current_line->arg1[i];

				}

				temp[i] = 58; // :
				temp[i + 1] = 0; // \0

				check_args = get_label_addr(temp, &labels);

				translate_jmp(temp, bcode_array, &counter, check_args, n_line, &flag, &labels, OP_CALL);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============RET===============
		
		if(!strcmp(current_line->cmd, "ret")) {

			if(!current_line->arg1) {

				translate_ret(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG1_ERROR, n_line, current_line->arg1);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================

		//==================================
		//===============LOGIC==============
		
		//=============AND===============

		if(!strcmp(current_line->cmd, "and")) {

			if(current_line->arg2) {

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

				translate_and(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//==============OR===============

		if(!strcmp(current_line->cmd, "or")) {

			if(current_line->arg2) {

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

				translate_or(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============XOR===============

		if(!strcmp(current_line->cmd, "xor")) {

			if(current_line->arg2) {

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

				translate_xor(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================
		//=============NOT===============

		if(!strcmp(current_line->cmd, "not")) {

			if(!current_line->arg2) {

				check_args = check_one_argument(current_line->arg1);

				translate_not(&current_line, bcode_array, &counter, check_args, n_line, &flag);

				current_line = current_line->next;
				continue;

			} else {

				error(ARG2_ERROR, n_line, current_line->arg2);
				flag = ERROR;
				current_line = current_line->next;
				continue;

			}

		}

		//===============================

		//==================================

		//========UNKNOWN COMMAND========

		error(CMD_ERROR, n_line, current_line->cmd);			
		flag = ERROR;
		current_line = current_line->next;

		//===============================

	}

	clean_label_list(&labels);

	return (flag == 1) ? ERROR : 0;

}
