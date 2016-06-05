#ifndef CLIENT_H
#define CLIENT_H
#include "time.h"
#include <stdlib.h>
#include <stdio.h>
static int last_id = 1;


typedef struct{
    int id;
    char* name;
    char gender;
    int spent;
    struct tm *last_visit;
    int is_active;
}client_t;

client_t client_create(char*,char,int,int,int,int);

void client_print(client_t);

void client_update_active(client_t*,int,int,int);



#endif // CLIENT_H

