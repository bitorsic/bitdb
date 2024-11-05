#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
		// use binary search
		int* left = &node->keys[0];
		int* right = &node->keys[node->keyCount - 1];

		while (left <= right) {
			int* mid = left + (right - left) / 2; // pointer arithmetics

			if (*mid == key) {
				printf("Cannot insert %d as it is already present\n", key);
				return;
			} else if (*mid < key) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}

		// left is the index at which to be inserted
		int* index = left;

		// shift all others to right and insert
		right = &node->keys[node->keyCount];
		left = right - 1;

		while (left >= index) {
			*right = *left;
			right--; left--;
		}

		// insert the given key at the index
		*index = key;
	}

	node->keyCount++;
}

void insertKeyInTree(int key) {
	if (root->isLeaf) {
		insertKeyInNode(key, root);
	}
}

int main() {
	root = initNode();

	insertKeyInTree(10);
	insertKeyInTree(30);
	insertKeyInTree(20);

	// for (int i = 0;i < MAX_KEYS; i++) {
	// 	printf("%d ", root->keys[i]);
	// }

	printTree(root, 0);

	return 0;
}