//List of client activity.

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
	activity_t** elements;
	int size;
	int max_size;
}activitylst_t;

activitylst_t* activitylst_create();

int activitylst_destroy(activitylst_t*);

int activitylst_add(activitylst_t*, activity_t*);

int activitylst_set(activitylst_t*, unsigned, activity_t*, activity_t*);

int activitylst_get(activitylst_t*, unsigned, activity_t*);

int activitylst_size(activitylst_t*, unsigned*);

int activitylst_is_empty(activitylst_t*);

int activitylst_elem_exists(activitylst_t*, activity_t);

#endif
