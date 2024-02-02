#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define tableSize 29

struct storage{
    int key;
    int qty;
    char name[25];
    char category[20];
    struct storage *next;
};

struct hashPool{
    struct storage *head;
    struct storage *tail;
};
struct hashPool hashTable[tableSize];

void init(){
    for(int i=0; i<tableSize; i++){
        hashTable[i].head = NULL;
        hashTable[i].tail = NULL;
    }
}

int generateKey(char *name){
    int key = 0;
    int len = strlen(name);
    for (int i = 0; i < len; i++) key += name[i];
    return key % tableSize;
}

struct storage *newNode(char *name, char *category){
    struct storage *curr = (struct storage *)malloc(sizeof(struct storage));
    curr->key = generateKey(name);
    curr->qty = 1;
    strcpy(curr->name, name);
    strcpy(curr->category, category);
    curr->next = NULL;
    return curr;
}

struct storage *searchNode(struct storage *node){
    struct storage *search = hashTable[node->key].head;
    struct storage *temp = NULL;
    
    temp = search;
    
    while (temp != NULL) {
    	if (strcmp(temp->name, node->name) == 0 && strcmp(temp->category, node->category) == 0) return temp;
    
    	temp = temp->next;
    	if (temp == NULL) return NULL;
	}
    
    return NULL;
}

void push(struct storage *node){
    if (hashTable[node->key].head == NULL) {
    	hashTable[node->key].head = hashTable[node->key].tail = node;
    	return;
	}
	
	storage *ptr = searchNode(node);
	if (ptr != NULL) {
		ptr->qty += node->qty;
		return;	
	}
	
	ptr = hashTable[node->key].head;
	while (ptr->next != NULL) ptr = ptr->next;
	
	ptr->next = node;
	hashTable[node->key].tail = node;
}

void printAll(){
    for(int i=0; i<tableSize; i++){
        printf("[%2d] : ", i);
        struct storage *curr = hashTable[i].head;
        while(curr != NULL){
            printf("%-10s (%-3d) -> ", curr->name, curr->qty);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main(){
    init();
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Gulai Kambing", "Daging"));
    push(newNode("Kangkung", "Sayuran"));
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Coca Cola", "Minuman"));
    push(newNode("Sate Ayam", "Daging"));
    push(newNode("Coca Cola", "Minuman"));
    push(newNode("Gulai Kambing", "Daging"));
    push(newNode("Sate Kambing", "Daging"));
    push(newNode("Opor Ayam", "Daging"));
    push(newNode("Sate Kambing", "Daging"));
    push(newNode("Sate Kambing", "Daging"));
    printAll();
    return 0;
}
//
//
//Output:
//[ 0] : NULL
//[ 1] : NULL
//[ 2] : NULL
//[ 3] : NULL
//[ 4] : NULL
//[ 5] : NULL
//[ 6] : Coca Cola  (2  ) -> NULL
//[ 7] : NULL
//[ 8] : NULL
//[ 9] : Sate Ayam  (4  ) -> Gulai Kambing (2  ) -> NULL
//[10] : Kangkung   (1  ) -> NULL
//[11] : NULL
//[12] : NULL
//[13] : NULL
//[14] : NULL
//[15] : NULL
//[16] : NULL
//[17] : NULL
//[18] : NULL
//[19] : NULL
//[20] : NULL
//[21] : NULL
//[22] : NULL
//[23] : NULL
//[24] : Sate Kambing (3  ) -> NULL
//[25] : NULL
//[26] : NULL
//[27] : NULL
//[28] : Opor Ayam  (1  ) -> NULL

