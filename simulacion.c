
#define MAP_SIZE 40

#include <stdio.h>


void simular(char mapa[MAP_SIZE][MAP_SIZE], Taxi taxi[MAP_SIZE][MAP_SIZE],
    Queue *colaSolicitudes, int grafo[MAX_NODOS][MAX_NODOS],
    Coord nodos[MAX_NODOS]) {
    
    int turno = 0;
    while (!queueIsEmpty(colaSolicitudes)) { // La simulación continúa hasta que no haya más solicitudes
        turno++;
        printf("\n=== TURNO %d ===\n", turno);

        // 2. Procesar Solicitud (1 por turno, según el PDF)
        Solicitud *solicitud = (Solicitud *)queuePop(colaSolicitudes);
        if (solicitud) {
        printf("Procesando solicitud en (%d, %d) con destino (%d, %d)\n",
                solicitud->x, solicitud->y, solicitud->destino_x, solicitud->destino_y);

        // 3. Encontrar el Taxi Óptimo (Dijkstra - *A implementar*)
        int id_taxi_optimo = encontrar_taxi_optimo(taxi, solicitud, grafo, nodos);

        if (id_taxi_optimo != -1) { // Si se encontró un taxi
            printf("Taxi %d asignado\n", id_taxi_optimo);

            // 4. Mover Taxi y Atender Solicitud (*A implementar*)
            mover_taxi(taxi, solicitud, mapa);

            // 5. Actualizar Estado del Sistema
            actualizar_estado_sistema(mapa, taxi, solicitud);

            free(solicitud); // Liberar la memoria de la solicitud procesada
        } else {
            printf("No hay taxis disponibles para esta solicitud.\n");
            // Si no hay taxi disponible, podrías volver a encolar la solicitud
            // o manejarla de alguna otra manera (por ejemplo, descartarla después de un tiempo)
            free(solicitud); // Liberar la memoria
        }
        }

        // 6. Visualizar el Estado del Sistema
        imprimir_mapa(mapa);
        imprimir_taxis(taxi);
        //imprimir_cola_solicitudes(colaSolicitudes); // Si es necesario

        #ifdef _WIN32
        Sleep(1000); // Pausa de 1 segundo (1000 milisegundos) en Windows
        #else
        sleep(1);   // Pausa de 1 segundo en sistemas Unix
        #endif
    }
    printf("\n--- SIMULACIÓN COMPLETADA ---\n");
    }