#ifndef CLIENT_LIST_H
#define CLIENT_LIST_H
#include <stdlib.h>
#include "client.h"
//Error definition
#define OK 0
#define NO_MEM 1
#define OUT_OF_RANK 2
#define NO_LIST 3
#define EMPTY_LIST 5
#define CLIENT_EXISTS 6

typedef client_t elem;

typedef struct {
	elem* elements;
	int size;
	int max_size;
}lista_elems_t;

lista_elems_t* list_create();

int list_destroy(lista_elems_t*);

int list_add(lista_elems_t*, elem);

int list_set(lista_elems_t*, unsigned, elem, elem*);

int list_get(lista_elems_t*, unsigned, elem*);

int list_size(lista_elems_t*, unsigned*);

int list_is_empty(lista_elems_t*);

int list_elem_exists(lista_elems_t*, char*);

void list_update_active(lista_elems_t*,int,int,int);

void client_visit_store(lista_elems_t*,char*,int,char,int,int,int);

#endif

