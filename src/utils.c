#include <stdlib.h>
#include <stdio.h>

// returns [index, found] (found can be 0 or 1)
int* findIndexForKey(int key, int* arr, int n) {
	int* result = malloc(2 * sizeof(int));
	// use binary search
	int* left = &arr[0];
	int* right = &arr[n - 1];

	while (left <= right) {
		int* mid = left + (right - left) / 2; // pointer arithmetics

		if (*mid == key) {
			result[0] = mid - &arr[0];
			result[1] = 1;
			return result;
		} else if (*mid < key) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	// if not found, simply return the index to perform insertion
	result[0] = left - &arr[0];
	result[1] = 0;

	return result;
}

void insertKeyAtIndex(int key, int indexInt, int* arr, int n) {
	// shift all others to right and insert
	int* right = &arr[n];
	int* left = right - 1;
	int* index = &arr[0] + indexInt;

	while (left >= index) {
		*right = *left;
		right--; left--;
	}

	// insert the given key at the index
	*index = key;
}