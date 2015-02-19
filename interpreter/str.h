#ifndef H_STR
#define H_STR

size_t header_size(header *header_of_file);

void read_header(header *header_of_file);

size_t check_header(header *header_of_file);

#endif