#include <stdio.h>
#include <stdin_fix.h>
#include <console_config.h>
#include <string.h>
#include <stdlib.h>
#include "parking.h"

// Función para pedir por teclado la plaza

void scan_p_plot(int* row_ptr, int* col_ptr) {

    int ret;

    char row;
    int column;

    do {

        printf("Plaza: ");
        ret = scanf("%c%2d",&row, &column);
        clear_stdin();

    } while(ret != 2);

    // A partir de los datos del usuario se obtienen la fila y columna como enteros

    *row_ptr = row - 'A';
    *col_ptr = column - 1;

}

void init_parking() {

    if (load_parking() != -1) {

        printf_c(LIGHT_MAGENTA_TXT, "Configuración encontrada!\n\n");
    }

    else {

        // Si no hay una configuarción de parking registrada

        printf_c(LIGHT_MAGENTA_TXT, "No hay ningún parking registrado.\n\n");

        int w, h;

        int ret;

        while(1) {

            do {
                printf("Tamaño (filas, columnas): ");
                ret = scanf("%2d, %2d", &h, &w);
                clear_stdin();

                if (h > MAX_ROWS || w > MAX_COLS) {

                    printf_c(LIGHT_RED_TXT, "Máximo número de filas/columnas superado!\n");

                    ret = 0;
                }

                if (h < 0 || w < 0) {

                    printf_c(LIGHT_RED_TXT, "No se aceptan números negativos!\n");

                    ret = 0;
                }

            } while(ret != 2);


            printf("Número de aparcamientos posibles: %d\n", w * h);

            if (confirm_action("Desea continuar?")) {

                create_parking(h, w); // Creación de parking en memoria

                break;

            }

        }

    }

}

// Función que modifica filas o columnas dependiendo del puntero a una función que se pase

void modify_parking(void(*modify)(int)) {

    int dn = read_int("Incremento: ");

    putchar('\n');

    if (dn == 0) {

        printf_c(LIGHT_MAGENTA_TXT, "Incremento nulo!\n");
    }

    else if (dn < 0) {

        printf_c(LIGHT_MAGENTA_TXT, "No se admiten decrementos!\n");
    }

    else {

        modify(dn);

    }

}

void parking_menu() {

    init_parking();

    char i_buffer [DEFAULT_BUFFER_SIZE];

    while(1) {

        printf_c(LIGHT_MAGENTA_TXT,"------- PARKING -------\n");

        // Imprimir representación del parking

        print_parking();

        // Imprimir opciones disponibles por categorías

        printf("Gestión:");
        printf("\n\n");

        printf("1. Introducir vehículo.\n");
        printf("2. Sacar vehículo.\n");
        printf("3. Consultar información de plaza.\n");
        printf("4. Obtener estadísticas generales.\n");
        putchar('\n');

        printf("Mantenimiento:\n\n");

        printf("5. Añadir filas.\n");
        printf("6. Añadir columnas.\n");
        putchar('\n');

        printf("Introduce 'v' para volver.\n");

        printf("\nInput: ");
        scan_str(i_buffer, sizeof(i_buffer));


        printf("\n----------------------\n\n"); // Separador

        if (strcmp(i_buffer, "v") == 0) {

            save_parking();
            break;
        }

        // Introducir vehículo en plaza

        else if (strcmp(i_buffer,"1") == 0) {

           int r;
           int c;

           scan_p_plot(&r, &c);

           printf("Matrícula: ");
           char* l_plate = read_str();

           putchar('\n');

           insert_vehicle(l_plate, r, c);
        }

        // Quitar vehículo de la plaza

        else if (strcmp(i_buffer, "2") == 0) {

            int r;
            int c;

            scan_p_plot(&r, &c);

            putchar('\n');

            remove_vehicle(r, c);

        }

        // Consultar información de plaza

        else if (strcmp(i_buffer, "3") == 0) {

            int r;
            int c;

            scan_p_plot(&r, &c);

            // Datos de la plaza

            putchar('\n');
            printf_c(UNDERLINE, "Datos de plaza");
            printf(":\n\n"); // Necesario caracter adicional para que el subrayado no se extienda

            printf("Vehículo con matrícula: %s\n", parking[r][c].l_plate);

            char* ptr = get_time_passed(parking[r][c].t_stamp);

            printf("Tiempo en parking: %s\n", ptr);

            free(ptr);
        }

        // Consultar estadísticas generales

        else if (strcmp(i_buffer, "4") == 0) {

            printf_c(UNDERLINE, "Datos estadísticos");
            printf(":\n\n");

            // Cálculo de total de plazas, num disponibles y ocupadas

            int total = num_rows * num_cols;

            printf("Plazas ocupadas: %d\n", num_vehicles);
            printf("Plazas libres: %d\n", total - num_vehicles);
            printf("-------------------\n");
            printf("Total de plazas: %d\n", total);
        }

        // Cambiar número de filas

        else if (strcmp(i_buffer, "5") == 0) {

            modify_parking(modify_rows);
        }

        // Cambiar número de columnas

        else if (strcmp(i_buffer, "6") == 0) {

           modify_parking(modify_columns);
        }

        // Opción incorrecta

        else { printf("Opción no válida!\n"); }

        putchar('\n'); // Nueva línea


        press_to_continue();
    }
}
