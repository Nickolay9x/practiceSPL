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
	
	//===============================
	
	//============ALLOCATE===========

	bcode_array = (BYTE*)calloc(BCODE_SIZE, sizeof(BYTE));
	ip_reg = (reg16*)malloc(sizeof(reg16));
	registers = (reg32*)calloc(5, sizeof(reg32));
	head = NULL;

	init_regs(&registers, ip_reg);

	//=====CHECK AND OPEN FILE=======

	if(!argv[1]) {

		clean(&head);
		printf("Where is your fu**in' asm file");
		_getch(); //temporary
		return 0;

	}

	fopen_s(&input, argv[1], "r");

	if(!input) {

		clean(&head);
		printf("Where is your fu**in' asm file");
		_getch(); //temporary
		return 0;

	}

	//===============================

	temp = (char*)malloc(sizeof(char));
	i = 0;

	while(fgets(temp, 20, input)) {

		if(strlen(temp) < 2) continue;

		parse(temp, strlen(temp), &head);

	}

	translate(&head, &bcode_array);

	printf("%c\n", bcode_array[1]);

	clean(&head);
	_getch(); //temporary
	return 0;

}

