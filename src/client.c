#include "client.h"

client_t client_create(char* name, char gender, int spent, int day, int month, int year){
    client_t client;

    client.id = last_id++;//TODO
    client.gender = gender;
    client.name = name;
    client.spent = spent;
    client.is_active = 1;
    client.last_visit = malloc(sizeof(struct tm));
    client.last_visit->tm_mday = day;
    client.last_visit->tm_mon = month - 1;
    client.last_visit->tm_year = year - 1900;
    client.last_visit->tm_hour = 0;
    client.last_visit->tm_min = 0;
    client.last_visit->tm_sec = 0;
    return client;
}

void client_print(client_t* client){
     char* teste = calloc(200,sizeof(char));
     strftime(teste,sizeof(char)*200,"%d/%m/%Y",client->last_visit);
     printf("%s\n",client->name);
     printf("%s\n",teste);
     //double dif = difftime(y,x)/(60*60*24);
}

void client_update_active(client_t* client,int day,int month,int year){
    struct tm new_day;
    new_day.tm_mday = day;
    new_day.tm_mon = month - 1;
    new_day.tm_year = year - 1900;
    new_day.tm_hour = 0;
    new_day.tm_min = 0;
    new_day.tm_sec = 0;
    time_t client_time = mktime(client->last_visit);
    time_t new_time = mktime(&new_day);
    double dif = difftime(new_time,client_time)/(60*60*24);
    if(dif < 30){
        client->last_visit->tm_mday = day;
        client->last_visit->tm_mon = month - 1;;
        client->last_visit->tm_year = year - 1900;
    } else{
        client->is_active = 0;
        client->spent = 0;
    }
}



