#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de nodo
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

// Clase Pila
typedef struct Pila {
    Nodo* cima;
} Pila;

// Constructor de la pila
Pila* crearPila() {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->cima = NULL;
    return pila;
}

// Método push
void push(Pila* pila, int valor) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = pila->cima;
    pila->cima = nuevoNodo;
}

// Método pop
int pop(Pila* pila) {
    if (pila->cima == NULL) {
        printf("Error: la pila está vacía.\n");
        exit(EXIT_FAILURE);
    }
    Nodo* nodoAEliminar = pila->cima;
    int valor = nodoAEliminar->dato;
    pila->cima = nodoAEliminar->siguiente;
    free(nodoAEliminar);
    return valor;
}

// Método top
int top(Pila* pila) {
    if (pila->cima == NULL) {
        printf("Error: la pila está vacía.\n");
        exit(EXIT_FAILURE);
    }
    return pila->cima->dato;
}

// Método empty
int empty(Pila* pila) {
    return pila->cima == NULL;
}

// Destructor de la pila
void destruirPila(Pila* pila) {
    while (!empty(pila)) {
        pop(pila);
    }
    free(pila);
}

