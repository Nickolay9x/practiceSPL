#ifndef H_LIST
#define H_LIST

struct element {

	char* cmd;
	char* arg1;
	char* arg2;

	struct element* next;

};

typedef struct element list;

void append(list **head, char *cmd, char *arg1, char *arg2);

list* get_last(list **head);

void del_list(list **head);

#endif