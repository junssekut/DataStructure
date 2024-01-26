#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	Node* next;
};

Node* head = NULL;
Node* tail = NULL;

Node* createNode(int value) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	
	newNode->value = value;
	newNode->next = NULL;
	
	return newNode;
}

void pushHead(int value) {
	Node* newNode = createNode(value);
	
	if (head == NULL) {
		head = tail = newNode;
	} else {
		newNode->next = head;
		head = newNode;
	}
}

void pushTail(int value) {
	Node* newNode = createNode(value);
	
	if (head == NULL) {
		head = tail = newNode;
	} else {
		tail->next = newNode;
		tail = newNode;
	}
}

void pushMiddle(int value, int index) {
	if (index == 0) {
		pushHead(value);
		return;
	}
	
	Node* newNode = createNode(value);
	Node* current = head;
	Node* prev = NULL;
	int i = 0;
	
	while (i < index) {
		prev = current;
		if (prev == NULL) {
			puts("index not found");
			return;
		}
		current = current->next;
		i++;
	}
	
	newNode->next = current;
	prev->next = newNode;
}

void popHead() {
	if (head == NULL) return;
	
	Node *current = head;
	
	if (current == tail) {
		head = tail = NULL;
	} else {
		head = current->next;
	}
	
	free(current);
}

void popTail() {
	if (head == NULL) return;
	
	Node* current = head;
	
	if (current == tail) {
		free(current);
		head = tail = current = NULL;
	} else {
		while (current->next != tail) {
			current = current->next;
		}
		
		free(tail);
		
		tail = current;
		
		if (tail != NULL) {
			tail->next = NULL;
		} else {
			head = tail = NULL;
		}
	}
}

void popMiddle(int index) {
	if (head == NULL) {
		puts("linked list is empty");
		return;
	}
	
	Node* current = head;
	Node* prev = NULL;
	int i = 0;
	
	while (i < index) {
		prev = current;
		current = current->next;
		
		if (current == NULL) {
			puts("index not found");
			return;
		}
		
		i++;
	}
	
	prev->next = current->next;
	free(current);
}

void displayNodes() {
	Node* current = head;
	
	while (current != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
	
	puts("");
}

Node* search(int value) {
	if (head == NULL) return NULL;
	
	Node* current = head;
	
	while (current != NULL) {
		if (current->value == value) {
			return current;
		}
		current = current->next;
	}
	
	return NULL;
} 

int main() {
	
	pushTail(3);
	pushTail(1);
	pushTail(7);
	pushTail(8);
	
	displayNodes();
	
	pushMiddle(10, 3);
	
	displayNodes();
	
	popMiddle(4);
	
	displayNodes();
	
	return 0;
}
