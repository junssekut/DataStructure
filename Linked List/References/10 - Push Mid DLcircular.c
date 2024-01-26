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
    }
    else{
        (*tail)->next = new_node;
        *tail = new_node;
        (*tail)->prev = temp;
    }
    // karena circular hubungkan tail dan head
    (*tail)->next = *head;
    (*head)->prev = *tail;
}

void show_nodes(struct Node *head){
    struct Node *temp = head;

    int i=1;
    while(temp != head->prev){
        printf("Node : %d,   value : %d\n",i,temp->value);
        temp = temp->next;
        i++;
    }
    printf("Node : %d,   value : %d\n",i,temp->value);
}

void push_mid(struct Node **head, struct Node **tail, int value, int pos){
    if(*head == NULL){
        *head = create_node(value);
        return;
    }

    struct Node *new_node = create_node(value);
    struct Node *current = *head;
    struct Node *previous = NULL;

    int i = 1;
    while(current != *tail && i < pos){
        previous = current;
        current = current->next;
        i++;
    }

    if(current == *head){ // jika di head, push head
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;

        // update circular
        (*head)->prev = *tail;
        (*tail)->next = *head;
    }
    else if(current == *tail){ // jika pos di tail, push tail
        push_tail(head,tail,value);
    }
    else{ // jika di tengah-tengah
        previous->next = new_node;
        new_node->prev = previous;
        new_node->next = current;
        current->prev = new_node;
    }
}

int main() {

    struct Node *head = NULL;
    struct Node *tail = NULL;

    push_tail(&head,&tail,33);
    push_tail(&head,&tail,3);
    push_tail(&head,&tail,5);
    push_tail(&head,&tail,81);
    show_nodes(head);

    printf("\n=== Insert value 72, to pos 3 ===\n");
    push_mid(&head,&tail,72,3);
    show_nodes(head);

    // === debugging circular ===
    // printf("\nprev h : %d\nval : %d\nnext : %d\n\n",head->prev->value,head->value,head->next->value);
    // printf("prev h : %d\nval : %d\nnext : %d\n\n",head->next->prev->value,head->next->value,head->next->next->value);
    // printf("prev h : %d\nval : %d\nnext : %d\n",tail->prev->value,tail->value,tail->next->value);

    return 0;
}