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

void pop_tail(struct Node **head, struct Node **tail){
    if(*head == *tail) {
        free(head);
        *head = *tail = NULL;
        return;
    }
    
    struct Node *temp = *head;
    while(temp->next != *tail) {
        temp = temp->next;
    }

    free(*tail);
    *tail = temp;
    (*tail)->next = NULL;
}

int main() {
    struct Node *head = NULL;
    struct Node *tail = NULL;

    push_tail(&head,&tail,65);
    push_tail(&head,&tail,45);
    push_tail(&head,&tail,25);
    push_tail(&head,&tail,67);
    push_tail(&head,&tail,59);
    show_nodes(head);

    printf("\n=== delete value 59 (tail) ===\n");
//    pop_tail(&head,&tail);
	
	struct Node* temp = tail->prev;
	free(tail);
	printf("%d\n", temp->value);
	tail = temp;
	tail->next = NULL;
	
    show_nodes(head);

    // printf("prev h : %d\nval : %d\nnext : %d\n",head->next->prev->value,head->next->value,head->next->next->value);

    return 0;
}
