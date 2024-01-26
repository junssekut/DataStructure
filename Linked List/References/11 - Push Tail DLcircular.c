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


int main() {

    struct Node *head = NULL;
    struct Node *tail = NULL;

    push_tail(&head,&tail,84);
    push_tail(&head,&tail,26);
    push_tail(&head,&tail,92);
    push_tail(&head,&tail,57);
    show_nodes(head);

    printf("\n=== Insert value 80, to tail ===\n");
    push_tail(&head,&tail,80);
    show_nodes(head);

    // === debugging circular ===
    // printf("\nprev h : %d\nval : %d\nnext : %d\n\n",head->prev->value,head->value,head->next->value);
    // printf("prev h : %d\nval : %d\nnext : %d\n\n",head->next->prev->value,head->next->value,head->next->next->value);
    // printf("prev h : %d\nval : %d\nnext : %d\n",tail->prev->value,tail->value,tail->next->value);

    return 0;
}