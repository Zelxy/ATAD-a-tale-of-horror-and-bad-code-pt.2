#include "bst.h"

elem_t bst_get_element(bst_node_t* root, key_t key) {
	bst_node_t* node = bst_search_node(root, key);
	if(node)
		return *node->value;
	return (elem_t)0;
}

bst_node_t* bst_search_node(bst_node_t* root, key_t key) {
	if (!root || root->key == key)
		return root;
	else if (key < root->key)
		return bst_search_node(root->left, key);
	else // key > node.key
		return bst_search_node(root->right, key);
}

void bst_insert(bst_node_t* root, key_t key, elem_t value) {
	if (!root) { //Node does not exist
		if (!(root = bst_node_create(key, value))) //Make one
			return; //End if failed
	} else if (key < root->key) //Less than this node
		bst_insert(root->left, key, value);
	else if (key > root->key){ //More than this node
		bst_insert(root->right, key, value);
	}else
		return;
}

bst_node_t* bst_node_create(key_t key, elem_t value) {
	bst_node_t* node;
	if (!(node = malloc(sizeof(bst_node_t))))
		return NULL;

	if (!(node->value = malloc(sizeof(elem_t)))) {
		free(node);
		return NULL;
	}
	node->key = key;
	*node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void bst_delete(bst_node_t* root, key_t key){
	if (!root)
		return;
	bst_node_t* node = bst_search_node(root, key);
	bst_node_delete(&node);
}

void bst_node_delete(bst_node_t** node_ptr) {
	bst_node_t* node = *node_ptr;
	if (!node->left && !node->right) { //It it is a leaf
		free(node->value);
		free(node);
	} else if (node->right) { //If it has a right branch
		*node_ptr = node->right; //Assign pointer to the branch
		free(node->value);
		free(node);
	} else if (node->left) { //Same for the right side
		*node_ptr = node->left;
		free(node->value);
		free(node);
	} else { //But if both sides have branches
		bst_node_t* next_inorder_node = bst_minimum(node->right);
		bst_node_t* next_inorder_node_root = next_inorder_node->root;
		free(node->value); //Free the old element
		node->key = next_inorder_node->key; //Assign the previous element
		node->value = next_inorder_node->value;
		next_inorder_node_root->left = NULL; //Clean references
		free(next_inorder_node); //Free the node memory
	}
}

unsigned bst_size(bst_node_t* node) {
	if (!node)
		return 0;
	else
		return bst_size(node->left) + bst_size(node->right) + 1;
}

unsigned bst_height(bst_node_t* node) {
	unsigned left, right;
	if (!node)
		return 0;
	else {
		left = bst_height(node->left);
		right = bst_height(node->right);
		if (left > right)
			return ++left;
		else
			return ++right;
	}
}

void bst_inorder(bst_node_t* node) {
	if (node != NULL) {
		bst_inorder(node->left);
		//do_something(node->value);
		bst_inorder(node->right);
	}
}

bst_node_t* bst_minimum(bst_node_t* node) {
	if (!node)
		return NULL;
	else if (!node->left)
		return node;
	else
		return bst_minimum(node->left);
}

bst_node_t* bst_maximum(bst_node_t* node) {
	if (!node)
		return NULL;
	else if (!node->right)
		return node;
	else
		return bst_maximum(node->right);
}
