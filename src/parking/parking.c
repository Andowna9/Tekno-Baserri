#include <stdlib.h>
#include <stdio.h>
#include <std_utils.h>
#include <string.h>
#include <time.h>
#include <console_config.h>
#include "parking.h"

// Creación dinámica del parking

void create_parking(int rows, int cols) {
    /** @brief Function for creation of parking of rows x cols size given in the parameters
     *
     *  @param rows Rows
     *  @param cols Columns
        @return Void
      */

    // Inicialización de variables globales en header

    num_rows = rows;

    num_cols = cols;

    num_vehicles = 0;

    // Reserva de momoria

    parking = (p_lot**) malloc(sizeof(p_lot*) * num_rows);

    int i;

    for (i = 0; i < num_rows; i++) {

        parking[i] = (p_lot*) calloc(num_cols, sizeof(p_lot)); // Utilizamos calloc() para inicializar la memoria reservada a 0
    }

}

// Función para comprobar si una plaza está ocupada

int vehicle_inside(int row, int col) {
    /** @brief Checks if a space is occupied by another vehicle
     *
     *  @param row Row
     *  @param col Column
        @return License plate of the vehicle inside, if it's not empty
      */

    return parking[row][col].l_plate != NULL;
}

// MANTENIMIENTO

void modify_columns(int dn) {
    /** @brief Modifies the number of columns
     *
     *  @param dn New number of columns
     *  @return ---
      */

    if (num_cols + dn > MAX_COLS) {

        printf_c(LIGHT_MAGENTA_TXT, "No es posible tener más de %d columnas!\n", MAX_COLS);

        return;
    }

    int i;

    for (i = 0; i < num_rows; i++) {

        parking[i] = (p_lot*) realloc(parking[i], sizeof(p_lot) * (num_cols + dn));

        int j;

        // Inicialización de nuevas matrículas a NULL, ya que realloc() no se comporta como calloc()

        for (j = num_cols; j < num_cols + dn; j++) {

            parking[i][j].l_plate = NULL;
        }
    }

    num_cols += dn;
}

void modify_rows(int dn) {
    /** @brief Modifies the number of rows
     *
     *  @param dn New number of rows
     *  @return ---
      */

    if (num_rows + dn > MAX_ROWS) {

        printf_c(LIGHT_MAGENTA_TXT, "No es posible tener más de %d filas!\n", MAX_ROWS);

        return;

    }

    parking = (p_lot**) realloc(parking, sizeof(p_lot*) * (num_rows + dn));

    int i;
    for (i = num_rows; i < num_rows + dn; i++) {

         parking[i] = (p_lot*) calloc(num_cols, sizeof(p_lot)); // Usamos calloc() para las columnas de la fila
    }

    num_rows += dn;
}

// Comprueba si una posición dada está fuera de rango

int out_of_bounds(int row, int col) {
    /** @brief Checks if a given position is out of bounds
     *
     *  @param row Row number
     *  @param col Column number
     *  @return true if out of bounds, false if not
      */

    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) { // Out of bounds

        printf_c(LIGHT_RED_TXT, "La plaza no existe!\n");
        return 1;

    }

    return 0;

}

// Inserta un vehículo en el parking

int insert_vehicle(char* key, int row, int col) {
    /** @brief Inserts a vehicle in a given position
     *
     *  @param key License plate
     *  @param row Row
     *  @param col COl
     *  @return true if success, false if occupied
      */

    if (vehicle_inside(row, col)) {

        printf_c(LIGHT_RED_TXT, "La plaza está ocupada!\n");
        return 0;
    }


    parking[row][col].l_plate = key;
    time_t t_stamp = time(NULL);

    if (t_stamp != -1) {

        parking[row][col].t_stamp = t_stamp;

    }

    num_vehicles++;

    printf_c(LIGHT_GREEN_TXT, "\nVehículo registrado correctamente");

    return 1;

}

// Limpieza de aparcamiento

void clear_p_lot(int row, int col) {
    /** @brief Clears a parking lot position ?????????
     *
     *  @param row Row
     *  @param col Column
     *  @return Void
      */

    // Liberación de puntero a matrícula

    free(parking[row][col].l_plate);

    parking[row][col].l_plate = NULL;

    parking[row][col].t_stamp = 0;

}

// Elimina un vehículo del parking

int remove_vehicle(int row, int col) {
    /** @brief Erases vehicle from parking
     *
     *  @param row Row
     *  @param col Column
     *  @return true if success, false if not
      */

    if (!vehicle_inside(row, col)) {

        printf_c(LIGHT_RED_TXT, "No hay ningún vehículo que sacar!\n");
        return 0;
    }

    clear_p_lot(row, col);

    num_vehicles--;

    printf_c(LIGHT_GREEN_TXT, "\nVehículo retirado con éxito");
    return 1;

}


// Representación matricial del parking en consola

void set_highlighted_point(int x, int y) {
    highlighted_point.x = x;
    highlighted_point.y = y;
}

void reset_highlighted_point() {
    highlighted_point.x = -1;
    highlighted_point.y = -1;
}

void print_parking() {
    /** @brief Prints the parking lot in console
     *
     *  @return Void
      */

    // Variables locales - Configuración visual en consola

    ANSI_COLOR free_color = LIGHT_CYAN_TXT;
    ANSI_COLOR occupied_color = LIGHT_YELLOW_TXT;
    ANSI_COLOR highlight_color = LIGHT_RED_TXT;

    char free_symbol [] = "-";
    char occupied_symbol [] = "•";

    // Leyenda

    putchar('\n');

    if (highlighted_point.x >= 0 && highlighted_point.y >= 0) {
        printf_c(highlight_color, " Seleccionado %s / %s\n", occupied_symbol, free_symbol);
    }

    printf_c(occupied_color, " Ocupado %s\n", occupied_symbol);
    printf_c(free_color," Libre  %s\n", free_symbol);

    // Visualización de las columnas (numéricas)

    int i;

    putchar('\n');

    printf("    "); // 4 espacios

    for (i = 1; i <= num_cols; i++) {

        if (i >= 10) printf("%d  ", i);

        else printf("%d   ", i);

    }

    putchar('\n');

    // Visualización de filas (letras) y estado de ocupación de aparcamientos

    int j;

    for (i = 0; i < num_rows; i++) {

        printf(" %c ",'A' + i);

        for (j = 0; j < num_cols; j++) {

            printf("[");

            if (!vehicle_inside(i, j)) {

                if (i == highlighted_point.x && j == highlighted_point.y) { // La plaza que queremos destacar
                    printf_c(highlight_color, "-");
                } else {
                    printf_c(free_color, "-");
                }


            }

            else {

                if (i == highlighted_point.x && j == highlighted_point.y) { // La plaza que queremos destacar
                    printf_c(highlight_color, "•");
                } else {
                    printf_c(occupied_color, "•"); // No es una plaza que queramos destacar
                }

            }

            printf("] ");
        }

        putchar('\n');
    }

    putchar('\n');
}

// Libera toda la memria dinámica empleada en el parking

void free_parking_memory() {
    /** @brief Frees dinamic memory used in the creation of the parking
     *
     *  @return Void
      */

    int i;

    int j;

    for (i = 0; i < num_rows; i++) {

        for (j = 0; j < num_cols; j++) {

            if (vehicle_inside(i, j)) {

                clear_p_lot(i, j);
            }
        }

        free(parking[i]);

    }

    free(parking);

}

// Formatos que se utilizan en lectura y escritura

static char size_format [] = "%d x %d";

static char vehicle_format [] = "(%d, %d) -> %s | %lld";

// Guarda los datos del parking en un fichero de texto

void save_parking() {
    /** @brief Saves parking information in a file
     *
     *  @return Void
      */

    FILE* fp = fopen("parking.config", "w");

    fprintf(fp, size_format, num_rows, num_cols);

    int i;

    int j;

    for (i = 0; i < num_rows; i++) {

        for (j = 0; j < num_cols; j++) {

            if (vehicle_inside(i, j)) {

                p_lot pl = parking[i][j];

                fputc('\n', fp);

                fprintf(fp, vehicle_format, i, j, pl.l_plate, pl.t_stamp);
            }
        }
    }

    fclose(fp);
}

// Carga los datos del parking

int load_parking() {
    /** @brief Loads the information of the parking in a file
     *
     *  @return -1 if file is empty
      */

    FILE* fp = fopen("parking.config", "r");

    if (fp == NULL) {

        return -1;
    }

    fscanf(fp, size_format, &num_rows, &num_cols);

    create_parking(num_rows, num_cols);

    // Quitamos el '\n' restante

    fgetc(fp);

    // Rellenar el parking

    int i;

    int j;

    char buffer [50];

    while(fgets(buffer,50,fp) != NULL) {

       char str [25];

       time_t t_stamp;

       sscanf(buffer, vehicle_format, &i, &j, str, &t_stamp);

       char* l_plate = (char*) malloc(sizeof(char) * (strlen(str) + 1));

       strcpy(l_plate, str);

       parking[i][j] = (p_lot) {l_plate, t_stamp};

       num_vehicles++;
    }

    fclose(fp);

    return 0;
}

char* get_time_passed(time_t time_stamp) {
    /** @brief Logs the time passed
     *
     *  @param time_stamp time stamp
     *  @return formatted string of the passed time
      */

    time_t current_stamp = time(NULL);

    time_t elapsed = current_stamp - time_stamp;

    // Cálculo de horas minutos y segundos

    int hours = elapsed / 3600;

    elapsed %= 3600;
    int minutes = elapsed / 60;

    elapsed %= 60;
    int seconds = elapsed;

    // Devolvemos string formateado

    return format_str("%d h %d min %d s", hours, minutes, seconds);

}
