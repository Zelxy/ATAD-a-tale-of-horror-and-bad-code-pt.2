#ifndef CLIENT_LIST_H
#define CLIENT_LIST_H

#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "client_activity.h"

//Error definition
#define OK 0
#define NO_MEM 1
#define OUT_OF_RANK 2
#define NO_LIST 3
#define NULL_PTR 4
#define EMPTY_LIST 5
#define CLIENT_EXISTS 6


typedef struct {
	client_t* elements;
	int size;
	int max_size;
}clientlst_t;

clientlst_t* clientlst_create();

int clientlst_destroy(clientlst_t*);

int clientlst_add(clientlst_t*, client_t);

int clientlst_set(clientlst_t*, unsigned, client_t, client_t*);

client_t* clientlst_get(clientlst_t*, unsigned);

int clientlst_size(clientlst_t*, unsigned*);

int clientlst_is_empty(clientlst_t*);

int clientlst_rank_lookup(clientlst_t*, char*);

int clientlst_elem_exists(clientlst_t*, char*);

int clientlst_update_active(clientlst_t*,int,int,int);

int clientlst_add_store_visit(clientlst_t*, clientactbst_node_t*, char*,int,char);

int clientlst_draw(clientlst_t*);

#endif

