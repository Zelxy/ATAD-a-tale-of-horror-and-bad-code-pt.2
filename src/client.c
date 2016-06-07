#include "client.h"

struct tm today;

client_t client_create(char* name, char gender, int spent) {
	static int last_id = 1;
	client_t client;
	client.id = last_id++;
	client.gender = gender;
	client.name = malloc(strlen(name)*sizeof(char)+1);
	strcpy(client.name, name);
	client.spent = spent;
	client.is_active = 1;
	client.last_visit = malloc(sizeof(struct tm));
	*client.last_visit = today;
	client.visits = 1;
	return client;
}

void client_print(client_t *client) {
	printf("%d - %10s", client->id, client->name);
	client->gender == 'm' ? printf(", masculino. "): printf(", feminino.");

	printf("%5dEuros, estado", client->spent);
	client->is_active ? printf(" ativo\n") : printf(" inativo\n");
}

void client_update_active(client_t* client) {//FIXME time
	time_t client_time = mktime(client->last_visit);
	time_t new_time = mktime(&today);
	double dif = difftime(new_time, client_time) / (60 * 60 * 24);
	if (dif >= 30) {
		client->is_active = 0;
		client->spent = 0;
		client->visits = 0;
		//TODO REMOVE CLIENT
	}
}

