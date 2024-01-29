#include <stdio.h>
#include <stdlib.h>

struct Stack {
	int value;
	Stack* next;
};

Stack* top = NULL;

void push(int value) {
	Stack* newStack = (Stack*) malloc(sizeof(Stack));
	
	newStack->value = value;
	newStack->next = NULL;
	
	if (top == NULL) {
		top = newStack;
	} else {
		newStack->next = top;
		top = newStack;
	}
}

int peek() {
	if (top == NULL) {
		puts("Stack is empty.");
		return -1;	
	}
	
	return top->value;
}

void pop() {
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
	
	puts("");
}

int main() {
	push(3);
	push(4);
	push(1);
	push(2);
	
	display();
	
	return 0;
}
