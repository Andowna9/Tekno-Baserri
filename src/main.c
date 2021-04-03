#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <stdin_fix.h>
#include "granja/farm.h"
#include "parking/parking_menu.h"

int main() {

    setup_console(); // Configuración de consola con colores + UTF-8

    char input_buffer[DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

    //test_each_printf_c();
    //test_nums_printf_c();


    while(1) {

        clear_screen();

        printf_c(DARK_GRAY_TXT, "------- TEKNO BASERRI -------\n\n"); // Ejemplo de salida de texto con color
        printf("1. Gestionar granja.\n");
        printf("2. Acceder a parking.\n");
        printf("\nPresiona 'q' para salir.\n\n");
        printf("Input: ");

        scan_str(input_buffer, sizeof(input_buffer));

        putchar('\n');

        if (strcmp(input_buffer, "q") == 0 || strcmp(input_buffer, "Q") == 0) {

            printf("\nFinalizando programa...\n");

            break;
        }
        else if (strcmp(input_buffer, "1") == 0) {

            // Menú granja
            // TODO - Implementar Granja
            farm_menu(); // Temporalmente inhabilitada -> CAMBIAR Includes que ya no funcionen

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


