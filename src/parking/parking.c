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

void add_columns(int n) {

    if (num_cols + n > MAX_COLS) {

        printf("Límite de columnas excedido\n");

        return;
    }

    int i;

    for (i = 0; i < num_rows; i++) {

        parking[i] = (p_lot*) realloc(parking[i], sizeof(p_lot) * (num_cols + n));

        int j;

        // Inicialización de nuevas matrículas a NULL, ya que realloc() no se comporta como calloc()

        for (j = num_cols; j < num_cols + n; j++) {

            parking[i][j].l_plate = NULL;
        }
    }

    num_cols += n;
}

void add_rows(int n) {

    if (num_rows + n > MAX_ROWS) {

        printf("Límite de filas excedido\n");

        return;

    }

    parking = (p_lot**) realloc(parking, sizeof(p_lot*) * (num_rows + n));

    int i;

    for (i = num_rows; i < num_rows + n; i++) {

         parking[i] = (p_lot*) calloc(num_cols, sizeof(p_lot)); // Usamos calloc() para las columnas de la fila
    }

    num_rows += n;
}

// Inserta un vehículo en el parking

void insert_vehicle(char* key, int row, int col) {

    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) { // Out of bounds

        printf("La plaza no existe!\n");

        return;

    }

    if (vehicle_inside(row, col)) {

        printf("La plaza está ocupada!\n");

        return;
    }

    parking[row][col].l_plate = key;

    time_t t_stamp = time(NULL);

    if (t_stamp != -1) {

        parking[row][col].t_stamp = t_stamp;

    }

    num_vehicles++;

    printf("Vehículo registrado correctamente\n");

}

// Limpieza de aparcamiento

void clear_p_lot(int row, int col) {

    // Liberación de puntero a matrícula

    free(parking[row][col].l_plate);

    parking[row][col].l_plate = NULL;

}

// Elimina un vehículo del parking

void remove_vehicle(int row, int col) {

    if (!vehicle_inside(row, col)) {

        printf("No hay ningún vehículo que sacar!\n");

        return;
    }

    clear_p_lot(row, col);

    num_vehicles--;

    printf("Vehículo retirado con éxito\n");

}


// Representación matricial del parking en consola

void print_parking() {

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

                printf_c(LIGHT_GREEN_TXT, "-");

            }

            else {

                printf_c(LIGHT_RED_TXT, "•");

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

    fscanf(fp, size_format, &num_cols, &num_rows);

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

    char* str = (char*) malloc(sizeof (char) * 50);

    sprintf_s(str, 50, "%d h %d min %d s", info->tm_hour,info->tm_min, info->tm_sec);

    return str;

}
