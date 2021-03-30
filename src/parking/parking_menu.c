#include <stdio.h>
#include <stdin_fix.h>
#include <string.h>
#include <stdlib.h>
#include "parking.h"

void scan_p_plot(int* row_ptr, int* col_ptr) {

    printf("Plaza: ");
    char row;
    int column ;
    scanf("%c%d",&row, &column);
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
            ret = scanf("%d %d", &w, &h);
            clear_stdin();
        } while(ret != 2);


        printf("Número de aparcamientos posibles: %d\n", w * h);
        printf("Desea continuar?(s/n) ");

        scan_str(buff);

        if (strcmp(buff, "s") == 0) {

            create_parking(w, h); // Creación de parking en memoria

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
        printf("Introduce 'v' para volver.\n");

        printf("Input: ");
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

        else if (strcmp(i_buffer, "2") == 0) {


        }

        // Consultar información de plaza

        else if (strcmp(i_buffer, "3") == 0) {

            int r;
            int c;

            scan_p_plot(&r, &c);

            printf("Vehículo con matrícula: %s\n", parking[r][c].l_plate);
        }

        else { printf("Opción no válida!\n"); }

    }
}
