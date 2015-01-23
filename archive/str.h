#ifndef H_STR
#define H_STR
#include "types.h"
#include "list.h"

void tolower_case(char *str);

void parse(char *str, size_t length, list **head);

unsigned char analysis(list **head, unsigned char **bcode_array);

#endif
