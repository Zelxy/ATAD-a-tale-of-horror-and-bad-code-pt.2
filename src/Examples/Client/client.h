#ifndef CLIENT_H
#define CLIENT_H
#include "time.h"
static int last_id = 0;

typedef struct client client_t;

struct client{
    int id;
    char* name;
    char gender;
    int spent;
    struct tm *last_visit;
    int isActive; // 0 = active 1 = inactive
};

client_t* client_create(char*,char,int,int,int,int);

void client_print(client_t*);


#endif // CLIENT_H
