#include <stdio.h>
#include <stdin_fix.h>
#include <console_config.h>
#include <string.h>
#include <stdlib.h>
#include "parking.h"
#include <stdbool.h>

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
        printf_c(LIGHT_GREEN_TXT, "Añadida(s) con éxito.\n");
    }

}

void clear_and_redraw() {
    clear_screen(); // Limpiamos pantalla
    printf_c(LIGHT_MAGENTA_TXT,"------- PARKING -------\n\n");
    print_parking(); // Redibujamos el parking
}

void clear_redraw_and_highlight(int r, int c) {
    set_highlighted_point(r, c); // Destacamos el punto
    clear_and_redraw();
    reset_highlighted_point(); // Dejamos de destacar
}

bool save_needed = false;

void parking_menu() {

    init_parking();

    char i_buffer [DEFAULT_BUFFER_SIZE];

    reset_highlighted_point();

    while(1) {

        clear_screen();

        printf_c(LIGHT_MAGENTA_TXT,"------- PARKING -------\n");

        // Imprimir representación del parking

        print_parking();

        // Imprimir opciones disponibles por categorías

        printf("--- Gestión");
        printf("\n\n");

        printf(" 1. Introducir vehículo.\n");
        printf(" 2. Sacar vehículo.\n");
        printf(" 3. Consultar información de plaza.\n");
        printf(" 4. Obtener estadísticas generales.\n");
        putchar('\n');

        printf("--- Mantenimiento\n\n");

        printf(" 5. Añadir filas.\n");
        printf(" 6. Añadir columnas.\n");
        printf(" 7. Crear nueva configuración.\n");
        putchar('\n');

        printf("\nIntroduce 's' para guardar los cambios.\n");
        printf("Introduce 'v' para volver.\n");

        printf("\nInput: ");
        scan_str(i_buffer, sizeof(i_buffer));


        printf("\n----------------------\n\n"); // Separador


        if (strcmp(i_buffer, "v") == 0 || strcmp(i_buffer, "V") == 0) {

            if (save_needed) {
                int dont_save = confirm_action("Existen cambios sin guardar, ¿salir?");

                if (dont_save) {
                    printf_c(LIGHT_RED_TXT, "No se han guardado los cambios.\n");
                    save_needed = false;
                    break;
                }
            } else {
                break;
            }



        }

        else if (strcmp(i_buffer, "s") == 0) {
            save_parking();
            save_needed = false;
            printf_c(LIGHT_GREEN_TXT, "Guardado con éxito\n");
        }

        // Introducir vehículo en plaza

        else if (strcmp(i_buffer,"1") == 0) {

           int r, c;
           scan_p_plot(&r, &c);

           if (!out_of_bounds(r, c)) {

               printf("Matrícula: ");
               char* l_plate = read_str();

               // Limpiamos y redibujamos para destacar el punto
               clear_redraw_and_highlight(r, c);

               // Confirmamos que quiera guardar
               printf("\nMatrícula: %s\n\n", l_plate);
               int save = confirm_action("Aparcar coche?");

               if (save) {
                   insert_vehicle(l_plate, r, c);
                   save_needed = true;

               } else {
                   printf_c(LIGHT_RED_TXT, "Operación cancelada. Coche no agregado\n");
               }

           }

           putchar('\n');


        }


        // Quitar vehículo de la plaza

        else if (strcmp(i_buffer, "2") == 0) {

            int r, c;
            scan_p_plot(&r, &c);

            if (!out_of_bounds(r, c)) {

                // Limpiamos y redibujamos para destacar el punto
                clear_redraw_and_highlight(r, c);

                // Confirmamos que quiera guardar
                int save = confirm_action("Retirar coche?");

                if (save) { // Caso afirmativo
                    remove_vehicle(r, c); // Aquí se incluye el aviso de que el coche se ha retirado con éxito
                    save_needed = true;


                } else { // Caso negativo
                    printf_c(LIGHT_RED_TXT, "Operación cancelada. Coche no retirado\n");
                }

            }


            putchar('\n');


        }

        // Consultar información de plaza

        else if (strcmp(i_buffer, "3") == 0) {

            int r;
            int c;
            scan_p_plot(&r, &c);

            if(!out_of_bounds(r, c)) {

                // Limpiamos y redibujamos para destacar el punto
                clear_redraw_and_highlight(r, c);

                // Datos de la plaza
                putchar('\n');
                printf_c(UNDERLINE, "Datos de plaza");
                printf(":\n\n"); // Necesario caracter adicional para que el subrayado no se extienda


                // Comprueba si la plaza está vacía para que no imprima "null" por pantalla
                char* plate = parking[r][c].l_plate;

                if (plate == NULL) {
                    printf_c(LIGHT_CYAN_TXT, "Plaza libre\n");
                    printf("Tiempo en parking: -\n");

                } else {
                    // Matrícula
                    printf("Vehículo con matrícula: ");
                    printf_c(LIGHT_YELLOW_TXT, "%s\n", plate);

                    // Tiempo en el parking
                    char* ptr = get_time_passed(parking[r][c].t_stamp);
                    printf("Tiempo en parking: %s\n", ptr);
                    free(ptr);
                }

            }

            putchar('\n');

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
            // TODO confirmar añadir columnas
            save_needed = true;
        }

        // Cambiar número de columnas
        else if (strcmp(i_buffer, "6") == 0) {

           modify_parking(modify_columns);
           // TODO confirmar añadir columnas
           save_needed = true;
        }

        //Crear nueva configuración
        else if (strcmp(i_buffer, "7") == 0) {

            // TODO Borrar configuración del fichero y crear un parking desde 0
        }

        // Opción incorrecta

        else { printf("Opción no válida!\n"); }

        putchar('\n'); // Nueva línea


        press_to_continue();
    }
}
