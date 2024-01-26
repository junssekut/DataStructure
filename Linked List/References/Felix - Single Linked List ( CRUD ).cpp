#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;

struct Node {
    int val;
    Node *next;
};

void beginsert(Node **head, int data){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> val = data;
    newNode -> next = NULL;
    if (*head == NULL){
        *head = newNode;
    } else {
        newNode -> next = *head;
        *head = newNode;
    }
}

void lastinsert(Node **head, int data){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> val = data;
    newNode -> next = NULL;
    if (*head == NULL){
        *head = newNode;
    } else {
        Node *ptr = *head;
        while (ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = newNode;
    }
}

void insertAt(Node **head, int data, int idx){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> val = data;
    newNode -> next = NULL;
    if (idx == 0){
        beginsert(head, data);
        return;
    }
    if (*head == NULL){
        printf("Index out of bound\n");
    } else {
        int i = 0;
        Node *prev = NULL;
        Node *curr = *head;
        while (i < idx){
            i++;
            prev = curr;
            if (prev == NULL){
                printf("Index out of bound\n");
                return;
            }
            curr = curr -> next;
        }
        newNode -> next = curr;
        prev -> next = newNode;
    }
}

void beginDelete(Node **head){
    if (*head == NULL) {
        printf("LIST IS EMPTY\n");
        return;
    }
    Node *temp = *head;
    *head = (*head) -> next;
    free(temp);
}

void lastDelete(Node *head){
    if (head == NULL){
        printf("LIST IS EMPTY\n");
        return;
    } else if (head -> next == NULL){
        printf("There is only the head\n");
        free(head);
        return;
    }
    Node *ptr = head;
    Node *prev = NULL;
    while (ptr -> next != NULL){
        prev = ptr;
        ptr = ptr -> next;
    }
    prev -> next = NULL;
    free(ptr);
}

void deleteAt(Node **head, int idx){
    if (*head == NULL){
        printf("LIST IS EMPTY\n");
        return;
    } else if (idx == 0){
        beginDelete(head);
        return;
    } else {
        Node *prev = NULL;
        Node *ptr = *head;
        int i = 0;
        while (i < idx){
            i++;
            prev = ptr;
            ptr = ptr -> next;
            if (ptr == NULL){
                printf("Index out of bound\n");
                return;
            }
        }
        prev -> next = ptr -> next;
        free(ptr);
    }
}

void search(Node *head, int value){
    if (head == NULL){
        printf("LIST IS EMPTY\n");
        return;
    } else {
        Node *ptr = head;
        int idx = 0;
        while (ptr != NULL){
            if (ptr -> val == value){
                printf("Found %d at index %d", value, idx);
                return;
            }
            idx ++;
            ptr = ptr -> next;
        }
        printf("%d not found\n", value);
    }
}

void print(Node *head){
    Node *ptr = head;
    while (ptr != NULL){
        printf("%d ", ptr -> val);
        ptr = ptr -> next;
    }
    printf("\n");
}

void freeAll(Node *head){
    Node *ptr = head;
    while (ptr != NULL){
        Node *temp = ptr;
        ptr = ptr -> next;
        free(temp);
    }
}

int main(){
    Node *head = NULL;

    beginsert(&head, 10);
    print(head);

    beginsert(&head, 12);
    print(head);

    lastinsert(&head, 18);
    print(head);

    insertAt(&head, 9, 1);
    print(head);

    insertAt(&head, 100, 4);
    print(head);

    insertAt(&head, 11, 0);
    print(head);

    beginDelete(&head);
    print(head);

    lastDelete(head);
    print(head);

    deleteAt(&head, 1);
    print(head);
    
    search(head, 10);


    freeAll(head);

    return 0;
}
