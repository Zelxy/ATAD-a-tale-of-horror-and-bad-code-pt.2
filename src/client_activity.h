/*
 * bst.h
 *
 *  Created on: May 28, 2016
 *      Author: claudio
 */

#ifndef CLIENT_BST_H_
#define CLIENT_BST_H_

#include <stdlib.h>
#include <string.h>
#include "client_activity.h"

typedef int activity_list_t;

typedef struct bst_node client_bst_node_t;
struct bst_node{
	client_bst_node_t* root;
	client_bst_node_t* left;
	client_bst_node_t* right;
	char*	key;
	activity_list_t*	activities;
};
activity_list_t client_bst_get_client_activity(client_bst_node_t*, char*);
client_bst_node_t* client_bst_search_node(client_bst_node_t*, char*);//Searches tree for the node with the key
client_bst_node_t* client_bst_node_create(char*, activity_list_t);//initializes a node
void client_bst_delete(client_bst_node_t*, char*);//Deletes the node with the key
void client_bst_node_delete(client_bst_node_t**);//Deletes a node from the tree
//TODO
//void bst_destroy(bst_node_t*);//Destroys a tree starting from a node

void client_bst_insert(client_bst_node_t*, char*, activity_list_t);//Inserts a node into the tree
void client_bst_delete_node(client_bst_node_t*, char*);//Deletes a node from the tree

unsigned client_bst_size(client_bst_node_t*);//Calculates number of nodes
unsigned client_bst_height(client_bst_node_t*);//Calculates tree maximum height

void client_bst_inorder(client_bst_node_t*);//Does "something" with each node in-order

client_bst_node_t* client_bst_minimum(client_bst_node_t*);//Seeks node with smaller key
client_bst_node_t* client_bst_maximum(client_bst_node_t*);//Seeks node with bigger key

#endif
