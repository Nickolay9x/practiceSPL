#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "header.h"

//Clean memory before close

void clean(list **head) {

	del_list(head);

	free(registers);
	free(ip_reg);

	free(bcode_array);

}

int main(int argc, char** argv) {

	//============DATA SEG===========

	size_t i;

	char *temp;
	list *head; //list with all commands
	unsigned short analys_code;

	FILE *output_file;
	
	//===============================
	
	//============ALLOCATE===========

	bcode_array = (unsigned char*)calloc(BCODE_SIZE, sizeof(unsigned char));
	ip_reg = (reg16*)malloc(sizeof(reg16));
	registers = (reg32*)calloc(5, sizeof(reg32));

	//==============INIT=============

	head = NULL;

	init_regs(&registers, ip_reg);

	//=====CHECK AND OPEN FILE=======

	if(!argv[1]) {

		clean(&head);
		printf("Where is your fu**in' asm file");
		_getch(); //temporary
		return 0;

	}

	fopen_s(&input_file, argv[1], "r");

	if(!input_file) {

		clean(&head);
		printf("Where is your fu**in' asm file");
		_getch(); //temporary
		return 0;

	}

	//===============================

	temp = (char*)malloc(sizeof(char));
	i = 0;

	while(fgets(temp, 40, input_file)) {

		if(strlen(temp) < 2) continue;

		parse(temp, strlen(temp), &head);

	}

	fclose(input_file);

	analys_code = analysis(&head, &bcode_array);

	printf("\nAnalys result: %d\n", analys_code);

	if(analys_code != 1) {

		fopen_s(&output_file, BCODE_FILE,"wb");

		fwrite(bcode_array, sizeof(bcode_array[0]), analys_code, output_file);

		fclose(output_file);

	}

	/*for(i = 0; i < analys_code; i++)
		printf("%d ", bcode_array[i]);*/

	// !1 - Everything OKEY
	// 1 - One or more lines had error

	clean(&head);
	_getch(); //temporary
	return 0;

}

