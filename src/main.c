#include <stdlib.h>
#include <stdio.h>
#include "../include/index.h"

int main() {
	initRoot();

	insertKeyInTree(10);
	insertKeyInTree(30);
	insertKeyInTree(20);

	printEntireTree();

	freeRoot();
	return 0;
}