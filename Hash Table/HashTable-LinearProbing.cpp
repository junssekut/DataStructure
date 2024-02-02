#include <stdio.h>
#include <string.h>

int hash(const char* str, int size) {
	int hashCode = 0;
	hashCode += str[0] - 'a';
	hashCode += str[strlen(str) - 1] - 'a';
	return hashCode % size;
}

bool isEmpty(const char* str) {
	return strlen(str) == 0;
}

int insert(char arr[][1024], int size, const char* value) {
	int hashCode = hash(value, size);
	int step = 0;
	
	if (!isEmpty(arr[hashCode])) {
		bool searchFromBeginning = true;
		for (int i = hashCode + 1; i < size; i++) {
			step++;
			if (isEmpty(arr[i])) {
				searchFromBeginning = false;
				hashCode = i;
				break;
			}
		}
		
		if (searchFromBeginning) {
			for (int i = 0; i < hashCode; i++) {
				step++;
				if (isEmpty(arr[i])) {
					hashCode = i;
					break;
				}
			}
		}
		
		if (!isEmpty(arr[hashCode])) {
//			printf("Tried to insert %s, but array is full.\n", value);
			return step;
		}
	}
	
		
//	printf("Inserted %s at %d.\n", value, hashCode);
	strcpy(arr[hashCode], value);
	
//	puts("");
	return step;
}

char* get(char arr[][1024], int size, const char* key) {
	int hashCode = hash(key, size);
	
	if (strcmp(arr[hashCode], key) != 0) {
		bool searchFromBeginning = true;
		for (int i = hashCode + 1; i < size; i++) {
			if (strcmp(arr[i], key) == 0) {
				searchFromBeginning = false;
				hashCode = i;
				break;
			}
		}
		
		if (searchFromBeginning) {
			for (int i = 0; i < hashCode; i++) {
				if (strcmp(arr[i], key) == 0) {
					hashCode = i;
					break;
				}
			}
		}
		
		if (strcmp(arr[hashCode], key) != 0) return NULL;
	}
	
	return arr[hashCode];
}

int main() {
	int n = 10;
	char arr[n][1024];
	for (int i = 0; i < n; i++) strcpy(arr[i], "");
	
	char w[][1024] = {
		"rainbow",
"street",
"lake",
"mountain",
"world",
"brain",
"main",
"lose",
"straight",
"rain",
	};
	
	char result[1024][1024];
	int resultIndex = 0;
	
	for (int i = 0; i < 10; i++) {
		int s = insert(arr, n, w[i]);
//		printf("%d|%s|%d\n", (hash(w[i], n) + s) % n, w[i], s);
		char resultBuffer[1024];
		int hashCode = (hash(w[i], n) + s) % n;
		{
			sprintf(resultBuffer, "%d|%s|%d\n", hashCode, w[i], s);
		}
		strcpy(result[hashCode], resultBuffer);
		if (resultIndex < hashCode) resultIndex = hashCode;
	}
	
	printf("Key|Value|Step\n");
	for (int i = 0; i <= resultIndex; i++) {
		printf("%s", result[i]);
	}
	
	
	return 0;
}
