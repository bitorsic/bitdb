#include <stdlib.h>
#include <stdio.h>
#include "../include/index.h"

int main() {
	initRoot();

	for(;;) {
		int input;
		printf("1. insert\n2. print\n3. exit\n");
		printf(">> ");
		scanf("%d", &input);

		switch (input) {
		case 1:
			int key;
			printf("key: ");
			scanf("%d", &key);
			insertKeyInTree(key);
			break;

		case 2:
			printEntireTree();
			break;

		case 3:
			freeRoot();
			exit(1);
			
		default:
			break;
		}
	}

	return 0;
}