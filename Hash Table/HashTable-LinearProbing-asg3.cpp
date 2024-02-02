#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hash(int val, int size) {
	char strBuffer[1024];
	int hashCode = 0;
	sprintf(strBuffer, "%d", val);
	for (int i = 0; i < strlen(strBuffer); i++) {
		hashCode += strBuffer[i];
	}
	return val % size;
}

int insert(int arr[], int size, int value) {
	int hashCode = hash(value, size);
	int step = 0;
	
	if (arr[hashCode] != NULL) {
		bool searchFromBeginning = true;
		for (int i = hashCode + 1; i < size; i++) {
			step++;
			if (arr[i] == NULL) {
				searchFromBeginning = false;
				hashCode = i;
				break;
			}
		}
		
		if (searchFromBeginning) {
			for (int i = 0; i < hashCode; i++) {
				step++;
				if (arr[i] == NULL) {
					hashCode = i;
					break;
				}
			}
		}
		
		if (arr[hashCode] != NULL) {
			return -1;
		}
	}
	
	arr[hashCode] = value;
	return step;
}
//
//char* get(char arr[][1024], int size, int* key) {
//	int hashCode = hash(key, size);
//	
//	if (strcmp(arr[hashCode], key) != 0) {
//		bool searchFromBeginning = true;
//		for (int i = hashCode + 1; i < size; i++) {
//			if (strcmp(arr[i], key) == 0) {
//				searchFromBeginning = false;
//				hashCode = i;
//				break;
//			}
//		}
//		
//		if (searchFromBeginning) {
//			for (int i = 0; i < hashCode; i++) {
//				if (strcmp(arr[i], key) == 0) {
//					hashCode = i;
//					break;
//				}
//			}
//		}
//		
//		if (strcmp(arr[hashCode], key) != 0) return NULL;
//	}
//	
//	return arr[hashCode];
//}

int main() {
	int n = 10;
	int arr[n];
	for (int i  = 0; i < n; i++) arr[i] = NULL;
	
	int w[] = {
		27, 72, 63, 42, 36, 18, 29, 101 
	};
	int wn = 8;
	
	printf("Key|Computed Hash (Index)|Step\n");
	for (int i = 0; i < wn; i++) {
		int s = insert(arr, n, w[i]);
		int hashCode = hash(w[i], n);
		printf("%d|%d|%d\n", (hashCode + s % n), w[i], s);
	}
	
	return 0;
}
