#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>    // Necesaria para configuración regional en sistemas UNIX.

//Estructura para almacenar los datos de cada desecho electrónico.
struct Desecho {
    char nombre[50];          // Almacena el nómbre de cada desecho.
    char categoria[20];      // Clacificación: reciclable, peligroso, no reciclable.
    int piezas;             // Cantidad de unidades del desecho.
};

// Función para leer cadenas de texto de forma segura.
void leerCadena(char* buffer, int tamaño) {
    fgets(buffer, tamaño, stdin);                // Lee la entrada del usuario.
    buffer[strcspn(buffer, "\n")] = '\0';       // Elimina el salto de línea final.
}

int main() {
    // ========= CONFIGURACIÓN INICIAL =========
    #ifdef _WIN32
        system("chcp 65001 > nul");            // Habilita UTF-8 en Windows
    #else
        setlocale(LC_ALL, "en_US.UTF-8");      // Configuración regional para UTF-8 en Mac OS, Linux y Solaris.
    #endif

    // ========= DATOS DEL ESTUDIANTE =========
    printf("Nombre: Orlando Antonio Maturano Pizaña\n");
    printf("Matrícula: ES251107915\n");
    printf("Grupo: DS-DFPR-2501-B1-013\n\n");

    // ========= VARIABLES GLOBALES =========
    struct Desecho *registros = NULL;  // Función dinámica para registros indefinidos.
    int total = 0;                     // Contador de desechos registrados.
    int opcion;                        // Almacena la opción seleccionada del menú principal.
    char respuesta[10];                // Buffer para respuestas de Si/No.

    // ========= BUCLE PRINCIPAL ========= 
    do {
        // ----- Menú de opciones -----
        printf("\n=== MENÚ PRINCIPAL ===\n");
        printf("1. Registrar desecho\n");
        printf("2. Imprimir boleta\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");

        leerCadena(respuesta, 10);   // Lee la opción como cadena.
        opcion = atoi(respuesta);    // Convierte a número.
    
        // ----- Manejo de opciones -----
        switch(opcion) {
            // ========= REGISTRO DE DESECHOS =========
            case 1:
                do {
                    // Redimencionar memoria para nuevo registro
                    struct Desecho *temp = realloc(registros, (total + 1) * sizeof(struct Desecho));
                    if (!temp) {
                        printf("\nError: Memoria insuficiente\n");
                        free(registros);
                        exit(1);
                    }
                    registros = temp;
                    
                    printf("\n=== REGISTRO ===\n");

                    // Captura del nombre:
                    printf("Nombre del desecho: ");
                    leerCadena(registros[total].nombre, 50);
                    
                    // Captura de categoría:
                    printf("Categoría (reciclable/peligroso/no reciclable): ");
                    leerCadena(registros[total].categoria, 20);

                    // Captura de cantidad de piezas:
                    printf("Número de piezas: ");
                    leerCadena(respuesta, 10);
                    registros[total].piezas = atoi(respuesta);

                    total++;  // Incrementa el contador de registros.
                    printf("\nDesecho registrado.\n");

                    // Pregunta para nuevo registro:
                    printf("\n¿Agregar otro? ((S)i/(N)o): ");
                    leerCadena(respuesta, 10);
                } while(respuesta[0] == 'S' || respuesta[0] == 's');  // Repite si la respuesta es afirmativa.
                break;
        
            // ========= IMPRESIÓN DE BOLETA =========
            case 2:
                printf("\n=== BOLETA DE INFORMACIÓN\n");
                for(int i = 0; i < total; i++) {   // Recorre todos los registros.
                    printf("\nDesecho %d:\n", i+1);
                    printf("Nombre: %s\n", registros[i].nombre);
                    printf("Categoría: %s\n", registros[i].categoria);
                    printf("Piezas: %d\n", registros[i].piezas);
                }
                break;

            // ========= SALIR DEL PROGRAMA =========
            case 3:
                printf("\nSaliendo del sistema...\n");
        }
    } while(opcion != 3);

    // ========= LIMPIEZA FINAL =========
    free(registros); // Para liberar memoria asignada dinámicamente.
    return 0;
}

