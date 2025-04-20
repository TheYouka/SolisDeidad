#ifndef COLA_H
#define COLA_H

#include <stdbool.h>

// Definición de la estructura de nodo de la cola
typedef struct Node {
    void* data;                // Puntero genérico para almacenar cualquier tipo de dato
    struct Node* next;
} Node;

// Definición de la estructura de la cola
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Prototipos de funciones
Queue* queueInitialize();
int queueIsEmpty(Queue* q);
void queuePush(Queue* q, void* value);
void* queuePop(Queue* q);
void* queueFront(Queue* q);
void queueDestroy(Queue* q);

#endif // COLA_H