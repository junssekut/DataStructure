#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

struct Node *create_node(int value){
    struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

void push_tail(struct Node **head, struct Node **tail, int value){
    struct Node *new_node = create_node(value);
    
    if(*head == NULL){
        *head = *tail = new_node;
    }
    else{
        (*tail)->next = new_node;
        *tail = (*tail)->next; // memindahkan tail
    }

    (*tail)->next = *head;
}

void pop_mid(struct Node **head, struct Node **tail, int value){
    if(*head == NULL) {
        *head = create_node(value);
        return;
    }
    
    struct Node *current = *head;
    struct Node *previous = NULL;

    while(current->next != *head && current->value != value){
        previous = current;
        current = current->next;
    }

    // jika udah di ujung, trus gaada nilai yang sama
    if(current == *tail && value != (*tail)->value){
        printf("node with value \"%d\" doesn't exist\n",value);
        return;
    }

    if(current == *head){ // pop head;
        *head = (*head)->next;
        (*tail)->next = *head;
    }
    else if(current == *tail){ // pop tail
        *tail = previous;
        (*tail)->next = *head;
    }else{
        previous->next = current->next;
    }

    free(current);
    current = NULL;
}

void show_nodes(struct Node *head, struct Node *tail){
    struct Node *temp = head;
    int i=1;

    while(temp != tail){ // di akalin buat print sirkular
        printf("Node : %d,   value : %d\n",i,temp->value);
        temp = temp->next;
        i++;
    }
    printf("Node : %d,   value : %d\n",i,temp->value);

}

int main() {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    
    push_tail(&head, &tail, 34);
    push_tail(&head, &tail, 33);
    push_tail(&head, &tail, 96);
    push_tail(&head, &tail, 47);
    push_tail(&head, &tail, 57);
    show_nodes(head, tail);

    printf("\n==== Delete by value 33 (mid) ====\n");
    pop_mid(&head,&tail,33);
    show_nodes(head, tail);

    return 0;
}