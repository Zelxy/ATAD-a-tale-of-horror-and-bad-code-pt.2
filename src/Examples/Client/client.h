#ifndef CLIENT_H
#define CLIENT_H
#include "time.h"
static int last_id = 0;


typedef struct{
    int id;
    char* name;
    char gender;
    int spent;
    struct tm *last_visit;
    int is_active;
}client_t;

client_t* client_create(char*,char,int,int,int,int);

void client_print(client_t*);


#endif // CLIENT_H
