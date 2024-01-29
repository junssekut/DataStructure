#include <stdio.h>
#include <stdlib.h>

struct QNode {
	int value;
	QNode* next;
};

struct Queue {
	QNode* front;
	QNode* rear;
};

QNode* createNode(int value) {
	QNode* newNode = (QNode*) malloc(sizeof(QNode));
	
	newNode->value = value;
	newNode->next = NULL;
	
	return newNode;
}

Queue* createQueue() {
	Queue* newQueue = (Queue*) malloc(sizeof(Queue));
	
	newQueue->front = newQueue->rear = NULL;
	
	return newQueue;
}

void enQueue(Queue** queue, int value) {
	QNode* newNode = createNode(value);
	
	if ((*queue)->front == NULL) {
		(*queue)->front = (*queue)->rear = newNode;
	} else {
		(*queue)->rear->next = newNode;
		(*queue)->rear = newNode;
	}
}

void deQueue(Queue** queue) {
	if ((*queue)->front == NULL) return;
	
	QNode* temp = (*queue)->front;
	
	(*queue)->front = (*queue)->front->next;
	
	if ((*queue)->front == NULL) (*queue)->rear = NULL;
	
	free(temp);
}

int front(Queue* queue) {
	if (queue->front == NULL) return NULL;
	
	return queue->front->value;
}

int rear(Queue* queue) {
	if (queue->front == NULL) return NULL;
	
	return queue->rear->value;
}

int main() {
	Queue* q = createQueue();
	
	enQueue(&q, 40);
	enQueue(&q, 3);
	enQueue(&q, 20);
	enQueue(&q, 10);
	
	printf("%d\n", front(q));
	printf("%d\n\n", rear(q));
	
	deQueue(&q);
	
	printf("%d\n", front(q));
	printf("%d\n\n", rear(q));
	
	deQueue(&q);
	
	printf("%d\n", front(q));
	printf("%d\n\n", rear(q));
	
	return 0;
}
