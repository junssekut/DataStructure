#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
    char op[255];
    Node *next;
};

struct Stack {
    Node *top;
};

char* pop (Node **top){
	if (top == NULL){
		printf("Stack is empty\n");
		return "";
	}
    char *val = malloc(sizeof(char) * 255);
    strcpy(val, (*top)->op);
    Node *temp = *top;
    *top = (*top)->next;
    free(temp);
    return val;
}

Node * push(Node *top, const char * op){
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode -> op, op);
    newNode -> next = NULL;
    if (top == NULL){
        top = newNode;
    } else {
        newNode -> next = top;
        top = newNode;
    }
    return top;
}

void freeAll(Stack *stack){
    Node *ptr = stack -> top;
    while (ptr!= NULL){
        Node *temp = ptr;
        ptr = ptr -> next;
        free(temp);
    }
    free(stack);
}

int main() {
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    char postfix[] = "7 6 5 * 3 2 ^ - +";
    int temp = 0;
    int trigger = 0;
    int i;
    for (i = 0; i < strlen(postfix); i++){
        if (postfix[i] >= '0' && postfix[i] <= '9'){
            temp *= 10;
            temp += postfix[i] - '0';
            trigger = 1;
        } else if (postfix[i] == ' '){
            if (trigger){
                char temps[255];
                sprintf(temps, "%d", temp);
                s -> top = push(s -> top, temps);
                temp = 0;
                trigger = 0;
            }
        } else {
            char num1[255];
            strcpy(num1, pop(&(s -> top)));
            char num2[255];
            strcpy(num2, pop(&(s -> top)));
            char temp2[101];
            sprintf(temp2, "(%s %c %s)", num2, postfix[i], num1);
            s -> top = push(s -> top, temp2);
        }
    }
    printf("%s\n", s -> top -> op);
    freeAll(s);

    return 0;
}
