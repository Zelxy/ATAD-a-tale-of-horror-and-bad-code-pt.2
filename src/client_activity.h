// Client activity binary search tree

#ifndef CLIENT_BST_H_
#define CLIENT_BST_H_

#include <stdlib.h>
#include <string.h>
#include "activity_list.h"

typedef struct bst_node clientactbst_node_t;
struct bst_node{
	clientactbst_node_t* root;
	clientactbst_node_t* left;
	clientactbst_node_t* right;
	char*	key;
	activitylst_t*	activities;
};
activitylst_t* clientactbst_get_client_activity(clientactbst_node_t*, char*);

clientactbst_node_t* clientactbst_search_node(clientactbst_node_t*, char*);//Searches tree for the node with the key
clientactbst_node_t* clientactbst_node_initialize(char*);//initializes a node
void clientactbst_delete(clientactbst_node_t*, char*);//Deletes the node with the key
void clientactbst_node_delete(clientactbst_node_t**);//Deletes a node from the tree
//TODO
//void bst_destroy(bst_node_t*);//Destroys a tree starting from a node

void clientactbst_insert(clientactbst_node_t*, char*, activity_t*);//Inserts a node into the tree
void clientactbst_delete_node(clientactbst_node_t*, char*);//Deletes a node from the tree

unsigned clientactbst_size(clientactbst_node_t*);//Calculates number of nodes
unsigned clientactbst_height(clientactbst_node_t*);//Calculates tree maximum height

void clientactbst_inorder(clientactbst_node_t*);//Does "something" with each node in-order

clientactbst_node_t* clientactbst_minimum(clientactbst_node_t*);//Seeks node with smaller key
clientactbst_node_t* clientactbst_maximum(clientactbst_node_t*);//Seeks node with bigger key

void clientactbst_add_store_visit(clientactbst_node_t*, char*, int);

#endif
