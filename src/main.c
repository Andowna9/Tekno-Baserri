#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include "console/console_config.h"

#define MAX_BUFFER_SIZE 10

// Declaración de funciones

// Llamar cuando estemos seguros de que una limpieza de stdin es necesaria (si no puede pausar la ejecución esperando input)

void clear_stdin();

// Elimina el caracter de nueva línea de un buffer de caracteres (string)

void clean_buffer(char* buffer);

int main() {

    // Configuración de consola con colores + UTF-8

    setup_console();

    // Buffer de lectura por defecto

     char input_buffer [MAX_BUFFER_SIZE];

    // Bucle hasta que se presione tecla de salida

    while(1) {

        printf_c(DARK_CYAN_TXT, "-------Tekno Baserri-------\n"); // Ejemplo de salida de texto con color

        printf("1. Gestionar granja\n");

        printf("2. Acceder a parking\n");

        printf("Presiona 'q' para salir\n");

        printf("Input: ");

        // Lectura de stdin y limpieza de input_buffer (Posible modularización (1 función vs 2 funciones) si se repiten mucho!)

        fgets(input_buffer, MAX_BUFFER_SIZE, stdin);

        clean_buffer(input_buffer);

        // FLUJO DEPENDIENDO DE LA OPCIÓN
        // Nota: 'strcmp' devuelve 0 si 2 strings son iguales

        // Fin del programa

        if (strcmp(input_buffer, "q") == 0) {

            printf("Finalizando programa...\n");

            break;
        }

        // Menú granja

        else if (strcmp(input_buffer, "1") == 0) {

            // TODO - Implementar Granja

            printf("[ GRANJA ]\n");

        }

        // Menú parking

        else if (strcmp(input_buffer, "2") == 0) {

            // TODO - Implementar Parking

            printf("[ PARKING ]\n");

        }

        else {

            printf("Opción no reconocida!\n");
        }


    }

    // TODO - Desalojar memoria dinámica si la hay


    // Restauración de configuración de consola (se revocan los cambios)

    restore_console();

    return 0;
}

// Definición de funciones

void clear_stdin() {

    char c;

    while((c = getchar()) != '\n'); // Se eliminan caracteres hasta alcanzar el salto de línea
}

void clean_buffer(char* buffer) {

    // Buscamos el salto de línea en la penúltima posición (la última es '\0')

    int pos = strlen(buffer) - 1;

    if (buffer[pos] == '\n') {

        // Si existe, se reemplaza por el caracter final

        buffer[pos] = '\0';
    }

    // Ha habido un overflow, ya que no se ha incluido el salto de línea y es necesaria una limpieza

    else {

        clear_stdin();
    }
}
