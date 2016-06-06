#include "client_activity.h"

struct tm today;

activitylst_t* clientactbst_get_client_activity(clientactbst_node_t* root, char* key) {
	clientactbst_node_t* node = clientactbst_search_node(root, key);
	if (node) return node->activities;
	return NULL;
}

clientactbst_node_t* clientactbst_search_node(clientactbst_node_t* root, char* key) {
	if (!root || !root->key || !strcmp(root->key, key)){
		return root;
	}else if (strcmp(key, root->key) < 0) { //Less than this node
		return clientactbst_search_node(root->left, key);
	} else if (strcmp(key, root->key) > 0) { //More than this node
		return clientactbst_search_node(root->right, key);
	}
}

void clientactbst_insert(clientactbst_node_t* root, char* key, activity_t* activity) {
	clientactbst_node_t* new_node;
	if (!root) return;
	/*if(!root->root){
	 strcpy(root->key, key);
	 activitylst_add(root->activities, activity);
	 return new_node;
	 }*/
	//XXX rework this code
	if (root->key) {
		if (strcmp(key, root->key) < 0) { //Less than this node

			if (root->left) {
				clientactbst_insert(root->left, key, activity);
			} else {
				new_node = clientactbst_node_initialize(key);
				root->left = new_node;
				new_node->root = root;
				activitylst_add(new_node->activities, activity);
			}
		} else if (strcmp(key, root->key) > 0) { //More than this node
			if (root->right) {
				return clientactbst_insert(root->right, key, activity);
			} else {
				new_node = clientactbst_node_initialize(key);
				root->right = new_node;
				new_node->root = root;
				activitylst_add(new_node->activities, activity);
			}
		} else {
			activitylst_add(root->activities, activity);
		}
	} else {
		root->key = malloc(sizeof(char) * strlen(key) + 1);
		strcpy(root->key, key);
		root->activities = activitylst_create();
		activitylst_add(root->activities, activity);
	}
}

clientactbst_node_t* clientactbst_node_initialize(char* key) {
	clientactbst_node_t* node;
	if (!(node = malloc(sizeof(clientactbst_node_t)))) return NULL;

	if (!(node->activities = malloc(sizeof(activitylst_t)))) {
		free(node);
		return NULL;
	}
	node->activities = activitylst_create();

	node->key = malloc(sizeof(char) * strlen(key) + 1);
	strcpy(node->key, key);
	node->left = NULL;
	node->right = NULL;
	return node;
}

void clientactbst_delete(clientactbst_node_t* root, char* key) {
	if (!root) return;
	clientactbst_node_t* node = clientactbst_search_node(root, key);
	clientactbst_node_delete(&node);
}

void clientactbst_node_delete(clientactbst_node_t** node_ptr) {
	clientactbst_node_t* node = *node_ptr;
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
		clientactbst_node_t* next_inorder_node = clientactbst_minimum(node->right);
		clientactbst_node_t* next_inorder_node_root = next_inorder_node->root;
		free(node->activities); //Free the old element
		node->key = next_inorder_node->key; //Assign the previous element
		node->activities = next_inorder_node->activities;
		next_inorder_node_root->left = NULL; //Clean references
		free(next_inorder_node); //Free the node memory
	}
}

unsigned clientactbst_size(clientactbst_node_t* node) {
	if (!node)
		return 0;
	else
		return clientactbst_size(node->left) + clientactbst_size(node->right) + 1;
}

unsigned clientactbst_height(clientactbst_node_t* node) {
	unsigned left, right;
	if (!node)
		return 0;
	else {
		left = clientactbst_height(node->left);
		right = clientactbst_height(node->right);
		if (left > right)
			return ++left;
		else
			return ++right;
	}
}

void clientactbst_inorder(clientactbst_node_t* node) {
	if (node != NULL) {
		clientactbst_inorder(node->left);
		//do_something(node->value);
		clientactbst_inorder(node->right);
	}
}

clientactbst_node_t* clientactbst_minimum(clientactbst_node_t* node) {
	if (!node)
		return NULL;
	else if (!node->left)
		return node;
	else
		return clientactbst_minimum(node->left);
}

clientactbst_node_t* clientactbst_maximum(clientactbst_node_t* node) {
	if (!node)
		return NULL;
	else if (!node->right)
		return node;
	else
		return clientactbst_maximum(node->right);
}

void clientactbst_add_store_visit(clientactbst_node_t* root, char* key, int value) {
	clientactbst_node_t* client_node = clientactbst_search_node(root, key);
	if (value < 0 && client_node) {
		client_node->activities->size--;
		return;
	}
	activity_t* activity = malloc(sizeof(activity));
	activity->spent = value;
	activity->date = malloc(sizeof(struct tm));
	*activity->date = today;

	clientactbst_insert(root, key, activity);
}
