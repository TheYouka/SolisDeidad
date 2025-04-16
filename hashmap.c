#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_MAP_SIZE 100

typedef struct HashNode {
    char *key;
    char *value;
    struct HashNode *next;
} HashNode;

typedef struct HashMap {
    HashNode *buckets[HASH_MAP_SIZE];
} HashMap;

unsigned int hashFunction(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % HASH_MAP_SIZE;
}

HashMap *hashCreate() {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (!map) {
        perror("Failed to create hash map");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        map->buckets[i] = NULL;
    }
    return map;
}

void hashInsert(HashMap *map, const char *key, const char *value) {
    unsigned int index = hashFunction(key);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    if (!newNode) {
        perror("Failed to insert into hash map");
        exit(EXIT_FAILURE);
    }
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = map->buckets[index];
    map->buckets[index] = newNode;
}

char *hashSearch(HashMap *map, const char *key) {
    unsigned int index = hashFunction(key);
    HashNode *current = map->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void hashFree(HashMap *map) {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashNode *current = map->buckets[i];
        while (current) {
            HashNode *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(map);
}

int main() {
    
    return 0;
}