#include "client_list.h"

lista_elems_t* clientlst_create() {
	lista_elems_t* list;
	list = malloc(sizeof(lista_elems_t));
	list->elements = calloc(100, sizeof(elem));
	list->size = 0;
	list->max_size = 100;
	return list;
}

int clientlst_destroy(lista_elems_t* list) {
	if (!list) {
		return NO_LIST;
	}
	free(list->elements);
	free(list);
	return OK;
}

int clientlst_add(lista_elems_t* list, elem e) {
	if (!list) NO_LIST;
	if (list->size == list->max_size) {
		list->max_size *= 2;
		if (!(list->elements = realloc(list->elements, list->max_size * sizeof(elem)))) return NO_MEM;
	}

	list->elements[list->size++] = e;
	return OK;
}

int clientlst_get(lista_elems_t* list, unsigned int rank, elem* e) {
	if (!list) return NO_LIST;
	if (!e) return 4;
	if (rank < 0 || rank >= list->size) return OUT_OF_RANK;
	*e = list->elements[rank];
	return OK;
}

int clientlst_set(lista_elems_t* list, unsigned int rank, elem in, elem* out) {
	if (!list) return NO_LIST;
	if (!out ) return NULL_PTR;
	if (rank < 0 || rank >= list->size) return OUT_OF_RANK;
	*out = list->elements[rank];
	list->elements[rank] = in;
	return OK;
}

int clientlst_size(lista_elems_t* list, unsigned int* size) {
	if (!list) return NO_LIST;
	*size = list->size;
	return OK;
}

int clientlst_is_empty(lista_elems_t* list) {
	if (!list) return NO_LIST;
	if (list->size == 0) return EMPTY_LIST;
	return OK;
}

int clientlst_elem_exists(lista_elems_t* list, char* name) {
	if (!list) return NO_LIST;
	int i;
	for (i = 0; i < list->size; i++) { //verify if there isn't a element with the same value.
		if (!strcmp(name,list->elements[i].name)) {
			return CLIENT_EXISTS; //each member of the list has to be unique.
		}
	}
	return OK;
}

void clientlst_update_active(lista_elems_t* list,int day,int month,int year){
    if (!list) return NO_LIST;
    int i;
    client_t aux;
    for(i=0;i<list->size;i++){
        clientlst_get(list,i,&aux);
        client_update_active(&aux,day,month,year);
    }
}

void client_visit_store(lista_elems_t* list,char* name,int value,char gender,int day,int month, int year){
    if(clientlst_elem_exists(list,name)==CLIENT_EXISTS){
        //add event
        //verify if still active
    } else{
        clientlst_add(list,client_create(name,gender,value,day,month,year));
    }
}

void clientlst_draw(lista_elems_t* list){
    if(!list) return NO_LIST;
    int i;
    client_t aux;
    for(i=0;i<list->size;i++){
        clientlst_get(list,i,&aux);
        client_print(aux);
    }
}

