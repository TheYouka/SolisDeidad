#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialize the queue
Queue* queueInitialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Check if the queue is empty
int queueIsEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue an element
void queuePush(Queue* q, void* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

// Dequeue an element
void* queuePop(Queue* q) {
    if (queueIsEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    Node* temp = q->front;
    void* value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

// Get the front element
void* queueFront(Queue* q) {
    if (queueIsEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    return q->front->data;
}

// Free the queue
void queueDestroy(Queue* q) {
    while (!queueIsEmpty(q)) {
        queuePop(q);
    }
    free(q);
}
