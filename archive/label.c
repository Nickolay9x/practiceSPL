#include "label.h"

#include <malloc.h>
#include <string.h>

size_t is_label(char *label) {

	size_t i;

	for(i = 0; i < strlen(label) - 1; i++) {

		if((label[i] < 33) && (label[i] > 126)) {

			return 0;

		}

	}

	return (label[i] == 58) ? 1 : 0;

}

short find_label(char *label_name, label_list **head) {

	label_list *iterator = (*head);

	while(iterator) {

		if(!strcmp(iterator->label.name, label_name) && !iterator->label.translated)
			return iterator->label.addr;

		iterator = iterator->next;

	}

	return 0;

}

short get_label_addr(char *label_name, label_list **head) {

	label_list *iterator = (*head);

	while(iterator) {

		if(!strcmp(iterator->label.name, label_name))
			return iterator->label.addr;

		iterator = iterator->next;

	}

	return 0;

}

size_t add_new_label(char *label_name, short address, label_list **head) {

	label_list *iterator = (*head);

	if(!(*head)) {

		(*head) = (label_list*)malloc(sizeof(label_list));
		(*head)->label.name = (char*)malloc(strlen(label_name) + 1);

		strcpy_s((*head)->label.name, strlen(label_name) + 1, label_name);
		(*head)->label.addr = address;
		(*head)->label.translated = 0;
		(*head)->next = NULL;

		return 1;

	}

	while(iterator->next) {

		if(!strcmp(iterator->label.name, label_name))
			return 0;

		iterator = iterator->next;

	}

	if(!strcmp(iterator->label.name, label_name))
			return 0;

	iterator->next = (label_list*)malloc(sizeof(label_list));
	iterator->next->label.name = (char*)malloc(strlen(label_name) + 1);

	strcpy_s(iterator->next->label.name, strlen(label_name) + 1, label_name);
	iterator->next->label.addr = address;
	iterator->next->label.translated = 0;
	iterator->next->next = NULL;

	return 1;

}

void clean_label_list(label_list **head) {

	label_list *iterator;

	while((*head)) {

		iterator = (*head);
		(*head) = iterator->next;
		free(iterator);

	}

}
