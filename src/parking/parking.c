#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <console_config.h>
#include "parking.h"

// Creación dinámica del parking

void create_parking(int rows, int cols) {

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

    return parking[row][col].l_plate != NULL;
}

// MANTENIMIENTO

void modify_columns(int dn) {

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

    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) { // Out of bounds

        printf_c(LIGHT_RED_TXT, "La plaza no existe!\n");
        return 1;

    }

    return 0;

}

// Inserta un vehículo en el parking

int insert_vehicle(char* key, int row, int col) {

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

    // Liberación de puntero a matrícula

    free(parking[row][col].l_plate);

    parking[row][col].l_plate = NULL;

    parking[row][col].t_stamp = 0;

}

// Elimina un vehículo del parking

int remove_vehicle(int row, int col) {

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

    FILE* fp = fopen("parking.txt", "w");

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

    FILE* fp = fopen("parking.txt", "r");

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

    time_t current_stamp = time(NULL);

    time_t elapsed = current_stamp - time_stamp;

    struct tm *info;

    info = gmtime(&elapsed);

    const char* str = "%d h %d min %d s";

    // Formateamos y obtenemos el número de caracteres necesarios (sin contar '\0')

    int num_c = snprintf(NULL, 0, str, info->tm_hour,info->tm_min, info->tm_sec);

    char* str_f = (char*) malloc(sizeof(char) * (num_c + 1));

    snprintf(str_f, num_c + 1, str, info->tm_hour,info->tm_min, info->tm_sec);

    return str_f;

}
