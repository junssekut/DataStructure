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
	int i = 0;
	
	while (current != NULL && i < index) {
		current = current->next;
		i++;
	}
	
	if (current != NULL) {
		newNode->next = current->next;
		current->next = newNode;
	}
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


}

void displayNodes() {
	Node* current = head;
	
	while (current != NULL) {
		printf("%d -> ", current->value);
		current = current->next;
	}
	
	printf("NULL");
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
	
	return 0;
}
