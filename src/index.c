#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/index.h"

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

// function definition
int insertKeyInNode(int key, struct Node* node);

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
	for (int i = 0; i < ORDER; i++) {
		node->children[i] = NULL;
	}

	return node;
}

struct Node* fetchParentNode(struct Node* node) {
	// base case
	if (node == root) {
		return NULL;
	}
		
	// find the parent node
	struct Node* parent;
	struct Node* tempNode = root;

	// using the middle element for efficiency
	int key = node->keys[node->keyCount / 2];

	// traverse through the tree until node with the key is reached
	int* findResult;

	while (tempNode != node) {
		findResult = findIndexForKey(key, tempNode->keys, tempNode->keyCount);
		int index = findResult[0];

		parent = tempNode;
		tempNode = tempNode->children[index];
	}
	
	free(findResult);
	
	return parent;
}

// only leaf nodes can be split using this function
void splitNode(struct Node* node, int* tempArray) {
	if (node->isLeaf == false) {
		printf("splitNode() was wrongfully called on non-leaf node\n");
		exit(1);
	}

	// set the index to where to split from
	int index = ORDER / 2;

	// modify the current node to have the middle element only
	node->isLeaf = false;
	node->keyCount = 1;
	node->keys[0] = tempArray[index];

	// initialize the left and right children
	struct Node* leftChild = initNode();
	struct Node* rightChild = initNode();

	// keys to the left of the middle go to the left child
	leftChild->keyCount = index; // since we wanna copy until (index - 1)
	memcpy(leftChild->keys, tempArray, index * sizeof(int));

	// now for the right child
	int rightKeyCount = MAX_KEYS - index;
	rightChild->keyCount = rightKeyCount;
	memcpy(rightChild->keys, &tempArray[index+1], rightKeyCount * sizeof(int));

	// attach the children
	node->children[0] = leftChild;
	node->children[1] = rightChild;
}

// returns the index at which the node was inserted
// used to insert node with single key, into another node
int insertNodeInNode(struct Node* node, struct Node* to) {
	if (node->keyCount > 1) {
		printf("insertNodeInNode() was wrongfully called on node with multiple keys\n");
		exit(1);
	}

	// find index
	int* findResult;
	findResult = findIndexForKey(node->keys[0], to->keys, to->keyCount);
	if (findResult[1] == 1) {
		free(findResult); return -1;
	}
	int index = findResult[0];
	free(findResult);

	if (to->keyCount < MAX_KEYS) {
		// insert the node's key
		insertKeyAtIndex(node->keys[0], index, to->keys, to->keyCount);

		// shift children to right if needed
		for (int i = to->keyCount + 1; i > index; i--) {
			to->children[i] = to->children[i-1];
		}

		// insert children
		to->children[index] = node->children[0]; // left child
		to->children[index+1] = node->children[1]; // right child
		
		to->keyCount++;
	} else {
		// TODO: insert the children at the correct index of correct tree
		printf("insertNodeInNode(): parent node is full\n");
		exit(1);
	}

	free(node); return index;
}

// returns index at which the key was inserted
int insertKeyInNode(int key, struct Node* node) {
	// base case - empty node
	if (node->keyCount == 0) {
		node->keys[0] = key;
		node->keyCount++;
		return 0;
	}

	// firstly, check if the key already exists
	int* findResult;
	
	findResult = findIndexForKey(key, node->keys, node->keyCount);
	if (findResult[1] == 1) {
		free(findResult); return -1;
	}

	int index = findResult[0]; // key should be inserted here
	free(findResult);
	
	if (node->keyCount < MAX_KEYS) {
		insertKeyAtIndex(key, index, node->keys, node->keyCount);
		node->keyCount++;
		return index;
	}

	// here, node->keyCount = MAX_KEYS
	// split node, since the node has become full
	
	// insert the key in a temp sorted array
	int tempArray[ORDER];
	memcpy(tempArray, node->keys, MAX_KEYS * sizeof(int));
	insertKeyAtIndex(key, index, tempArray, ORDER); // since we already know the index

	splitNode(node, tempArray);

	// insert the split node into its parent
	struct Node* parent = fetchParentNode(node);
	if (parent == NULL) { // since the node itself is the root
		return index;
	}
	
	index = insertNodeInNode(node, parent);

	return index;
}

void printTree(struct Node* root, int depth) {
	if (root == NULL) {
        return;
    }

	// space before to denote the level
    for (int i = 0; i < depth; i++) {
        printf("  ");
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

// ------------------------------------------------------ //

void initRoot() {
	root = initNode();
}

void freeRoot() {
	free(root);
}

void insertKeyInTree(int key) {
	struct Node* node = root;

	// traverse until leaf node arrives
	while (!node->isLeaf) {
		// find index of key which is *just* greater than the given key
		int* findResult;

		findResult = findIndexForKey(key, node->keys, node->keyCount);
		if (findResult[1] == 1) {
			printf("Cannot insert %d as it is already present\n", key);
			free(findResult); return;
		}
		int index = findResult[0];
		node = node->children[index];
		
		free(findResult);
	}

	int index = insertKeyInNode(key, node);
	if (index == -1) {
		printf("Cannot insert %d as it is already present\n", key);
	}
}

void printEntireTree() {
	printTree(root, 0);
}