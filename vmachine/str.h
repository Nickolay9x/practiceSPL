#include "types.h"
#ifndef H_STR
#define H_STR

void parse(char *str, size_t length, list **head);

void translate(list **head, BYTE **bcode_array);

#endif