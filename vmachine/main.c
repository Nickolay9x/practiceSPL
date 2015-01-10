#include <malloc.h>
#include "header.h"

int main(int argc, char **argv) {

	BYTE* bcode_array;

	bcode_array = (BYTE*)calloc(BCODE_SIZE, sizeof(BYTE));

	return 0;

}

