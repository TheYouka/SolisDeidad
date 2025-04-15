#ifndef PILA_H
#define PILA_H

#include <stdbool.h>

// Definición de la estructura de nodo
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
} Nodo;

// Definición de la estructura de la pila
typedef struct Pila {
    Nodo* cima;
} Pila;

// Prototipos de funciones
Pila* crearPila();
void push(Pila* pila, int valor);
int pop(Pila* pila);
int top(Pila* pila);
int empty(Pila* pila);
void destruirPila(Pila* pila);

#endif // PILA_H