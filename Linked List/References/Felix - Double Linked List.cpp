#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;

struct Node {
    int val;
    Node *next;
    Node *prev;
};

void beginsert(Node **head, int data){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> val = data;
    newNode -> prev = NULL;
    newNode -> next = NULL;
    if (*head == NULL){
        *head = newNode;
    } else {
        newNode -> next = *head;
        (*head) -> prev = newNode;
        *head = newNode;
    }
}

void lastInsert(Node **head, int data){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> val = data;
    newNode -> prev = NULL;
    newNode -> next = NULL;
    if (*head == NULL){
        *head = newNode;
    } else {
        Node *ptr = *head;
        while (ptr -> next != NULL){
            ptr = ptr -> next;
        }
        newNode -> prev = ptr;
        ptr -> next = newNode;
    }
}

void insertAt(Node **head, int data, int idx){
    if (idx == 0) {
        beginsert(head, data);
        return;
    }
    if (*head == NULL){
        printf("Idx out of bound\n");
        return;
    } else {
        int i = 0;
        Node *prev = NULL;
        Node *ptr = *head;
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode -> val = data;
        newNode -> prev = NULL;
        newNode -> next = NULL;
        while (i < idx){
            i++;
            prev = ptr;
            if (prev == NULL){
                printf("Index out of bound");
                return;
            }
            ptr = ptr -> next;
        }
        newNode -> prev = prev;
        newNode -> next = ptr;
        prev -> next = newNode;
        if (ptr != NULL) ptr -> prev = newNode;
    }
}

void beginDelete(Node **head){
    if (*head == NULL){
        printf("LIST IS EMPTY\n");
        return;
    } 
    if ((*head) -> next == NULL){
        free(*head);
        *head = NULL;
        return;
    }
    *head = (*head) -> next;
    free((*head) -> prev);
    (*head) -> prev = NULL;
}

void lastDelete(Node **head){
    if (*head == NULL){
        printf("LIST IS EMPTY\n");
        return; 
    }
    if ((*head) -> next == NULL){
        free(*head);
        (*head) = NULL;
        return;
    }
    Node *ptr = *head;
    while (ptr -> next != NULL){
        ptr = ptr -> next;
    }
    ptr -> prev -> next = NULL;
    free(ptr);
}

void deleteAt(Node **head, int idx){
    if (*head == NULL){
        printf("LIST IS EMPTY\n");
        return;
    }
    if (idx == 0){
        beginDelete(head);
        return;
    }
    if ((*head) -> next == NULL){
        printf("Index out of bound\n");
        return;
    }
    int i = 0;
    Node *ptr = *head;
    Node *prev = NULL;
    while (i < idx){
        i ++;
        prev = ptr;
        ptr = ptr -> next;
        if (ptr == NULL){
            printf("Index out of bound\n");
            return;
        }
    }
    Node *temp = ptr;
    prev -> next = ptr -> next;
    ptr = ptr -> next;
    free(temp);
    if (ptr != NULL){
        ptr -> prev = prev;
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

void search(Node *head, int search){
    Node *ptr = head;
    int idx = 0;
    while (ptr != NULL){
        if (ptr -> val == search){
            printf("%d found at index %d\n", search, idx);
            return;
        }
        idx++;
        ptr = ptr -> next;
    }
    printf("Not Found");
}

int main(){
    Node *head = NULL;
    beginsert(&head, 1);
    print(head);

    beginsert(&head, 2);
    print(head);

    lastInsert(&head, 3);
    print(head);

    insertAt(&head, 4, 4);
    print(head);

    beginDelete(&head);
    print(head);

    lastDelete(&head);
    print(head);

    deleteAt(&head, 1);
    print(head);

    search(head, 4);

    freeAll(head);

    return 0;
}
