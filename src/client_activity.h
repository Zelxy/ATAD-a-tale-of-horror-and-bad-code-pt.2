// Client activity binary search tree

#ifndef CLIENT_BST_H_
#define CLIENT_BST_H_

#include <stdlib.h>
#include <string.h>
#include "activity_list.h"

typedef struct bst_node client_bst_node_t;
struct bst_node{
	client_bst_node_t* root;
	client_bst_node_t* left;
	client_bst_node_t* right;
	char*	key;
	activity_list_t*	activities;
};
activity_list_t* clientactbst_get_client_activity(client_bst_node_t*, char*);
client_bst_node_t* clientactbst_search_node(client_bst_node_t*, char*);//Searches tree for the node with the key
client_bst_node_t* clientactbst_node_create(char*, activity_list_t);//initializes a node
void clientactbst_delete(client_bst_node_t*, char*);//Deletes the node with the key
void clientactbst_node_delete(client_bst_node_t**);//Deletes a node from the tree
//TODO
//void bst_destroy(bst_node_t*);//Destroys a tree starting from a node

void clientactbst_insert(client_bst_node_t*, char*, activity_list_t);//Inserts a node into the tree
void clientactbst_delete_node(client_bst_node_t*, char*);//Deletes a node from the tree

unsigned clientactbst_size(client_bst_node_t*);//Calculates number of nodes
unsigned clientactbst_height(client_bst_node_t*);//Calculates tree maximum height

void clientactbst_inorder(client_bst_node_t*);//Does "something" with each node in-order

client_bst_node_t* clientactbst_minimum(client_bst_node_t*);//Seeks node with smaller key
client_bst_node_t* clientactbst_maximum(client_bst_node_t*);//Seeks node with bigger key

#endif
