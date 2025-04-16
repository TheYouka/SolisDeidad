#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

// Tamaño del HashMap
#define HASH_MAP_SIZE 100

// Estructura de un nodo en el HashMap
typedef struct HashNode {
    char *key;                // Clave
    char *value;              // Valor
    struct HashNode *next;    // Puntero al siguiente nodo (en caso de colisión)
} HashNode;

// Estructura del HashMap
typedef struct HashMap {
    HashNode *buckets[HASH_MAP_SIZE]; // Arreglo de buckets
} HashMap;

// Prototipos de funciones
unsigned int hashFunction(const char *key);
HashMap *hashCreate();
void hashInsert(HashMap *map, const char *key, const char *value);
char *hashSearch(HashMap *map, const char *key);
void hashFree(HashMap *map);

#endif // HASHMAP_H