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

void push_mid(struct Node **head, struct Node **tail, int value, int idx) {
    struct Node *new_node = create_node(value);

    if (*head == NULL) {
        *head = *tail = new_node;
        return;
    }

    // Insert position selain di head
    struct Node *prev = NULL;
    struct Node *current = *head;

    int i = 1;
    while (i < idx && current != *tail) {
        prev = current;
        current = current->next;
        i++;
    }
    
    if (current == *head) { // push head
        new_node->next = *head;
        *head = new_node;
        (*tail)->next = *head;
    }
    else if(current == *tail){ // push tail
        (*tail)->next = new_node;
        *tail = new_node;

        (*tail)->next = *head; // karena circular, kita sambungin ke head
    }
    else { // push mid
        prev->next = new_node;
        new_node->next = current;
    }
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
    
    push_tail(&head, &tail, 1);
    push_tail(&head, &tail, 84);
    push_tail(&head, &tail, 55);
    push_tail(&head, &tail, 19);
    push_tail(&head, &tail, 68);
    show_nodes(head, tail);

    printf("\n==== Insert 17 to node 4 (mid) ====\n");
    push_mid(&head, &tail, 17, 4); // insert 17 to node 4
    show_nodes(head, tail);
    // printf("%d\n",tail->next->value);

    return 0;
}