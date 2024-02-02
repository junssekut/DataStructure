#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Queue Queue;

struct Node {
    int val;
    Node *next;
};

struct Queue{
    Node *head;
    Node *tail;
};

void push_tail(int data, Queue *q){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->val = data;
    newNode->next = NULL;
    if(q->head == NULL){
        q->head = newNode;
        q->tail = newNode;
    }
    else{
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

void freeAll(Queue *q){
    Node *temp = q->head;
    while(temp!= NULL){
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    q->head = NULL;
    q->tail = NULL;
    free(q);
}

void print(Queue *q){
    Node *temp = q -> head;
    while(temp!= NULL){
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void pop_head(Queue *q){
    Node *temp = q -> head;
    if(temp!= NULL){
        q -> head = q -> head -> next;
        free(temp);
    }
    if (q -> head == NULL){
        q -> tail = NULL;
    }
}

int main(){
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    push_tail(10, queue);
    push_tail(20, queue);
    push_tail(30, queue);
    pop_head(queue);
    print(queue);

    freeAll(queue);

    return 0;
}