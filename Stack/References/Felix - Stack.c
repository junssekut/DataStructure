#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
    int val;
    Node *next;
};

struct Stack {
    Node *top;
};

int peek(Node *top){
    return top->val;
}

Node *pop_head(Node *top){
    if (top == NULL){
        printf("Stack is empty\n");
        return NULL;
    }
    Node *tmp = top;
    top = top->next;
    free(tmp);
    return top;
}

Node* push_head(int val, Node *top){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> val = val;
    newNode -> next = NULL;
    if (top == NULL){
        top = newNode;
    } else {
        newNode -> next = top;
        top = newNode;
    }
    return top;
}

void print(Node *top){
    Node *ptr = top;
    while (ptr != NULL){
        printf("%d\n", ptr -> val);
        ptr = ptr -> next;
    }
    printf("\n");
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
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack -> top = NULL;
    stack -> top = push_head(10, stack -> top);
    stack -> top = push_head(20, stack -> top);
    stack -> top = push_head(30, stack -> top);
    stack -> top = push_head(40, stack -> top);
    stack -> top = pop_head(stack -> top);
    print(stack -> top);
    freeAll(stack);
    
    return 0;
}