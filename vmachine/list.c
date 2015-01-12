#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "str.h"

void append(list **head, char *cmd, char *arg1, char *arg2) {

	list *temp;
	
	if(!*head) {

		(*head) = (list*)malloc(sizeof(list));

		(*head)->cmd = (char*)malloc(strlen(cmd) + 1);
		strcpy_s((*head)->cmd, strlen(cmd) + 1, cmd);
		tolower_case((*head)->cmd);

		if(arg1) {

			(*head)->arg1 = (char*)malloc(strlen(arg1) + 1);
			strcpy_s((*head)->arg1, strlen(arg1) + 1, arg1);
			tolower_case((*head)->arg1);

		} else {

			(*head)->arg1 = NULL;

		}

		if(arg2) {

			(*head)->arg2 = (char*)malloc(strlen(arg2) + 1);
			strcpy_s((*head)->arg2, strlen(arg2) + 1, arg2);
			tolower_case((*head)->arg2);
			 
		} else {

			(*head)->arg2 = NULL;

		}

		(*head)->next = NULL;

	} else {

		temp = get_last(head);

		temp->next = (list*)malloc(sizeof(list));

		temp->next->cmd = (char*)malloc(strlen(cmd) + 1);
		strcpy_s(temp->next->cmd, strlen(cmd) + 1, cmd);
		tolower_case(temp->next->cmd);

		if(arg1) {

			temp->next->arg1 = (char*)malloc(strlen(arg1) + 1);
			strcpy_s(temp->next->arg1, strlen(arg1) + 1, arg1);
			tolower_case(temp->next->arg1);

		} else {

			temp->next->arg1 = NULL;

		}

		if(arg2) {
		
			temp->next->arg2 = (char*)malloc(strlen(arg2) + 1);
			strcpy_s(temp->next->arg2, strlen(arg2) + 1, arg2);
			tolower_case(temp->next->arg2);

		} else {

			temp->next->arg2 = NULL;

		}

		temp->next->next = NULL;
	}
}

list* get_last(list **head) {

	list *last;
	last = (*head);

	if(!*head)
		return NULL;

	while(last->next) {

		last = last->next;

	}

	return last;

}

void del_list(list **head) {

	list *first;

	while((*head)) {

		first = (*head);
		(*head) = first->next;

		if(first->cmd)
			free(first->cmd);

		if(first->arg1)
			free(first->arg1);

		if(first->arg2)
			free(first->arg2);

		free(first);

	}

}