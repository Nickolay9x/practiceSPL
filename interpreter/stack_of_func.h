#ifndef H_STACK_OF_FUNC
#define H_STACK_OF_FUNC

// This stack to store functions properties. Top element - last called function

struct element {

	unsigned short sizeof_args;
	unsigned short sizeof_local;
	unsigned short sizeof_base_part;
	unsigned short sizeof_main_part;

	struct element* next;

};

typedef struct element stack_func;

void push(unsigned short args, unsigned short local, stack_func **head);

void pop(stack_func **head, unsigned char *breakexec);

unsigned short get_offset(stack_func **head, unsigned short func_id, unsigned short var_id);	

unsigned short sizeof_stack(stack_func **head);

#endif