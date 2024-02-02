#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
    char op;
    Node *next;
};

struct Stack {
    Node *top;
};

char pop (Node **top){
	if (top == NULL){
		printf("Stack is empty\n");
		return ' ';
	}
    char val = (*top)->op;
    Node *temp = *top;
    *top = (*top)->next;
    free(temp);
    return val;
}

Node * push(Node *top, char op){
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
    char infix[] = "2^3^4";
    char postfix[255] = "\0";
    int precedence[101];
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;
    precedence['^'] = 3;
    precedence['('] = 0;
    precedence[')'] = 0;
    for (int i = 0; i < strlen(infix); i++){
        Node *ptr = s -> top;
        if (infix[i] >= '0' && infix[i] <= '9'){
            char temp[11];
            int idx = 0;
            while (infix[i] >= '0' && infix[i] <= '9'){
                temp[idx++] = infix[i++];
            }
            i--;
            temp[idx] = ' ';
            temp[idx + 1] = '\0';
            strcat(postfix,  temp);
        } else if (infix[i] == ' '){
            continue;
        } else {
            if (infix[i] == ')'){
                char temp[3];
                while (s -> top -> op != '('){
                    temp[0] = pop(&s -> top);
                    temp[1] = ' ';
                    temp[2] = '\0';
                    strcat(postfix, temp);
                }
                pop(&(s->top));
            } else if (infix[i] == '(') {
                s->top = push(s -> top, infix[i]);
            } else {
                char temp[3];
                if (s -> top != NULL) {
                    while (s -> top != NULL && precedence[infix[i]] <= precedence[s -> top -> op]){
                        temp[0] = pop(&(s->top));
                        temp[1] =' ';
                        temp[2] = '\0';
                        strcat(postfix, temp);
                    }
                }
                s->top = push(s -> top, infix[i]);
            }
        }
    }
    while (s -> top != NULL){
        char temp[3];
        temp[0] = pop(&(s -> top));
        temp[1] =' ';
        temp[2] = '\0';
        strcat(postfix, temp);
    }
    postfix[strlen(postfix) - 1] = '\0';
    printf("%s\n", postfix);
    freeAll(s);
    return 0;
}
