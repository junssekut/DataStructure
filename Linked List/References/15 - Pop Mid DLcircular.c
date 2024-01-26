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

void pop_mid(struct Node **head, struct Node **tail, int value){
    if(*head == NULL){
        printf("Tidak terdapat list!. Delete tail gagal.\n");
        return;
    }

    struct Node* previous = NULL;
    struct Node* current = *head;

    while(current->value != value && current != *tail){
        previous = current;
        current = current->next;
    }

    // jika udah diujung, dan ga sama nilainya
    if(current == *tail && current->value != value){
        printf("Value %d, tidak ditemukan didalam list!\n",value);
        return;
    }

    if(current == *head){ // pop head
        *head = (*head)->next;
        
        // buat circular
        (*head)->prev = *tail;
        (*tail)->next = *head;
    }
    else if(current == *tail){ // pop tail
        *tail = (*tail)->prev;

        (*head)->prev = *tail; 
        (*tail)->next = *head;
    }
    else { // pop mid
        previous->next = current->next;
        current->next->prev = previous;
    }

    // janlup free, trus null
    free(current);
    current = NULL;
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

    push_tail(&head,&tail,22);
    push_tail(&head,&tail,39);
    push_tail(&head,&tail,56);
    push_tail(&head,&tail,50);
    push_tail(&head,&tail,12);
    show_nodes(head);

    printf("\n=== Delete by value 50 (mid) ===\n");
    pop_mid(&head,&tail,50);
    show_nodes(head);

    // === debugging circular ===
    // printf("\nprev h : %d\nval : %d\nnext : %d\n\n",head->prev->value,head->value,head->next->value);
    // printf("prev h : %d\nval : %d\nnext : %d\n\n",head->next->prev->value,head->next->value,head->next->next->value);
    // printf("prev h : %d\nval : %d\nnext : %d\n",tail->prev->value,tail->value,tail->next->value);

    return 0;
}