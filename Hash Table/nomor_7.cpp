#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int tableSize = 7;

struct storage{
    char name[25];
    char category[20];
};

struct storage hashTable[tableSize];

void init(){
    for(int i=0; i<tableSize; i++){
        strcpy(hashTable[i].name,"");
        strcpy(hashTable[i].category,"");
    }
}

int generateKey(const char *name){
    int key;
    key = name[0] - 'A';
    return key % tableSize;
}

int linearProbing(int key){
	int originalKey = key;
	
	do {
		if (strlen(hashTable[key].name) == 0 && strlen(hashTable[key].category) == 0) 
			return key;
		key = (key + 1) % tableSize;
	} while (originalKey != key);
	
	key = -1;
	
    return key;
}

void insert(const char *name, const char *category){
    int index = linearProbing(generateKey(name));
    
    if (index == -1) {
    	puts("The hashTable is full!");
    	return;
	}
	
	storage newStorage;
	strcpy(newStorage.name, name);
	strcpy(newStorage.category, category);
	
	hashTable[index] = newStorage;
}

void printAll(){
    for(int i=0; i<tableSize; i++){
        printf("[%2d] : ", i);
        if(strcmp(hashTable[i].name,"") != 0){
            printf("%s", hashTable[i].name);
        }else{
            printf("NULL");
        }
        printf("\n");
    }
}

int main(){
    init();
    insert("Sate Ayam", "Daging");
    insert("Gulai Kambing", "Daging");
    insert("Kangkung", "Sayuran");
    insert("Coca Cola", "Minuman");
    insert("Opor Ayam", "Daging");
    insert("Sprite", "Minuman");
    insert("Fanta", "Minuman");
    insert("Ayam Kalasan", "Daging");
    printAll();
    return 0;
}

//The hashTable is full! 
//[ 0] : Opor Ayam
//[ 1] : Sprite
//[ 2] : Coca Cola
//[ 3] : Kangkung
//[ 4] : Sate Ayam
//[ 5] : Sate Kambing
//[ 6] : Gulai Kambing

