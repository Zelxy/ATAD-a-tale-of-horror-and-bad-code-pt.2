#include "list.h"

lista_elems_t* createList()
{
    lista_elems_t* tmp_lista;
    tmp_lista = malloc(sizeof(struct listaE));
    tmp_lista->elementos = calloc(100,sizeof(elem));
    tmp_lista->nElems = 0;
    tmp_lista->maxSize = 100;
    return tmp_lista;
}

int destroyList(lista_elems_t** lista)
{
    free((*lista)->elementos);
    free(*lista);
    *lista = NULL;
}

int addList(lista_elems_t* lista,elem e)
{
    if(lista == NULL) return NULL_PTR;
    if(lista->nElems == lista->maxSize){
        lista->maxSize *= 2;
        if((lista->elementos = realloc(lista->elementos,lista->maxSize*sizeof(elem))) == NULL)return NO_MEM;
    }
    if(elemExistList(lista,e) == CLIENTE_EXISTE) return CLIENTE_EXISTE;

    lista->elementos[lista->nElems++] = e;
    return OK;
}

int getList(lista_elems_t* lista,unsigned int rank,elem* e){
    if(lista == NULL) return NO_LIST;
    if(e == NULL) return NULL_PTR;
    if(rank<0 || rank>=lista->nElems) return OUT_OF_RANK;
    *e = lista->elementos[rank];
    return OK;
}

int setList(lista_elems_t* lista,unsigned int rank, elem in, elem* out){
    if(lista == NULL) return NO_LIST;
    if(out == NULL || in == NULL) return NULL_PTR;
    if(rank<0 || rank>=lista->nElems) return OUT_OF_RANK;
    *out = lista->elementos[rank];
    lista->elementos[rank] = in;
    return OK;
}

int sizeList(lista_elems_t* lista,unsigned int* size){
    if(lista == NULL) return NO_LIST;
    if(size == NULL) return NULL_PTR;
    *size =  lista->nElems;
    return OK;
}

int isEmptyList(lista_elems_t* lista){
    if(lista == NULL) return NO_LIST;
    if(lista->nElems == 0) return EMPTY_LIST;
    return OK;
}

int elemExistList(lista_elems_t* lista,elem e){
    if(lista == NULL) return NO_LIST;
    int i;
    for(i = 0;i<lista->nElems;i++){ //verify if there isn't a element with the same value.
        if(e == lista->elementos[i]){
            return CLIENTE_EXISTE; //each member of the list has to be unique.
        }
    }
    return OK;
}
