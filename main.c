#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Para GetCurrentDirectory
// Importa utils.h
//#include "utils.h"

#define MAX_NODOS 100
#define MAX_TAXIS 26
#define MAP_SIZE 40
#define MAX_PATH 260

void mostrar_menu() {
    printf("\n=== MENÚ PRINCIPAL ===\n");
    printf("1. Agregar nodos al mapa\n");
    printf("2. Agregar calle\n");
    printf("3. Ver mapa\n");
    printf("4. Agregar taxis\n");
    printf("5. Agregar solicitudes\n");
    printf("6. Borrar solicitud\n");
    printf("7. Ver solicitudes\n");
    printf("8. Simular\n");
    printf("9. Salir\n");
    printf("Seleccione una opción: ");
};


void cargar_nodos(char mapa[MAP_SIZE][MAP_SIZE], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo nodos.txt");
        return;
    }

    char line[100]; // Buffer para leer líneas completas
    int id, x, y;

    // lee con fgets() para evitar problemas con espacios en blanco
    while (fgets(line, sizeof(line), file)) {
        // Lee el id, x y y de la línea
        if (sscanf(line, "%d,%d,%d", &id, &x, &y) == 3) {
            // Verifica que las coordenadas estén dentro del rango del mapa
            if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                mapa[x][y] = 'o'; // Asigna el último dígito del número al nodo
            } else {
                printf("Coordenadas fuera de rango: %d %d\n", x, y);
            }
        } else {
            printf("Error al leer la línea: %s\n", line);
        }
    }

    fclose(file);
};



// Función principal de prueba
int main() {
    
    // crea una matriz para el mapa, rellenaro con "."
    char mapa[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            mapa[i][j] = '.';
        }
    };

    // Cargar nodos desde el archivo nodos.txt
    cargar_nodos(mapa, "c:\\Users\\the_y\\Documents\\SolisDeidad\\nodos.txt");
   
    // Crear matriz de adyacencia para el grafo
    int grafo[MAX_NODOS][MAX_NODOS];
    for (int i = 0; i < MAX_NODOS; i++) {
        for (int j = 0; j < MAX_NODOS; j++) {
            grafo[i][j] = 0; // Inicializar con 0 (sin conexión)
        }
    }


    return 0;
};


