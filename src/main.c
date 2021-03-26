#include <stdio.h>
#include <string.h>
#include "console/console_config.h"
#include "granja/granja.h"
#include "fixStdin.h"

#define MAX_BUFFER_SIZE 10



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

        if (!strcmp(input_buffer, "q")) {
            printf("Finalizando programa...\n");
            break;
        }
        else if (!strcmp(input_buffer, "1")) {
            // Menú granja
            // TODO - Implementar Granja
            menuGranja();

        } else if (!strcmp(input_buffer, "2")) {
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


