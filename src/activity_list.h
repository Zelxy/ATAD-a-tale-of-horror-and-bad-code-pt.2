#ifndef ACTIVITY_LIST_H
#define ACTIVITY_LIST_H
#include <stdlib.h>
#include "client.h"
#include <time.h>

//Error definition
#define OK 0
#define NO_MEM 1
#define OUT_OF_RANK 2
#define NO_LIST 3
#define NULL_PTR 4
#define EMPTY_LIST 5
#define CLIENT_EXISTS 6

typedef struct{
	int spent;
    struct tm *date;
}activity_t;

typedef struct {
	activity_t* elements;
	int size;
	int max_size;
}activity_list_t;

activity_list_t* activity_list_create();

int activity_list_destroy(activity_list_t*);

int activity_list_add(activity_list_t*, activity_t);

int activity_list_set(activity_list_t*, unsigned, activity_t, activity_t*);

int activity_list_get(activity_list_t*, unsigned, activity_t*);

int activity_list_size(activity_list_t*, unsigned*);

int activity_list_is_empty(activity_list_t*);

int activity_list_elem_exists(activity_list_t*, activity_t);

#endif
