#ifndef H_STACK
#define H_STACK

// This stack to store functions properties. Top element - last called function

struct element {

	unsigned short sizeof_args;
	unsigned short sizeof_local;

	struct element* next;

};

typedef struct element stack_func;

void push(unsigned short args, unsigned short local, stack_func **head);

void pop(stack_func **head, unsigned char *breakexec);

#endif