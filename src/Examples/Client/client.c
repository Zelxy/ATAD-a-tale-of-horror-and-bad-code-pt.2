#include "client.h"

client_t* client_create(char* name, char gender, int spent, int day, int month, int year){
    client_t *client_tmp = malloc(sizeof(struct client));

    client_tmp->id = last_id++;
    client_tmp->gender = gender;
    client_tmp->name = name;
    client_tmp->spent = spent;
    client_tmp->is_active = 0;
    client_tmp->last_visit = malloc(sizeof(struct tm));
    client_tmp->last_visit->tm_mday = day;
    client_tmp->last_visit->tm_mon = month - 1;
    client_tmp->last_visit->tm_mon = year - 1900;

    return client_tmp;
}

void client_print(client_t* client){
     char* teste = calloc(200,sizeof(char));
     strftime(teste,sizeof(char)*200,"%d/%m/%Y",client->last_visit);
     printf("%s",client->name);
     printf("%s\n",teste);
}
