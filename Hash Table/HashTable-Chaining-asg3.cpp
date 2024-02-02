#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int value;
	Node* next;	
};

struct Table {
	int size;
	Node** values;
};

int hash(int val, int size) {
	return val % size;
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

Node* createNode(int value) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	
	newNode->value = value;
	newNode->next = NULL;
	
	return newNode;
}

void pushTail(Node** head, int value) {
	Node* newNode = createNode(value);
	
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	
	Node* ptr = *head;
	while (ptr->next != NULL) ptr = ptr->next;
	
	ptr->next = newNode;
}

void insert(Table** table, int size, int value) {
	int hashCode = hash(value, size);
	
	pushTail(&(*table)->values[hashCode], value);
}

int get(Table** table, int size, int value) {
	int hashCode = hash(value, size);
	
	Node* ptr = (*table)->values[hashCode];
	while (ptr != NULL && ptr->value != value) {
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
			printf("%d -> ", ptr->value);
			ptr = ptr->next;
		}
		puts("");
	}
}

int main() {
	int n = 10;
	Table* table = createTable(n);
	
	int w[] = {
		27, 72, 63, 42, 36, 18, 29, 101 
	};
	int nw = sizeof(w) / sizeof(w[0]);
	
	printf("Key|Value\n");
	for (int i = 0; i < nw; i++) {
		insert(&table, n, w[i]);
	}
	
	display(table);
		
	return 0;
}
