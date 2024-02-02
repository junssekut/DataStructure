#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
    int op;
    Node *next;
};

struct Stack {
    Node *top;
};

int pop (Node **top){
	if (top == NULL){
		printf("Stack is empty\n");
		return -1;
	}
    int val = (*top) -> op;
    Node *temp = *top;
    *top = (*top)->next;
    free(temp);
    return val;
}

Node * push(Node *top, int op){
    Node *newNode = malloc(sizeof(Node));
    newNode -> op = op;
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

int main(){
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    char ex[] = "7 6 5 * 3 2 ^ - +";
    int temp = 0;
    int trig = 0;
    int i;
    for (i = 0; i < strlen(ex); i++){
        if (ex[i] >= '0' && ex[i] <= '9'){
            temp *= 10;
            temp += ex[i] - '0';
            trig = 1;
        } else if (ex[i] == ' '){
            if (trig){
                trig = 0;
                s->top = push(s->top, temp);
                temp = 0;
            }
        } else {
            int num1 = pop(&(s->top));
            int num2 = pop(&(s->top));

            if (ex[i] == '+'){
                s->top = push(s->top, num2+num1);
            } else if (ex[i] == '-'){
                s->top = push(s->top, num2-num1);
            } else if (ex[i] == '*'){
                s->top = push(s->top, num2*num1);
            } else if (ex[i] == '/'){
                s->top = push(s->top, num2/num1);
            } else {
                s->top = push(s->top, (int) pow(num2, num1));
            }
        }
    }
    printf("%d\n", s->top->op);
    freeAll(s);

    return 0;
}
