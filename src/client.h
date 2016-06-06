#ifndef CLIENT_H
#define CLIENT_H
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct{
    int id;
    char* name;
    char gender;
    int spent;
    struct tm *last_visit;
    int is_active;
}client_t;

client_t client_create(char*,char,int);

void client_print(client_t*);

void client_update_active(client_t*,int,int,int);

#endif // CLIENT_H

