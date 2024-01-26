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
}

void show_nodes(struct Node *head){
    struct Node *temp = head;
    int i=0;
    while(temp != NULL){
        if(i==0){
            printf("Node : HEAD,   value : %d\n",temp->value);
        }
        else printf("Node : %d,   value : %d\n",i,temp->value);
        temp = temp->next;
        i++;
    }
}

void pop_mid(struct Node **head, struct Node **tail, int value){
    if(*head == NULL){
        printf("Tidak terdapat list!. Gagal delete %d pada list\n",value);
        return;
    }
    struct Node *current = *head;
    struct Node *prev = NULL;

    while(current != NULL && current->value != value){
        prev = current;
        current = current->next;
    }

    if(current == NULL){
        printf("Tidak ada nilai %d, dalam nodes\n",value);
        return;
    }


    if(current == *head){ // jika delete di head, pop head
        *head = (*head)->next;
    }
    else if(current == *tail){ // jika yang di delete ada di tail, pop tail
        *tail = prev;
    }
    else{ // jika di tengah2
        prev->next = current->next;
    }

    free(current);
    current = NULL;
}

int main() {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    
    push_tail(&head, &tail, 0);
    push_tail(&head, &tail, 60);
    push_tail(&head, &tail, 25);
    push_tail(&head, &tail, 65);
    push_tail(&head, &tail, 23);
    show_nodes(head);

    printf("\n==== Delete 25 (mid) ====\n");
    pop_mid(&head, &tail,25); // pop by value
    show_nodes(head);

    // printf("head = %d\n",head->value);
    // printf("tail = %d\n",tail->value);

    return 0;
}