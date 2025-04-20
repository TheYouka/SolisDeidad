#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHMAP_SIZE 128

typedef struct HashNode {
    char *key;
    void *value;
    struct HashNode *next;
} HashNode;

typedef struct HashMap {
    HashNode *buckets[HASHMAP_SIZE];
} HashMap;

// Hash function
unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % HASHMAP_SIZE;
}

// Initialize the hashmap
void hashmap_init(HashMap *map) {
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        map->buckets[i] = NULL;
    }
}

// Insert a key-value pair into the hashmap
void hashmap_put(HashMap *map, const char *key, void *value) {
    unsigned int index = hash(key);
    HashNode *node = map->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value; // Update value if key exists
            return;
        }
        node = node->next;
    }

    // Create a new node
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

// Retrieve a value by key from the hashmap
void *hashmap_get(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    HashNode *node = map->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL; // Key not found
}

// Remove a key-value pair from the hashmap
void hashmap_remove(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    HashNode *node = map->buckets[index];
    HashNode *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                map->buckets[index] = node->next;
            }
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

// Free all memory used by the hashmap
void hashmap_free(HashMap *map) {
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        HashNode *node = map->buckets[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
}

// Example usage
int mainXD() {
    HashMap map;
    hashmap_init(&map);

    // Insert some key-value pairs
    int value1 = 42;
    hashmap_put(&map, "key1", &value1);

    int value2 = 84;
    hashmap_put(&map, "key2", &value2);

    // Retrieve values
    int *retrieved_value1 = (int *)hashmap_get(&map, "key1");
    if (retrieved_value1) {
        printf("Retrieved value for key1: %d\n", *retrieved_value1);
    } else {
        printf("Key not found: key1\n");
    }

    // Remove a key-value pair
    hashmap_remove(&map, "key1");

    // Try to retrieve the removed key
    retrieved_value1 = (int *)hashmap_get(&map, "key1");
    if (retrieved_value1) {
        printf("Retrieved value for key1: %d\n", *retrieved_value1);
    } else {
        printf("Key not found: key1\n");
    }

    // Free the hashmap
    hashmap_free(&map);

    return 0;
}