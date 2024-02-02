#include <stdlib.h>
#include <stdio.h>

#include "./stack.h"

struct Stack {
	char value;
	Stack* next;
};

Stack* createStack(char value) {
	Stack* newStack = (Stack*) malloc(sizeof(Stack));
	
	newStack->value = value;
	newStack->next = NULL;
	
	return newStack;
}

int push(Stack** top, char value) {
	Stack* newStack = createStack(value);
	
	if (*top == NULL) {
		*top = newStack;
		return 2;
	}
	
	newStack->next = (*top)->next;
	(*top) = newStack;
	return 1;
}

int pop(Stack** top) {
	if (*top == NULL) return 2;
	
	Stack* temp = *top;
	(*top) = (*top)->next;
	free(temp);
	return 1;
}

bool isEmpty(Stack* top) {
	return top == NULL;
}

char peek(Stack* top) {
	if (top == NULL) return '\0';
	
	return top->value;
}

char peekAndPop(Stack** top) {
	char value = peek(*top);
	pop(top);
	return value;
}

void display(Stack* top) {
	if (top == NULL) return;
	
	Stack* ptr = top;
	
	while (ptr != NULL) {
		printf("%c ", ptr->value);
		ptr = ptr->next;
	}
}
