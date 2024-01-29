#include <stdio.h>
#include <stdlib.h>

struct Stack {
	int value;
	Stack* next;
};

Stack* top = NULL;

Stack* createStack(int value) {
	Stack* newStack = (Stack*) malloc(sizeof(Stack));
	
	newStack->value = value;
	newStack->next = NULL;
	
	return newStack;
}

void push(int value) {
	Stack* newStack = createStack(value);
	
	newStack->next = top;
	
	top = newStack;
}

bool isEmpty() {
	return top == NULL;
}

int peek() {
	if (top == NULL) {
		puts("Stack is empty.");
		return -1;	
	}
	
	return top->value;
}

void pop(Stack* top) {
	if (top == NULL) {
		puts("Stack is empty.");
		return;
	}
	
	Stack* temp = top;
	top = top->next;
	free(temp);
}

void display() {
	if (top == NULL) {
		puts("Stack is empty.");
		return;
	}
	
	Stack* current = top;
	while (current != NULL) {
		printf("%d ", current->value);
		current = current->next;
	}
}

int main() {
	top = createStack(5);
	
	push(3);
	push(4);
	push(1);
	push(2);
	
	display();
	
	return 0;
}
