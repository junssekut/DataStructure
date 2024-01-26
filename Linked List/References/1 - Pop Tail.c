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

void pop_tail(struct Node **head, struct Node **tail){
    if(*head == *tail){
        free(head);
        *head = *tail = NULL;
    }
    else{
        struct Node *temp = *head;
        while(temp->next != *tail){
            temp = temp->next;
        }
        free(*tail);
        *tail = temp;
        (*tail)->next = NULL;
    }
}

int main() {

    struct Node *head = NULL;
    struct Node *tail = NULL;
    
    push_tail(&head, &tail, 67);
    push_tail(&head, &tail, 13);
    push_tail(&head, &tail, 62);
    push_tail(&head, &tail, 42);
    push_tail(&head, &tail, 81);
    show_nodes(head);

    printf("\n==== Delete 81 (tail) ====\n");
    pop_tail(&head, &tail);
    show_nodes(head);

    return 0;
}