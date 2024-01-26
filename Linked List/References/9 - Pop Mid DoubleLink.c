#include <stdio.h>
#include <stdlib.h>

struct Node{
    struct Node* prev;
    int value;
    struct Node* next;
};

struct Node *create_node(int value) {
    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

void push_tail(struct Node **head, struct Node **tail, int value){
    struct Node *new_node = create_node(value);
    struct Node *temp = *tail;

    if(*head == NULL){
        *head = *tail = new_node;
        return;
    }

    (*tail)->next = new_node;
    *tail = new_node;
    (*tail)->prev = temp;
}

void show_nodes(struct Node *head){
    struct Node *temp = head;

    int i=0;
    while(temp != NULL){
        printf("Node : %d,   value : %d\n",i,temp->value);
        temp = temp->next;
        i++;
    }
}

void pop_mid(struct Node **head, struct Node **tail, int value){
    if(*head == NULL) {
        printf("List is empty, cannot pop %d in list\n",value);
        return;
    }

    struct Node *current = *head;
    struct Node *previous = NULL;

    while(current != NULL && current->value != value){
        previous = current;
        current = current->next;
    }

    if(current == NULL){ // ga ketemu
        printf("value : %d, is not on the list!\n",value);
        return;
    }

    if(current == *head){ // jika di head, pop head
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
    else if(current == *tail){ // jika di tail, pop tail
        previous->next = NULL;
        *tail = previous;
    }
    else {  // jika di tengah2
        previous->next = current->next;
        current->next->prev = previous; 
    }

    free(current);
    current = NULL;
}

int main() {

    struct Node *head = NULL;
    struct Node *tail = NULL;

    push_tail(&head,&tail,0);
    push_tail(&head,&tail,83);
    push_tail(&head,&tail,72);
    push_tail(&head,&tail,95);
    push_tail(&head,&tail,42);
    show_nodes(head);

    printf("\n=== delete value 72 (mid) ===\n");
    pop_mid(&head,&tail,72);
    show_nodes(head);

    // printf("prev h : %d\nval : %d\nnext : %d\n",head->next->prev->value,head->next->value,head->next->next->value);

    return 0;
}