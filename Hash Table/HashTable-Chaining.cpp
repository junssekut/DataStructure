#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	char value[64];
	Node* next;	
};

struct Table {
	int size;
	Node** values;
};

int hash(const char* str, int size) {
//	int hashCode = 0;
//	for (int i = 0; i < strlen(str); i++) hashCode += str[i];
//	return hashCode % size;
	return strlen(str) % 5;
}

Table* createTable(int size) {
	Table* newTable = (Table*) malloc(sizeof(Table));
	
	newTable->size = size;
	newTable->values = (Node**) malloc(size * sizeof(Node*));
	
	for (int i = 0; i < size; i++) {
		newTable->values[i] = (Node*) malloc(sizeof(Node));
		newTable->values[i] = NULL;	
	}
	
	return newTable;
}

Node* createNode(const char* value) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	
	strcpy(newNode->value, value);
	newNode->next = NULL;
	
	return newNode;
}

void pushTail(Node** head, const char* value) {
	Node* newNode = createNode(value);
	
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	
	Node* ptr = *head;
	while (ptr->next != NULL) ptr = ptr->next;
	
	ptr->next = newNode;
}

void insert(Table** table, int size, const char* value) {
	int hashCode = hash(value, size);
	
	pushTail(&(*table)->values[hashCode], value);
}

char* get(Table** table, int size, const char* value) {
	int hashCode = hash(value, size);
	
	Node* ptr = (*table)->values[hashCode];
	while (ptr != NULL && strcmp(ptr->value, value) != 0) {
		ptr = ptr->next;
		if (ptr == NULL) {
			return NULL;
		}
	}
	
	return ptr->value;
}

void display(Table* table) {
	for (int i = 0; i < table->size; i++) {
		printf("%d|", i);
		Node* ptr = table->values[i];
	
		while (ptr != NULL) {
			printf("%s -> ", ptr->value);
			ptr = ptr->next;
		}
		puts("");
	}
}

int main() {
	int n = 5;
	Table* table = createTable(n);
	
	char w[][1024] = {
		"Hemnes",
	    "Sprutt",
	    "Hodde",
	    "Dvala",
	    "Godmorgon",
	    "Aina",
	    "Sannolikt",
	    "Variera",
	    "Viktigt",
	    "Anvandbar",
	    "Vardagen",
	    "Alex",
	    "Malm",
	    "Micke",
	    "Svartasen",
	    "Skarsta",
	    "Stuva",
	    "Algot",
	    "Glotten",
	    "Gruntal",
	};
	int nw = sizeof(w) / sizeof(w[0]);
	
	printf("No|Value\n");
	for (int i = 0; i < nw; i++) {
		insert(&table, n, w[i]);
	}
	
	display(table);
		
	return 0;
}
