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

void pop_head(struct Node **head){
    if(*head == NULL){
        printf("List is empty!. Cannot delete head.\n");
        return;
    }

    *head = (*head)->next;
    free((*head)->prev);
    (*head)->prev = NULL;
}

int main() {

    struct Node *head = NULL;
    struct Node *tail = NULL;

    push_tail(&head,&tail,39);
    push_tail(&head,&tail,23);
    push_tail(&head,&tail,1);
    push_tail(&head,&tail,96);
    push_tail(&head,&tail,26);
    show_nodes(head);

    printf("\n=== delete value 39 (head) ===\n");
    pop_head(&head);
    show_nodes(head);
    
    // printf("prev h : %d\nval : %d\nnext : %d\n",head->next->prev->value,head->next->value,head->next->next->value);


    return 0;
}