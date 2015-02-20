#include "stack.h"

#include <stdio.h>
#include <malloc.h>

void push(unsigned short args, unsigned short local, stack_func **head) {

	stack_func *new_function = (stack_func*)malloc(sizeof(stack_func));

	new_function->next = (!(*head)) ? NULL : (*head);

	new_function->sizeof_args = args;
	new_function->sizeof_local = local;

	(*head) = new_function;

}

void pop(stack_func **head) {

	stack_func *pop_function = (stack_func*)malloc(sizeof(stack_func));

	pop_function = (*head);
	(*head) = (*head)->next;

	free(pop_function);

}