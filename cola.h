#ifndef COLA_H
#define COLA_H

#include <stdbool.h>

// Definición de la estructura de nodo de la cola
typedef struct NodoCola {
    int dato;
    struct NodoCola* siguiente;
} NodoCola;

// Definición de la estructura de la cola
typedef struct Cola {
    NodoCola* frente;
    NodoCola* final;
} Cola;

// Prototipos de funciones
Cola* crearCola();
void encolar(Cola* cola, int valor);
int desencolar(Cola* cola);
int frente(Cola* cola);
bool estaVacia(Cola* cola);
void destruirCola(Cola* cola);

#endif // COLA_H