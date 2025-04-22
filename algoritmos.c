#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "main.h" // Asegúrate de incluir las definiciones necesarias

#define INF INT_MAX

// Implementación del algoritmo de Dijkstra para encontrar el taxi más cercano
int encontrar_taxi_optimo(Taxi taxi[MAP_SIZE][MAP_SIZE], Solicitud *solicitud,
    int grafo[MAX_NODOS][MAX_NODOS], Coord nodos[MAX_NODOS]) {

    int dist[MAX_NODOS]; // Distancias mínimas desde el nodo de la solicitud
    int visitado[MAX_NODOS] = {0}; // Nodos visitados
    int origen = solicitud->id; // Nodo donde se hizo la solicitud

    // Inicializar distancias
    for (int i = 0; i < MAX_NODOS; i++) {
        dist[i] = INF;
    }
    dist[origen] = 0;

    // Dijkstra
    for (int i = 0; i < MAX_NODOS; i++) {
        int min_dist = INF, u = -1;

        // Encontrar el nodo no visitado con la menor distancia
        for (int j = 0; j < MAX_NODOS; j++) {
            if (!visitado[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // No hay más nodos alcanzables
        visitado[u] = 1;

        // Relajar las aristas del nodo actual
        for (int v = 0; v < MAX_NODOS; v++) {
            if (grafo[u][v] && !visitado[v] && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }

    // Buscar el taxi más cercano
    int taxi_optimo = -1;
    int distancia_minima = INF;

    for (int i = 0; i < MAX_NODOS; i++) {
        if (dist[i] < distancia_minima && nodos[i].x != -1 && nodos[i].y != -1) {
            Taxi *t = &taxi[nodos[i].x][nodos[i].y];
            if (t->id_taxi != -1 && t->estado == 0) { // Taxi libre
                distancia_minima = dist[i];
                taxi_optimo = t->id_taxi;
            }
        }
    }

    return taxi_optimo; // Retorna el ID del taxi más cercano o -1 si no hay taxis disponibles
}

