#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int hashTableSize = 10;

struct hashNode {
	char name[100];
	int value;
	struct hashNode *next;
};

int convertStringToInt(char* string){
    int hashCode = 0;
    for (int i = 0; i < strlen(string); i++) hashCode += string[i];
    hashCode %= hashTableSize;
    return hashCode;
}

void show(hashNode* hashTable[]) {
	struct hashNode *temp = NULL;

	for (int i = 0; i < hashTableSize; i++) {
		temp = hashTable[i];
		printf("[%d] ", i);
		while (temp != NULL) {
			printf("%s:%d -> ", temp->name, temp->value);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

void insert(char* string, int value, hashNode* hashTable[]) {
	int hashCode = convertStringToInt(string);
	
	hashNode* newNode = (hashNode*) malloc(sizeof(hashNode));
	strcpy(newNode->name, string);
	newNode->value = value;
	newNode->next = NULL;
	
	if (hashTable[hashCode] == NULL) {
		hashTable[hashCode] = newNode;
		return;
	}
	
	hashNode* ptr = hashTable[hashCode];
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	ptr->next = newNode;
}

int retrieve(char* string, hashNode* hashTable[]){	
	int hashCode = convertStringToInt(string);
	
	hashNode* ptr = hashTable[hashCode];
	while (ptr != NULL && strcmp(ptr->name, string) != 0) {
		ptr = ptr->next;
	}
	
	if (ptr == NULL) {
		printf("%s:not found\n", string);
		return -1;
	}
	
	printf("%s:%d\n", string, ptr->value);
	
	return ptr->value;
}

int main() {
	struct hashNode* hashTable[hashTableSize];
	for (int i = 0; i < hashTableSize; i++) {
		hashTable[i] = NULL;
	}
	
	insert("Arif", 18, hashTable);
	insert("Agnes", 19, hashTable);
	insert("Indah", 20, hashTable);
	insert("Iman", 21, hashTable);
	insert("Udin", 22, hashTable);
	insert("Umar", 22, hashTable);
	insert("Eko", 21, hashTable);
	insert("Emil", 20, hashTable);
	insert("Olga", 19, hashTable);
	insert("Oky", 18, hashTable);
	
	show(hashTable);
	printf("\n");
	int value = retrieve("Anton", hashTable);
	value = retrieve("Udin", hashTable);
	value = retrieve("Oky", hashTable);
		
	return 0;
}
