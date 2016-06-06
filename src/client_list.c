#include "client_list.h"

extern struct tm today;

clientlst_t* clientlst_create() {
	clientlst_t* list;
	list = malloc(sizeof(clientlst_t));
	list->elements = calloc(100, sizeof(client_t));
	list->size = 0;
	list->max_size = 100;
	return list;
}

int clientlst_destroy(clientlst_t* list) {
	if (!list) {
		return NO_LIST;
	}
	free(list->elements);
	free(list);
	return OK;
}

int clientlst_add(clientlst_t* list, client_t e) {
	if (!list) return NO_LIST;
	if (list->size == list->max_size) {
		list->max_size *= 2;
		if (!(list->elements = realloc(list->elements, list->max_size * sizeof(client_t)))) return NO_MEM;
	}

	list->elements[list->size] = e;
	list->size++;
	return OK;
}

client_t* clientlst_get(clientlst_t* list, unsigned rank) {
	if (!list || rank < 0 || rank >= list->size) return NULL;
	return list->elements+rank;
}

int clientlst_set(clientlst_t* list, unsigned int rank, client_t in, client_t* out) {
	if (!list) return NO_LIST;
	if (!out) return NULL_PTR;
	if (rank < 0 || rank >= list->size) return OUT_OF_RANK;
	*out = list->elements[rank];
	list->elements[rank] = in;
	return OK;
}

int clientlst_size(clientlst_t* list, unsigned int* size) {
	if (!list) return NO_LIST;
	*size = list->size;
	return OK;
}

int clientlst_is_empty(clientlst_t* list) {
	if (!list) return NO_LIST;
	if (list->size == 0) return EMPTY_LIST;
	return OK;
}

int clientlst_rank_lookup(clientlst_t* list, char* name) {
	for (int i = 0; i < list->size; i++) { //verify if there isn't a element with the same value.
		if (!strcmp(name, list->elements[i].name)) {
			return i;
		}
	}
	return -1;
}

int clientlst_elem_exists(clientlst_t* list, char* name) {
	if (!list) return NO_LIST;
	return (clientlst_rank_lookup(list, name) > -1) ? 1 : 0;
}

int clientlst_update_active(clientlst_t* list) {
	if (!list) return NO_LIST;
	int i;
	client_t* aux;
	for (i = 0; i < list->size; i++) {
		aux = clientlst_get(list, i);
		client_update_active(aux);
	}
	return OK;
}

int clientlst_add_store_visit(clientlst_t* list, char* name, int value, char gender,char* last_name) {
	if (!list) return NO_LIST;
	int rank = clientlst_rank_lookup(list, name);
	if (rank == -1) {
		clientlst_add(list, client_create(name, gender, value));
		//TODO Add to activity tree;
	} else {
		client_t* client = clientlst_get(list, rank);
		if (!client)
			fprintf(stderr, "Inconsistência encontrada na lista de clientes!");
		*client->last_visit = today;
		client->spent += value;
		if(strcmp(last_name,name)){
            client->visits += 1;
            printf("%s visitou a loja! %d\n",client->name,client->visits);
		}

		//TODO Add to activity tree;
	}
	strcpy(last_name,name);
	return OK;
}

int clientlst_draw(clientlst_t* list) {
	if (!list) return NO_LIST;
	client_t *aux;
	for (int i = 0; i < list->size; i++) {
		aux = clientlst_get(list, i);
		client_print(aux);
	}
	return OK;
}

