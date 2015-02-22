#include "stack_of_func.h"
#include "types.h"
#include "main_variables.h"

#include <stdio.h>
#include <malloc.h>

void push(unsigned short args, unsigned short local, stack_func **head) {

	stack_func *new_function = (stack_func*)malloc(sizeof(stack_func));

	new_function->next = (!(*head)) ? NULL : (*head);

	new_function->sizeof_args = args;
	new_function->sizeof_local = local;
	new_function->sizeof_base_part = (local * STACK_ELEMENT_SIZE) + (12 * STACK_ELEMENT_SIZE) + (4 * STACK_ELEMENT_SIZE);

	if((*head)) {

		(*head)->sizeof_main_part = sp - STACK_ELEMENT_SIZE - bp;

	} else {

		new_function->sizeof_main_part = NULL;

	}

	(*head) = new_function;

}

void pop(stack_func **head, unsigned char *breakexec) {

	stack_func *pop_function = (stack_func*)malloc(sizeof(stack_func));

	pop_function = (*head);
	(*head) = (*head)->next;

	if(!(*head)) (*breakexec) = 1;

	free(pop_function);

}

unsigned short get_offset(stack_func **head, unsigned short func_id, unsigned short var_id) {

	stack_func *temp;
	unsigned short offset = 0;

	func_id = sizeof_stack(head) - func_id;

	temp = (*head);

	offset += temp->sizeof_base_part + (sp - temp->sizeof_base_part);

	temp = temp->next;

	func_id--;

	while(func_id) {

		offset += temp->sizeof_base_part + temp->sizeof_main_part;

		temp = temp->next;
		func_id--;

	}

	offset =+  temp->sizeof_main_part + (var_id * STACK_ELEMENT_SIZE);

	return offset;

}

unsigned short sizeof_stack(stack_func **head) {

	unsigned short count = 0;
	
	stack_func *temp = (*head);

	while(temp) {

		count++;
		temp = temp->next;

	}

	return count;

}