#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

//Definiçao de erros
#define OK 0
#define NO_MEM 1
#define OUT_OF_RANK 2
#define NO_LIST 3
#define NULL_PTR 4
#define EMPTY_LIST 5
#define CLIENTE_EXISTE 6

typedef int elem;

struct listaE{
    elem* elementos;
    int nElems;
    int maxSize;
};
typedef struct listaE lista_elems_t;

lista_elems_t* createList();

int destroyList(lista_elems_t**);

int addList(lista_elems_t*,elem);

int setList(lista_elems_t*,unsigned int,elem,elem*);

int getList(lista_elems_t*,unsigned int,elem*);

int sizeList(lista_elems_t*,unsigned int*);

int isEmptyList(lista_elems_t*);

int elemExistList(lista_elems_t*,elem);
#endif // LISTAelemS_H
