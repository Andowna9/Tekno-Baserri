#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <std_utils.h>
#include "farm/farm.h"
#include "parking/parking_menu.h"
#include "parking/parking.h"
#include <logger.h>

static void configure_logger() {
    set_log_file("main.log");
}

int main() {

    setup_console(); // Configuración de consola con colores + UTF-8
    configure_logger();
    char input_buffer[DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

    //test_each_printf_c();
    //test_nums_printf_c();

    //logger_demo();

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

            printf("Finalizando programa...\n");

            break;
        }
        else if (strcmp(input_buffer, "1") == 0) {

            // Menú granja

            farm_menu();

        } else if (strcmp(input_buffer, "2") == 0) {

            // Menú parking

            parking_menu();

        }

        else { printf("Opción no reconocida!\n\n"); press_to_continue();}


    }

    // Liberación de memoria dinámica sobrante

    free_parking_memory();

    restore_console(); // Restauración de configuración de consola (se revocan los cambios)

    return 0;
}


