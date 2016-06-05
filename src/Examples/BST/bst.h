#ifndef BST_BST_H_
#define BST_BST_H_

#include <stdlib.h>

typedef int key_t;
typedef int elem_t;

typedef struct bst_node bst_node_t;
struct bst_node{
	bst_node_t* root;
	bst_node_t* left;
	bst_node_t* right;
	key_t	key;
	elem_t*	value;
};

elem_t bst_get_element(bst_node_t*, key_t);
bst_node_t* bst_search_node(bst_node_t*, key_t);//Searches tree for the node with the key
bst_node_t* bst_node_create(key_t, elem_t);//initializes a node
void bst_delete(bst_node_t*, key_t);//Deletes the node with the key
void bst_node_delete(bst_node_t**);//Deletes a node from the tree
//TODO
//void bst_destroy(bst_node_t*);//Destroys a tree starting from a node

void bst_insert(bst_node_t*, key_t, elem_t);//Inserts a node into the tree
void bst_delete_node(bst_node_t*, key_t);//Deletes a node from the tree

unsigned bst_size(bst_node_t*);//Calculates number of nodes
unsigned bst_height(bst_node_t*);//Calculates tree maximum height

void bst_inorder(bst_node_t*);//Does "something" with each node in-order

bst_node_t* bst_minimum(bst_node_t*);//Seeks node with smaller key
bst_node_t* bst_maximum(bst_node_t*);//Seeks node with bigger key

#endif /* BST_BST_H_ */
