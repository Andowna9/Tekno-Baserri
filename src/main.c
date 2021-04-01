#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <stdin_fix.h>
#include "granja/granja.h"
#include "parking/parking_menu.h"

int main() {

    setup_console(); // Configuración de consola con colores + UTF-8

    char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto

    while(1) {

        printf_c(DARK_CYAN_TXT, "\n------- TEKNO BASERRI -------\n\n"); // Ejemplo de salida de texto con color
        printf("1. Gestionar granja.\n");
        printf("2. Acceder a parking.\n");
        printf("\nPresiona 'q' para salir.\n\n");
        printf("Input: ");

        scan_str(input_buffer);

        putchar('\n');

        if (strcmp(input_buffer, "q") == 0) {

            printf("\nFinalizando programa...\n");

            break;
        }
        else if (strcmp(input_buffer, "1") == 0) {

            // Menú granja
            // TODO - Implementar Granja
            printf("Sorry! Not implemented yet!\n");
            //menuGranja(); // Temporalmente inhabilitada -> CAMBIAR Includes que ya no funcionen

        } else if (strcmp(input_buffer, "2") == 0) {

            // Menú parking

            parking_menu();

        }

        else { printf("Opción no reconocida!\n"); }


    }

    // TODO - Desalojar memoria dinámica si la hay

    restore_console(); // Restauración de configuración de consola (se revocan los cambios)

    return 0;
}


