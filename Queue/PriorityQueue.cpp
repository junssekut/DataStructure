#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Patient {
	char name[16];
	int age;
	int priority;
};

struct Node {
	Patient value;
	Node* next;
};

struct Queue {
	Node* front;
	Node* rear;
};

Patient createPatient(const char *name, int age, const char* priority) {
	Patient patient;
	
	strcpy(patient.name, name);
	patient.age = age;
	
	switch (priority[0]) {
		case 'l':
			patient.priority = 3;
			break;
		case 'm':
			patient.priority = 2;
			break;
		case 'h':
			patient.priority = 1;
			break;
	}
	
	return patient;
}

Patient createPatient() {
	Patient patient;
	
	do {
		printf("Input patient name [1 - 15 characters]: ");
		scanf("%[^\n]", patient.name);
		fflush(stdin);
		
		int length = strlen(patient.name);
		if (length >= 1 && length <= 15) break;
	} while (1);
	
	do {
		printf("Input patient age [more than 0]: ");
		scanf("%d", &patient.age);
		fflush(stdin);
		
		if (patient.age > 0) break;
	} while (1);
	
	do {
		char priorityBuffer[5];
		printf("Input patient priority [LOW|MID|HIGH]: ");
		scanf("%s", priorityBuffer);
		
		if (strcmp(priorityBuffer, "LOW") == 0) {
			patient.priority = 3;
			break;
		}
		
		if (strcmp(priorityBuffer, "MID") == 0) {
			patient.priority = 2;
			break;
		}
		
		if (strcmp(priorityBuffer, "HIGH") == 0) {
			patient.priority = 1;
			break;
		}
	} while (1);
	
	return patient;
}

Node* createNode(Patient patient) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	
	newNode->value = patient;
	newNode->next = NULL;
	
	return newNode;
}

Queue* createQueue() {
	Queue* newQueue = (Queue*) malloc(sizeof(Queue));
	
	newQueue->front = newQueue->rear = NULL;
	
	return newQueue;
}

int enqueue(Queue** queue, Patient patient) {
	Node* newNode = createNode(patient);
	
	if ((*queue)->front == NULL) {
		(*queue)->front = (*queue)->rear = newNode;
		return 2;
	} 
	
	if ((*queue)->front->value.priority > patient.priority) {
		newNode->next = (*queue)->front;
		(*queue)->front = newNode;	
		return 3;
	}
	
	if ((*queue)->rear->value.priority <= patient.priority) {
		(*queue)->rear->next = newNode;
		(*queue)->rear = newNode;
		return 4;
	}

	Node* ptr = (*queue)->front;
	while (ptr->next != NULL && ptr->next->value.priority < patient.priority) {
		ptr = ptr->next;
	}
	
	newNode->next = ptr->next;
	ptr->next = newNode;
	
	return 1;
}

int dequeue(Queue** queue) {
	if ((*queue)->front == NULL) {
		(*queue)->front = (*queue)->rear = NULL;
		return 2;
	}
	
	Node* tempNode = (*queue)->front;
	(*queue)->front = (*queue)->front->next;
	free(tempNode);
	tempNode = NULL;
	
	if ((*queue)->front == NULL) (*queue)->rear = NULL;
	
	return 1;
}

void display(Queue* queue) {
	if (queue->front == NULL) {
		puts("Failed to display queue because patient queue is empty.");
		return;
	}
	
	Node* ptr = queue->front;
	while (ptr != NULL) {
		printf("Nama: %s, Umur: %d, Status: %d\n", ptr->value.name, ptr->value.age, ptr->value.priority);
		ptr = ptr->next;
	}
}

int main() {
	Queue* q = createQueue();
	
	enqueue(&q, createPatient("Rizki", 33, "low"));
	enqueue(&q, createPatient("Richard", 26, "low"));
	enqueue(&q, createPatient("Andi", 16, "high"));
	enqueue(&q, createPatient("Nur", 74, "mid"));
	enqueue(&q, createPatient("Coki", 66, "low"));
	
	puts("Linked List after entering data:");
	display(q);
	
	dequeue(&q);
	dequeue(&q);
	dequeue(&q);
	
	puts("\nLinked List after dequeue data:");
	display(q);
		
	return 0;
}
