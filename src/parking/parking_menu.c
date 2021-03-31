#include <stdio.h>
#include <stdin_fix.h>
#include <console_config.h>
#include <string.h>
#include <stdlib.h>
#include "parking.h"

void scan_p_plot(int* row_ptr, int* col_ptr) {

    printf("Plaza: ");
    char row;
    int column ;
    scanf("%c%2d",&row, &column);
    *row_ptr = row - 'A';
    *col_ptr = column - 1;

    clear_stdin();
}

void init_parking() {

    char buff[MAX_BUFFER_SIZE];

    // Si no hay una configuarción de parking registrada

    printf("No hay ningún parking registrado\n");

    int w, h;

    int ret;

    while(1) {

        do {
            printf("Tamaño (filas columnas): ");
            ret = scanf("%2d %2d", &h, &w);
            clear_stdin();

            if (h > MAX_ROWS || w > MAX_COLS) {

                printf("Máximo número de filas/columnas superado!\n");

                ret = 0;
            }

            if (h < 0 || w < 0) {

                printf("No se aceptan números negativos!\n");

                ret = 0;
            }

        } while(ret != 2);


        printf("Número de aparcamientos posibles: %d\n", w * h);
        printf("Desea continuar?(s/n) ");

        scan_str(buff);

        if (strcmp(buff, "s") == 0) {

            create_parking(h, w); // Creación de parking en memoria

            break;

        }

    }


}

void parking_menu() {

    init_parking();

    char i_buffer [MAX_BUFFER_SIZE];

    while(1) {

        // Imprimir representación del parking

        print_parking();

        printf("1. Introducir vehículo.\n");
        printf("2. Sacar vehículo.\n");
        printf("3. Consultar información de plaza.\n");
        printf("4. Obtener estadísticas generales.\n");
        printf("5. Añadir filas.\n");
        printf("6. Añadir columnas.\n");
        printf("Introduce 'v' para volver.\n");

        printf("\nInput: ");
        scan_str(i_buffer);

        // Introducir vehículo en plaza

        if (strcmp(i_buffer,"1") == 0) {

           int r;
           int c;

           scan_p_plot(&r, &c);

           printf("Matrícula: ");
           char* l_plate = read_str();
           insert_vehicle(l_plate, r, c);
        }

        // Quitar vehículo de la plaza

        else if (strcmp(i_buffer, "2") == 0) {

            int r;
            int c;

            scan_p_plot(&r, &c);
            remove_vehicle(r, c);

        }

        // Consultar información de plaza

        else if (strcmp(i_buffer, "3") == 0) {

            int r;
            int c;

            scan_p_plot(&r, &c);

            // Datos de la plaza

            printf_c(UNDERLINE, "Datos de plaza\n");

            printf("Vehículo con matrícula: %s\n", parking[r][c].l_plate);
        }

        else if (strcmp(i_buffer, "4") == 0) {

            int total = num_rows * num_cols;


            printf("Plazas ocupadas: %d\n", num_vehicles);
            printf("Plazas libres: %d\n", total - num_vehicles);
            printf("-------------------\n");
            printf("Total de plazas: %d\n", total);
        }

        else if (strcmp(i_buffer, "5") == 0) {

            int n = read_int("Incremento: ");

            add_rows(n);
        }

        else if (strcmp(i_buffer, "6") == 0) {

           int n = read_int("Incremento: ");

           add_columns(n);
        }

        else { printf("Opción no válida!\n"); }

    }
}
