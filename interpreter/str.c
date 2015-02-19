#include "main_variables.h"
#include "types.h"
#include "str.h"

#include <malloc.h>

size_t header_size(header *header_of_file) {

	return (sizeof(header_of_file->signature) + sizeof(header_of_file->version) + sizeof(header_of_file->consts_count) + sizeof(header_of_file->consts_size) + header_of_file->consts_count + header_of_file->consts_size + sizeof(main_id) + sizeof(count_of_funcs));

}

void read_header(header *header_of_file) {

	char clength;
	size_t ilength;

	size_t i;

	fread(header_of_file, sizeof(header), 1, input_bcode);

	const_str = (char**)malloc(header_of_file->consts_count);

	for(i = 0; i < header_of_file->consts_count; i++) {

		fread(&clength, 1, 1, input_bcode);
		ilength = clength;

		const_str[i] = (char*)malloc(ilength);
		fread(const_str[i], ilength, 1, input_bcode);

	}

	fread(&main_id, sizeof(main_id), 1, input_bcode);

}

size_t check_header(header *header_of_file) {

	if(header_of_file->signature != -17734)
		return ERROR;

	if(header_of_file->version <= 0)
		return ERROR;

	if(header_of_file->consts_count < 0)
		return ERROR;

	if(header_of_file->consts_size < 0)
		return ERROR;

	return 0;

}