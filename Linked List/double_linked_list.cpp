#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	Node* prev;
	Node* next;
};

Node* head = NULL;
Node* tail = NULL;

Node* createNode(int value) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	
	newNode->value = value;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

void pushHead(int value) {
	Node* newNode = createNode(value);
	
	if (head == NULL) {
		head = tail = newNode;
	} else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pushTail(int value) {
	Node* newNode = createNode(value);
	
	if (head == NULL) {
		head = tail = newNode;
	} else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}

void pushMiddle(int value, int index) {
	if (head == NULL) {
		puts("linked list is empty");
		return;	
	}
	
	Node* current = head;
	Node* prev = NULL;
	int i = 0;
	
	while (current != tail && i < index) {
		prev = current;
		current = current->next;
		if (current->next == NULL) {
			puts("index not found");
			return;
		}
		i++;
	}
	
	if (current == head) pushHead(value);
	else if (current == tail) pushTail(value);
	else {
		Node* newNode = createNode(value);
		
		prev->next = newNode;
		newNode->prev = prev;
		newNode->next = current;
		current->prev = newNode;
	}
}

void popHead() {
	if (head == NULL) return;
	
	if (head == tail) {
		free(head);
		head = tail = NULL;
	} else {
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
}

void popTail() {
	if (head == NULL) return;
	
	if (head == tail) {
		free(head);
		head = tail = NULL;
	} else {
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL;
	}
}

void popMiddle(int index) {
	if (head == NULL) {
		puts("linked list is empty");
		return;	
	}
	
	int i = 0;
	Node* current = head;
	Node* prev = NULL;
	
	while (i < index) {
		prev = current;
		current = current->next;
		i++;
	}
	
	if (current == NULL) {
		puts("data not found");
		return;
	}
	
	if (current == head) {
		popHead();
	} else if (current == tail) {
		popTail();
	} else {
		prev->next = current->next;
		current->next->prev = prev;
		
		free(current);
		current = NULL;
	}
	
	
}

Node* searchNode(int value) {
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

void display() {
	Node* current = head;
	
	while (current != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
	
	puts("");
}

int main() {
	pushTail(3);
	pushTail(2);
	pushTail(4);
	pushTail(9);
	
	display();
	
	pushMiddle(3, 134134);
	
	display();

	return 0;
}
