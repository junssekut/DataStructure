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

void pop_tail(struct Node **head, struct Node **tail){
    struct Node* current = *head;
    struct Node* prev = NULL;
    while(current != *tail){
        prev = current;
        current = current->next;
    }
    free(*tail);
    *tail = prev;
    (*tail)->next = *head;
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
    
    push_tail(&head, &tail, 59);
    push_tail(&head, &tail, 31);
    push_tail(&head, &tail, 89);
    push_tail(&head, &tail, 73);
    push_tail(&head, &tail, 95);
    show_nodes(head, tail);

    printf("\n==== Delete value 95 (tail) ====\n");
    pop_tail(&head,&tail);
    show_nodes(head, tail);
    // printf("%d\n",tail->next->value);

    return 0;
}