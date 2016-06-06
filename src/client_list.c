#include "client_list.h"

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

int clientlst_get(clientlst_t* list, unsigned int rank, client_t* e) {
	if (!list) return NO_LIST;
	if (!e) return 4;
	if (rank < 0 || rank >= list->size) return OUT_OF_RANK;
	*e = list->elements[rank];
	return OK;
}

int clientlst_set(clientlst_t* list, unsigned int rank, client_t in, client_t* out) {
	if (!list) return NO_LIST;
	if (!out ) return NULL_PTR;
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

int clientlst_elem_exists(clientlst_t* list, char* name) {
	if (!list) return NO_LIST;
	int i;
	for (i = 0; i < list->size; i++) { //verify if there isn't a element with the same value.
		if (!strcmp(name,list->elements[i].name)) {
			return CLIENT_EXISTS; //each member of the list has to be unique.
		}
	}
	return OK;
}

int clientlst_update_active(clientlst_t* list,int day,int month,int year){
    if (!list) return NO_LIST;
    int i;
    client_t aux;
    for(i=0;i<list->size;i++){
        clientlst_get(list,i,&aux);
        client_update_active(&aux,day,month,year);
    }
    return OK;
}

int client_visit_store(clientlst_t* list,char* name,int value,char gender){
    if(!list) return NO_LIST;
    if(clientlst_elem_exists(list,name)==CLIENT_EXISTS){
       //TODO process visits
    } else{
        clientlst_add(list,client_create(name,gender,value));
        //TODO register visit
    }
    return OK;
}

int clientlst_draw(clientlst_t* list){
    if(!list) return NO_LIST;
    client_t aux;
    for(int i=0; i<list->size; i++){
        clientlst_get(list,i,&aux);
        client_print(aux);
    }
    return OK;
}

