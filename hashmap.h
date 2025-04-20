#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

// Tamaño del HashMap
#define HASHMAP_SIZE 128

// Definición de la estructura de nodo del HashMap
typedef struct HashNode {
    char *key;                // Clave
    void *value;              // Valor asociado
    struct HashNode *next;    // Puntero al siguiente nodo (en caso de colisión)
} HashNode;

// Definición de la estructura del HashMap
typedef struct HashMap {
    HashNode *buckets[HASHMAP_SIZE]; // Arreglo de buckets
} HashMap;

// Prototipos de funciones
unsigned int hash(const char *key);
void hashmap_init(HashMap *map);
void hashmap_put(HashMap *map, const char *key, void *value);
void *hashmap_get(HashMap *map, const char *key);
void hashmap_remove(HashMap *map, const char *key);
void hashmap_free(HashMap *map);

#endif // HASHMAP_H