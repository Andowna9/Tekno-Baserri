#include <stdio.h>
#include <string.h>
#include "console/console_config.h"

#define MAX_BUFFER_SIZE 10

// Declaración de funciones

void clear_stdin(); // Llamar cuando estemos seguros de que una limpieza de stdin es necesaria (si no puede pausar la ejecución esperando input)
void clean_buffer(char* buffer); // Elimina el caracter de nueva línea de un buffer de caracteres (string)

int main() {
    setup_console(); // Configuración de consola con colores + UTF-8
    char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto

    while(1) {

        printf_c(DARK_CYAN_TXT, "-------Tekno Baserri-------\n"); // Ejemplo de salida de texto con color
        printf("1. Gestionar granja\n");
        printf("2. Acceder a parking\n");
        printf("Presiona 'q' para salir\n");
        printf("Input: ");

        fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
        clean_buffer(input_buffer);

        if (strcmp(input_buffer, "q") == 0) {
            printf("Finalizando programa...\n");
            break;
        }
        else if (strcmp(input_buffer, "1") == 0) {
            // Menú granja
            // TODO - Implementar Granja
            printf("[ GRANJA ]\n");

        } else if (strcmp(input_buffer, "2") == 0) {
            // Menú parking
            // TODO - Implementar Parking
            printf("[ PARKING ]\n");

        }

        else { printf("Opción no reconocida!\n"); }


    }

    // TODO - Desalojar memoria dinámica si la hay

    restore_console(); // Restauración de configuración de consola (se revocan los cambios)

    return 0;
}

// Definición de funciones

void clear_stdin() {
    char c;
    while((c = getchar()) != '\n'); // Se eliminan caracteres hasta alcanzar el salto de línea
}

void clean_buffer(char* buffer) {

    int pos = strlen(buffer) - 1; // Buscamos el salto de línea en la penúltima posición (la última es '\0')
    if (buffer[pos] == '\n') {
        buffer[pos] = '\0'; // Si existe, se reemplaza por el caracter final
    }

    else {
        clear_stdin(); // Ha habido un overflow, ya que no se ha incluido el salto de línea y es necesaria una limpieza
    }
}
