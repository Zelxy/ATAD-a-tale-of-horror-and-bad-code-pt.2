#include "activity_list.h"

activity_list_t* activity_list_create() {
	activity_list_t* list;
	list = malloc(sizeof(activity_list_t));
	list->elements = calloc(100, sizeof(activity_t));
	list->size = 0;
	list->max_size = 100;
	return list;
}

int activitylst_destroy(activity_list_t* list) {
	if (!list) {
		return NO_LIST;
	}
	free(list->elements);
	free(list);
	return OK;
}

int activitylst_add(activity_list_t* list, activity_t e) {
	if (!list) return NULL_PTR;
	if (list->size == list->max_size) {
		list->max_size *= 2;
		if (!(list->elements = realloc(list->elements, list->max_size * sizeof(activity_t)))) return NO_MEM;
	}
	list->elements[list->size++] = e;
	return OK;
}

int activitylst_get(activity_list_t* list, unsigned rank, activity_t* e) {
	if (list == NULL) return NO_LIST;
	if (e == NULL) return NULL_PTR;
	if (rank < 0 || rank >= list->size) return OUT_OF_RANK;
	*e = list->elements[rank];
	return OK;
}

int activitylst_set(activity_list_t* list, unsigned rank, activity_t in, activity_t* out) {
	if (!list) return NO_LIST;
	if (!out) return NULL_PTR;
	if (rank < 0 || rank >= list->size) return OUT_OF_RANK;
	*out = list->elements[rank];
	list->elements[rank] = in;
	return OK;
}

int activitylst_size(activity_list_t* lista, unsigned* size) {
	if (lista == NULL) return NO_LIST;
	if (size == NULL) return NULL_PTR;
	*size = lista->size;
	return OK;
}

int activitylst_is_empty(activity_list_t* list) {
	if (list == NULL) return NO_LIST;
	if (list->size == 0) return EMPTY_LIST;
	return OK;
}
