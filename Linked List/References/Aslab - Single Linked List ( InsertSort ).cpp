#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char name[100];
	int age;
	char nim[100];
	struct Node *next;
};

Node *head = NULL, *tail = NULL; //initialized head and tail kosong

Node *createNode(const char* name, int age, const char* nim){ //untuk bikin Node baru
	Node *new_node = (Node*)malloc(sizeof(Node));
	strcpy(new_node->name, name);
	new_node->age = age;
	strcpy(new_node->nim, nim);
	new_node->next = NULL;
	return new_node;
}

void pushHead(const char* name, int age, const char* nim){ //nambahin ke depannya
	Node *new_node = createNode(name, age, nim);
	
	if (head == NULL){				//kalau headnya kosong, berarti new_node merupakan head dan tail
		head = tail = new_node;
	} else {
		new_node->next = head;		//kalau headnya ada, new_node akan pindah ke sebelum head
		head = new_node;			//new_node berubah jadi head yg baru
	}
}

void pushTail(const char* name, int age, const char* nim){
	Node *new_node = createNode(name, age, nim);
	
	if (head == NULL){
		head = tail = new_node;
	} else {
		tail->next = new_node; 		//setelah tail, ada data baru
		tail = new_node;			//data baru jadi tail
	}
}

void pushMid(const char* name, int age, const char* nim){
	Node *new_node = createNode(name, age, nim);
	
	if (head == NULL){
		head = tail = new_node;
	} else if (strcmp(name, head->name) < 0){	//kalau namanya lebih kecil dari head
		pushHead(name, age, nim);				//new_node jadi head
	} else if (strcmp(name, tail->name) >= 0){	//kalau namanya sama atau lebih besar dari tail
		pushTail(name, age, nim);				//new_node jadi tail
	} else {
		Node *current = head;
		while (current->next != NULL && strcmp(name, current->next->name) >= 0){
			current = current->next;
		}
		//masukin ditengah-tengah current dan current->next
		new_node->next = current->next;
		current->next = new_node;
	}
}

void printAll(){
	Node *current = head;
	
	while (current != NULL){		//selama current belum NULL, dia akan ngeprint masing-masing isinya
		printf("Name	: %s\n", current->name);
		printf("Age	: %d\n", current->age);
		printf("NIM	: %s\n", current->nim);
		printf("===========================\n");
		current = current->next;	//selama masih ada, dia akan iterasi terus menerus sampai datanya habis
	}
}

Node *searching(const char* nim){	//searching harus yg bener2 unik, jadinya parameternya pakai nim
	Node *current =  head;
	
	while (current != NULL && strcmp(nim, current->nim) != 0){	//selama currentnya belum NULL dan selama nim yg dicari belum sama kayak current-nim
		current = current->next;								//maka akan berjalan terus sampai nim-nya ketemu
	}
	return current;	//kalau udh ketemu, maka return current
}

void popHead(){
	if (head == NULL){			//kalau data gaada samsek
		puts("Data is empty.");	//print ini
		return;				
	} else if(head == tail){	//kalau data cuma satu
		free(head);				//free ini kebalikan dari malloc, jd dia melepas memory yg jd pointer head
		head = tail = NULL;		//jadi head & tail kosong
	} else {
		Node *temp = head;		//temp ini anggapannya adalah Node yg mau dihapus
		head =  head->next;		//pindahin head ke sebelahnya
		free(temp);				//free tempnya buat hapus headnya
		temp = NULL;			//tempnya jadi kosong
	}
	
}

void popTail(){					//ketika datanya kosong
	if(head == NULL){
		puts("Data is empty.");
		return;
	} else if (head == tail){	//ketika datanya cuma satu
		free(head);
		head = tail = NULL;
	} else {
		Node *current = head;	
		while (current->next != tail){	//ketika current->next belum sama dengan tail maka dia akan looping trs
			current = current->next;	//dia akan berhenti tepat satu sblm si tail
		}
		tail = current;			//set current jadi tail
		free(current->next);	//free current->next
		current->next = NULL;	//current-next jd kosong
	}
}

void popMid(const char* nim){	//patokannya nimnya karena harus unik
	if (head == NULL){
		puts("Data is empty.");
		return;
	} else if(strcmp(nim, head->nim) == 0){
		popHead();
	} else if(strcmp(nim, tail->nim) == 0){
		popTail();
	} else {
		Node *current = head;
		while (current != NULL && strcmp(nim, current->nim) != 0){	//selama current belum sama dengan NULL dan selama nim yg dicari belum sama dengan current->next
			current = current->next;											//maka looping trs
		}
		printf("\n\n\n[%s]\n\n\n", current->name);
		if (current->next == NULL){ //kalau ternyata datanya gaada
			puts("Not Found!");		//print ini
			return;
		} else {
			Node* temp = current->next;	//declare dulu temp itu sama dengan current->next
			current->next = temp->next;	//sambung current->next sama temp->next
			free(temp);					//hapus temp
			temp = NULL;				//temp jadi kosong
			
		}
	}
}

int main(){
	pushMid("Asha", 19, "123123");
	pushMid("Alia", 19, "321321");
	pushMid("Aya", 19, "456456");
	pushMid("Jasmine", 19, "654654");
	pushMid("Revina", 19, "789789");
	pushMid("Syifa", 19, "987987");
	pushMid("Amel", 19, "890890");
	
	puts("Before");
	puts("===========================");
	printAll();
	
	puts("");
	
	Node *to_find = searching("123123");
	
	if(to_find != NULL){
		printf("Data found\n");
		printf("Name	: %s\n", to_find->name);
		printf("Age	: %d\n", to_find->age);
	} else {
		puts("Not found.");
	}
	
	puts("");
	
	popHead();
	popTail();
	popMid("654654");
	puts("After");
	puts("===========================");
	printAll();
	return 0;
}
