#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "str.h"
#include "translater.h"

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

	size_t n_line;
	size_t counter;

	size_t check_args;

	list *current_line;

	unsigned char flag;

	//===============================

	//==========INITIALIZE===========

	i = 0; j = 0; 
	n_line = 0;
	counter = 0;

	current_line = (*head);

	flag = 0;

	//===============================

	while(current_line) {

		n_line++;

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

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

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

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

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

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

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

				check_args = check_two_arguments(current_line->arg1, current_line->arg2);

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

		//LATER

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

		//LATER

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

	return (flag == 1) ? ERROR : 0;

}