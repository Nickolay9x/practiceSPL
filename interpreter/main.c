#include "main_variables.h"
#include "types.h"
#include "executing.h"
#include "str.h"

#include <stdlib.h>

void clean(size_t count) {

	size_t i;

	for(i = 0; i < count; i++)
		free (const_str[i]);

}

int main(int argc, char **argv) {

	// HEADER OF BYTECODE FILE

	header header_info;

	// PROPERTIES

	size_t stack_size;
	size_t bcode_size;

	// FLAGS

	unsigned char error_flag;

	// COUNTER AND OTHER TEMPORARY VARS

	size_t i;

	error_flag = 0;

	// CHECK STACK SIZE

	if(!argv[2]) {

		error(STACK_ND, 0);
		stack_size = 500;

	} else {

		stack_size = atoi(argv[2]);
		if((stack_size > 64000) || (stack_size <= 20)) {

			error(STACK_TG, 0);
			stack_size = 500;

		}

	}

	// CHECK ARGUMENT

	if(!argv[1]) {

		error(INPUT_NF, 0);
		error(ERROR, 0);
		_getch();
		return ERROR;

	}

	fopen_s(&input_bcode, argv[1], "rb");

	// CHECK BYTECODE FILE OPENED

	if(!input_bcode) {

		error(INPUT_NOP, 0);
		error(ERROR, 0);
		_getch();
		return ERROR;

	}

	// READ THE FILE

	read_header(&header_info);
	
	if(check_header(&header_info)) {

		error(INPUT_INC, 0);
		error(ERROR, 0);
		_getch();
		return ERROR;

	}

	//GET BYTECODE SIZE

	fseek(input_bcode, 0, SEEK_END);
	bcode_size = ftell(input_bcode);
	bcode_size -= header_size(&header_info);

	//SEEK TO THE BYTECODE BEGINNING

	fseek(input_bcode, header_size(&header_info), SEEK_SET);
	bcode_array = (unsigned char*)malloc(bcode_size);

	//READ TO BYTECODE ARRAY

	for(i = 0; i < bcode_size; i++) {
	
		fread(&bcode_array[i], 1, 1, input_bcode);

	}

	fclose(input_bcode);

	// DECLARE STACK AND EXECUTE FILE

	stack = (unsigned char*)malloc(stack_size);

	execute(bcode_size, &error_flag);

	// FINISH

	clean(header_info.consts_count);

	_getch();
	return (!error_flag) ? EXIT_SUCCESS : ERROR;

}