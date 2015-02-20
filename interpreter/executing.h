#ifndef H_EXECUTING
#define H_EXECUTING

#include "stack.h"

#include <stdio.h>

//PRINT ERROR MESSAGES

	void error(size_t code, unsigned  short index);

//LOAD ON TOS AND ARIPMETIC COMMANDS

	void load_cmds();
	void ariphmetic_cmds();

//PRINT TOS

	void print_cmds();

//CONVERT TOS

	void convert_cmds();

//STACK FUNCTIONS

	void stack_cmds();

//VARIABLES

	//QUICK VARIABLES

		void quick_loadvar_cmds();
		void quick_storevar_cmds();

	//LOAD/STORE VARIABLES

		void loadvar_cmds();
		void storevar_cmds();

	//LOAD/STORE FOR CYCLES

		void cycle_load_cmds();
		void cycle_store_cmds();

//CMP, JMP, LABEL, IF*

	void cmp_cmds(); 
	void lbl_cmds(stack_func **head);
	void if_cmds();

//OTHER FUNCTIONS(CALL, STOP, DUMP, BREAK)

	void other_cmds(stack_func **head);

//MAIN EXECUTE FUNCTION

	size_t execute(size_t last_cmd, unsigned char *er_flag);

#endif