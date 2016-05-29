#include "client.h"

client_t* client_create(char* name, char gender, int spent, int day, int month, int year){
    client_t *client = malloc(sizeof(client_t));

    client->id = last_id++;//TODO
    client->gender = gender;
    client->name = name;
    client->spent = spent;
    client->is_active = 0;
    client->last_visit = malloc(sizeof(struct tm));
    client->last_visit->tm_mday = day;
    client->last_visit->tm_mon = month - 1;
    client->last_visit->tm_mon = year - 1900;

    return client;
}

void client_print(client_t* client){
     char* teste = calloc(200,sizeof(char));
     strftime(teste,sizeof(char)*200,"%d/%m/%Y",client->last_visit);
     printf("%s",client->name);
     printf("%s\n",teste);
}
