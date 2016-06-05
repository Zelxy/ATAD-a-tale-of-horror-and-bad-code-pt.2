#include "client_activity.h"

activity_list_t client_bst_get_client_activity(client_bst_node_t* root, char* key) {
	client_bst_node_t* node = client_bst_search_node(root, key);
	if (node) return *node->activities;
	return (activity_list_t) 0;
}

client_bst_node_t* client_bst_search_node(client_bst_node_t* root, char* key) {
	if (!root || root->key == key)
		return root;
	else if (key < root->key)
		return client_bst_search_node(root->left, key);
	else
		// key > node.key
		return client_bst_search_node(root->right, key);
}

void client_bst_insert(client_bst_node_t* root, char* key, activity_list_t value) {
	if (!root) { //Node does not exist
		if (!(root = client_bst_node_create(key, value))) //Make one
			return;//End if failed
	} else if(strcmp(key, root->key) < 0) //Less than this node
		client_bst_insert(root->left, key, value);
	else if (strcmp(key, root->key) > 0) { //More than this node
		client_bst_insert(root->right, key, value);
	} else
		return;
	//FIXME I don't think this will work as expected.
}

client_bst_node_t* client_bst_node_create(char* key, activity_list_t value) {
	client_bst_node_t* node;
	if (!(node = malloc(sizeof(client_bst_node_t)))) return NULL;

	if (!(node->activities = malloc(sizeof(activity_list_t)))) {
		free(node);
		return NULL;
	}
	node->key = key;
	*node->activities = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void client_bst_delete(client_bst_node_t* root, char* key) {
	if (!root) return;
	client_bst_node_t* node = client_bst_search_node(root, key);
	client_bst_node_delete(&node);
}

void client_bst_node_delete(client_bst_node_t** node_ptr) {
	client_bst_node_t* node = *node_ptr;
	if (!node->left && !node->right) { //It it is a leaf
		free(node->activities);
		free(node);
	} else if (node->right) { //If it has a right branch
		*node_ptr = node->right; //Assign pointer to the branch
		free(node->activities);
		free(node);
	} else if (node->left) { //Same for the right side
		*node_ptr = node->left;
		free(node->activities);
		free(node);
	} else { //But if both sides have branches
		client_bst_node_t* next_inorder_node = client_bst_minimum(node->right);
		client_bst_node_t* next_inorder_node_root = next_inorder_node->root;
		free(node->activities); //Free the old element
		node->key = next_inorder_node->key; //Assign the previous element
		node->activities = next_inorder_node->activities;
		next_inorder_node_root->left = NULL; //Clean references
		free(next_inorder_node); //Free the node memory
	}
}

unsigned client_bst_size(client_bst_node_t* node) {
	if (!node)
		return 0;
	else
		return client_bst_size(node->left) + client_bst_size(node->right) + 1;
}

unsigned client_bst_height(client_bst_node_t* node) {
	unsigned left, right;
	if (!node)
		return 0;
	else {
		left = client_bst_height(node->left);
		right = client_bst_height(node->right);
		if (left > right)
			return ++left;
		else
			return ++right;
	}
}

void client_bst_inorder(client_bst_node_t* node) {
	if (node != NULL) {
		client_bst_inorder(node->left);
		//do_something(node->value);
		client_bst_inorder(node->right);
	}
}

client_bst_node_t* client_bst_minimum(client_bst_node_t* node) {
	if (!node)
		return NULL;
	else if (!node->left)
		return node;
	else
		return client_bst_minimum(node->left);
}

client_bst_node_t* client_bst_maximum(client_bst_node_t* node) {
	if (!node)
		return NULL;
	else if (!node->right)
		return node;
	else
		return client_bst_maximum(node->right);
}
