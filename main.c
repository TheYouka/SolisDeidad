#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Para GetCurrentDirectory
//#include "hashmap.h"
#include "pila.h" // Para la pila
#include "cola.h" // Para la cola
// Importa utils.h
//#include "utils.h"

#define MAX_NODOS 100
#define MAX_TAXIS 26
#define MAP_SIZE 40
#define MAX_PATH 260

// Strcut para los taxis
typedef struct {
    int id_taxi;
    int x;
    int y;
    int estado; // 0: libre, 1: ocupado
} Taxi;

// Struct para las solicitudes
typedef struct {
    int id; // ID del nodo donde se hizo la llamada 
    int x; // Coordenada x de destino
    int y; // Coordenada y de destino
} Solicitud;

typedef struct {
    int x; // Coordenada x del nodo
    int y; // Coordenada y del nodo
}Coord;

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

// imprimir mapa 
void imprimir_mapa(char mapa[MAP_SIZE][MAP_SIZE]) {
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
};

void cargar_nodos(char mapa[MAP_SIZE][MAP_SIZE], const char *filename, Coord nodos[MAX_NODOS]) {
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
                mapa[x][y] = 'o'; // Asigna el nodo al mapa
                if (id >= 0 && id < MAX_NODOS) {
                    nodos[id].x = x; // Actualiza la coordenada x del nodo
                    nodos[id].y = y; // Actualiza la coordenada y del nodo
                } else {
                    printf("ID fuera de rango: %d\n", id);
                }
            } else {
                printf("Coordenadas fuera de rango: %d %d\n", x, y);
            }
        } else {
            printf("Error al leer la línea: %s\n", line);
        }
    }

    fclose(file);
}


// Añadir taxis al mapa
void agregar_taxi(Taxi taxi[MAP_SIZE][MAP_SIZE], char mapa[MAP_SIZE][MAP_SIZE]) {
    int id_taxi, x, y;
    char opcion;

    do {
        printf("Ingrese el ID del taxi: ");
        scanf("%d", &id_taxi);
        printf("Ingrese la coordenada X del taxi: ");
        scanf("%d", &x);
        printf("Ingrese la coordenada Y del taxi: ");
        scanf("%d", &y);

        // Verifica que las coordenadas estén dentro del rango del mapa
        if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
            // Comprueba que exista un nodo calle en esa coordenada
            if (mapa[x][y] == 'o') {
                taxi[x][y].id_taxi = id_taxi; // Asigna el id del taxi
                taxi[x][y].x = x; // Asigna la coordenada x
                taxi[x][y].y = y; // Asigna la coordenada y
                taxi[x][y].estado = 0; // Inicializa el estado como libre
                mapa[x][y] = 'x'; // Marca la posición en el mapa con 'x' indicando un taxi
                printf("Taxi agregado correctamente.\n");
            } else {
                printf("No existe un nodo calle en las coordenadas: %d %d\n", x, y);
            }
        } else {
            printf("Coordenadas fuera de rango: %d %d\n", x, y);
        }

        printf("¿Desea agregar otro taxi? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');
}

// funcion que cargue los taxis
void cargar_taxis(Taxi taxi[MAP_SIZE][MAP_SIZE], char mapa[MAP_SIZE][MAP_SIZE], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo taxis.txt");
        return;
    }

    char line[100]; // Buffer para leer líneas completas
    int id_taxi, x, y;

    // lee con fgets() para evitar problemas con espacios en blanco
    while (fgets(line, sizeof(line), file)) {
        // Lee id_taxi, x y y de la línea
        if (sscanf(line, "%d,%d,%d", &id_taxi, &x, &y) == 3) {
            // Verifica que las coordenadas estén dentro del rango del mapa
            if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                // Comprueba que exista un nodo calle en esa coordenada
                if (mapa[x][y] == 'o') {
                    taxi[x][y].id_taxi = id_taxi; // Asigna el id del taxi
                    taxi[x][y].x = x; // Asigna la coordenada x
                    taxi[x][y].y = y; // Asigna la coordenada y
                    taxi[x][y].estado = 0; // Inicializa el estado como libre
                    mapa[x][y] = 'x'; // Marca la posición en el mapa con 'x' indicando un taxi
                } else {
                    printf("No existe un nodo calle en las coordenadas: %d %d\n", x, y);
                }
            } else {
                printf("Coordenadas fuera de rango: %d %d\n", x, y);
            }
        } else {
            printf("Error al leer la línea: %s\n", line);
        }
    }

    fclose(file);
}

// Cargar calles desde el archivo calles.txt
void cargar_calles(int grafo[MAX_NODOS][MAX_NODOS], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo calles.txt");
        return;
    }

    char line[100]; // Buffer para leer líneas completas
    int id1, id2, peso;

    // lee con fgets() para evitar problemas con espacios en blanco
    while (fgets(line, sizeof(line), file)) {
        // Lee id_calle1, id_calle2 y peso de la línea
        if (sscanf(line, "%d,%d,%d", &id1, &id2, &peso) == 3) {
            // Verifica que los IDs estén dentro del rango permitido
            if (id1 >= 0 && id1 < MAX_NODOS && id2 >= 0 && id2 < MAX_NODOS) {
                grafo[id1][id2] = peso; // Asigna el peso a la matriz de adyacencia
                grafo[id2][id1] = peso; // Si el grafo es no dirigido
            } else {
                printf("IDs fuera de rango: %d %d\n", id1, id2);
            }
        } else {
            printf("Error al leer la línea: %s\n", line);
        }
    }

    fclose(file);
}

// Agregar calles desde consola
void agregar_calle(int grafo[MAX_NODOS][MAX_NODOS], Coord nodos[MAX_NODOS]) {
    int id1, id2, peso;
    char opcion;

    do {
        printf("Ingrese el ID del primer nodo: ");
        scanf("%d", &id1);
        printf("Ingrese el ID del segundo nodo: ");
        scanf("%d", &id2);
        printf("Ingrese el peso de la conexión: ");
        scanf("%d", &peso);

        // Validar que ambos nodos existen en el mapa
        if (id1 >= 0 && id1 < MAX_NODOS && id2 >= 0 && id2 < MAX_NODOS &&
            nodos[id1].x != -1 && nodos[id1].y != -1 &&
            nodos[id2].x != -1 && nodos[id2].y != -1) {
            grafo[id1][id2] = peso; // Agregar conexión
            grafo[id2][id1] = peso; // Grafo no dirigido
            printf("Calle agregada correctamente.\n");
        } else {
            printf("Uno o ambos nodos no existen en el mapa.\n");
        }

        printf("¿Desea agregar otra calle? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');
}


// Cargar solo las solicitudes desde el archivo solicitudes.txt
void cargar_solicitudes(Queue *colaSolicitudes, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo solicitudes.txt");
        return;
    }

    char line[100]; // Buffer para leer líneas completas
    int id, x, y;

    // lee con fgets() para evitar problemas con espacios en blanco
    while (fgets(line, sizeof(line), file)) {
        // Lee id, x y y de la línea
        if (sscanf(line, "%d,%d,%d", &id, &x, &y) == 3) {
            // Crear una nueva solicitud
            Solicitud *solicitud = (Solicitud *)malloc(sizeof(Solicitud));
            if (!solicitud) {
                perror("Error al asignar memoria para la solicitud");
                fclose(file);
                return;
            }
            solicitud->id = id;
            solicitud->x = x;
            solicitud->y = y;

            // Encolar la solicitud
            queuePush(colaSolicitudes, solicitud);
        } else {
            printf("Error al leer la línea: %s\n", line);
        }
    }

    fclose(file);
}


// Funcipon para agregar nodos al mapa
void agregar_nodos(char mapa[MAP_SIZE][MAP_SIZE]) {
    
    int id, x, y;
    char opcion;
    do {
        printf("Ingrese el ID del nodo: ");
        scanf("%d", &id);
        printf("Ingrese la coordenada X del nodo: ");
        scanf("%d", &x);
        printf("Ingrese la coordenada Y del nodo: ");
        scanf("%d", &y);

        // Verifica que las coordenadas estén dentro del rango del mapa
        if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
            mapa[x][y] = 'o'; // Asigna el nodo al mapa
            printf("Nodo agregado correctamente.\n");
        } else {
            printf("Coordenadas fuera de rango: %d %d\n", x, y);
        }

        printf("¿Desea agregar otro nodo? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');
};


// Agregar solicitudes desde consola
void agregar_solicitud(Queue *colaSolicitudes, Coord nodos[MAX_NODOS]) {
    int id, destino_x, destino_y;
    char opcion;

    do {
        printf("Ingrese el ID del nodo donde se hace el pedido: ");
        scanf("%d", &id);

        // Validar que el nodo exista
        if (id >= 0 && id < MAX_NODOS && nodos[id].x != -1 && nodos[id].y != -1) {
            printf("Ingrese la coordenada X del destino: ");
            scanf("%d", &destino_x);
            printf("Ingrese la coordenada Y del destino: ");
            scanf("%d", &destino_y);

            // Validar que las coordenadas del destino estén dentro del rango del mapa
            if (destino_x >= 0 && destino_x < MAP_SIZE && destino_y >= 0 && destino_y < MAP_SIZE) {
                // Crear una nueva solicitud
                Solicitud *solicitud = (Solicitud *)malloc(sizeof(Solicitud));
                if (!solicitud) {
                    perror("Error al asignar memoria para la solicitud");
                    return;
                }
                solicitud->id = id;
                solicitud->x = destino_x;
                solicitud->y = destino_y;

                // Encolar la solicitud
                queuePush(colaSolicitudes, solicitud);
                printf("Solicitud agregada correctamente.\n");
            } else {
                printf("Coordenadas del destino fuera de rango: %d %d\n", destino_x, destino_y);
            }
        } else {
            printf("El nodo con ID %d no existe.\n", id);
        }

        printf("¿Desea agregar otra solicitud? (s/n): ");
        scanf(" %c", &opcion);
    } while (opcion == 's' || opcion == 'S');
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

    // Crear un arreglo para los nodos que guarde un struct con sus coordenadas en base a su id
    Coord nodos[MAX_NODOS];
    for (int i = 0; i < MAX_NODOS; i++) {
        nodos[i].x = -1; // Inicializar con -1 (sin nodo)
        nodos[i].y = -1;
    }


    // Cargar nodos desde el archivo nodos.txt
    cargar_nodos(mapa, "c:\\Users\\the_y\\Documents\\SolisDeidad\\nodos.txt",nodos);
   
    // Crear matriz de adyacencia para el grafo
    int grafo[MAX_NODOS][MAX_NODOS];
    for (int i = 0; i < MAX_NODOS; i++) {
        for (int j = 0; j < MAX_NODOS; j++) {
            grafo[i][j] = 0; // Inicializar con 0 (sin conexión)
        }
    }
    
    // Cargar calles desde el archivo calles.txt
    FILE *file = fopen("c:\\Users\\the_y\\Documents\\SolisDeidad\\calles.txt", "r");
    cargar_calles(grafo, "c:\\Users\\the_y\\Documents\\SolisDeidad\\calles.txt");

    //imprimir_mapa(mapa); // Imprimir el mapa después de cargar los nodos

    // Crea matriz que dado una coordenada x,y devuelve el id del taxi
    Taxi taxi[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            taxi[i][j].id_taxi = -1; // Inicializar con -1 (sin taxi)
            taxi[i][j].x = -1;
            taxi[i][j].y = -1;
            taxi[i][j].estado = 0; // Inicializar como libre
        }
    }

    // cargar taxis desde el archivo taxis.txt
    FILE *file_taxis = fopen("c:\\Users\\the_y\\Documents\\SolisDeidad\\taxis.txt", "r");
    cargar_taxis(taxi, mapa,"c:\\Users\\the_y\\Documents\\SolisDeidad\\taxis.txt");

    // Crea una cola para las solicitudes, cada solicitud tiene un id (el id del nodo donde se pidió), coordenadas x,y de destino
    Queue* colaSolicitudes = queueInitialize();

    // Cargar solicitudes desde el archivo solicitudes.txt
    cargar_solicitudes(colaSolicitudes, "c:\\Users\\the_y\\Documents\\SolisDeidad\\solicitudes.txt");


    // Mostrar el menú principal
    int opcion;
    do {
        mostrar_menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregar_nodos(mapa);
                break;
            case 2:
                // Agregar calle (no implementado en este ejemplo)
                agregar_calle(grafo, nodos);
                break;
            case 3:
                imprimir_mapa(mapa);
                break;
            case 4:
                // Agregar taxis (no implementado en este ejemplo)
                agregar_taxi(taxi, mapa);
                break;
            case 5:
                // Agregar solicitudes (no implementado en este ejemplo)
                agregar_solicitud(colaSolicitudes, nodos);
                break;
            case 6:
                // Borrar solicitud (no implementado en este ejemplo)
                // NO IMPLEMENTAR
                break;
            case 7:
                // Ver solicitudes (no implementado en este ejemplo)
                break;
            case 8:
                // Simular (no implementado en este ejemplo)
                break;
            case 9:
                printf("Saliendo del programa...\n");
                Sleep(2000);
                printf("Saliendo del programa, no se desespere.\n");
                Sleep(2000);
                printf("Hasta luego\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 9);


    return 0;
};


