#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ORDER 4

// Node for the B-tree
struct Node {
	int keys[ORDER - 1];
	struct Node* children[ORDER];
	int keyCount;
	bool isLeaf;
};

// declaring the root node here
struct Node* root = NULL;

struct Node* initNode() {
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	
	// error handling if malloc fails
	if (node == NULL) {
		printf("initNode() failed\n");
		exit(1);
	}

	node->keyCount = 0;
	node->isLeaf = true;
	for (int i = 0;i < ORDER - 1; i++) {
		node->keys[i] = -1;
	}
	for (int i = 0; i < ORDER; i++) {
		node->children[i] = NULL;
	}

	return node;
}


int main() {
	root = initNode();

	for (int i = 0;i < ORDER - 1; i++) {
		printf("%d ", root->keys[i]);
	}

	return 0;
}