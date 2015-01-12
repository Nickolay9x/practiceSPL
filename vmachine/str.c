#include <stdio.h>
#include <malloc.h>
#include "list.h"
#include "str.h"

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

//Translate commands

void translate(list **head, BYTE **bcode_array) {

	//============DATA SEG===========

	size_t i, j;
	size_t n_line;

	list *temp;

	//===============================

	//==========INITIALIZE===========

	i = 0; j = 0; 
	n_line = 0;

	temp = (*head);

	//===============================

	printf("%s\n", temp->next->arg2);

	(*bcode_array)[1] = 33;

}