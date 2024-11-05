#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/utils.h"

#define ORDER 4
#define MAX_KEYS (ORDER - 1)
#define MIN_KEYS (ORDER / 2)

// Node for the B-tree
struct Node {
	int keys[MAX_KEYS];
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
	for (int i = 0;i < MAX_KEYS; i++) {
		node->keys[i] = -1;
	}
	for (int i = 0; i < ORDER; i++) {
		node->children[i] = NULL;
	}

	return node;
}

void initRoot() {
	root = initNode();
}

void freeRoot() {
	free(root);
}

void printTree(struct Node* root, int depth) {
	if (root == NULL) {
        return;
    }

	// space before to denote the level
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }

	// printing keys
    printf("[");
    for (int i = 0; i < root->keyCount; i++) {
        printf("%d", root->keys[i]);
        if (i < root->keyCount - 1) {
            printf(",");
        }
    }
    printf("]\n");

    // recursion for children
    if (!root->isLeaf) {
        for (int i = 0; i <= root->keyCount; i++) {
            printTree(root->children[i], depth + 1);
        }
    }
}

void insertKeyInNode(int key, struct Node* node) {
	if (node->keyCount == 0) {
		node->keys[0] = key;
	} else if (node->keyCount < MAX_KEYS) {
		int* findResult;
		
		findResult = findIndexForKey(key, node->keys, node->keyCount);
		if (findResult[1] == 1) {
			printf("Cannot insert %d as it is already present\n", key);
			return;
		}

		int index = findResult[0];

		insertKeyAtIndex(key, index, node->keys, node->keyCount);

		free(findResult);
	} else {
		// TODO: write logic to split tree
	}

	node->keyCount++;
}

void insertKeyInTree(int key) {
	if (root->isLeaf) {
		insertKeyInNode(key, root);
	} else {
		// TODO: write logic to traverse until leaf node arrives
	}
}

void printEntireTree() {
	printTree(root, 0);
}