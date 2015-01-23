#ifndef H_LABEL
#define H_LABEL

#include <stdio.h>

typedef struct {

	char *name;
	short addr;
	char translated;

} label_type;

struct label_element {

	label_type label;
	struct label_element *next;

};

typedef struct label_element label_list;

size_t is_label(char *label);

size_t add_new_label(char *label_name, short address, label_list **head);

short find_label(char *label_name, label_list **head);

short get_label_addr(char *label_name, label_list **head);

void clean_label_list(label_list **head);

#endif