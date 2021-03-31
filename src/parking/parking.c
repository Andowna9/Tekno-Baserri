#include <stdlib.h>
#include <stdio.h>
#include <console_config.h>
#include "parking.h"

// Creación dinámica del parking

void create_parking(int rows, int cols) {

    // Inicialización de variables globales en header

    num_rows = rows;

    num_cols = cols;

    num_vehicles = 0;

    // Reserva de momoria

    parking =  (p_lot**) malloc(sizeof(p_lot*) * num_rows);

    int i;

    for (i = 0; i < num_rows; i++) {

        parking[i] = (p_lot*) calloc(num_cols, sizeof(p_lot));
    }

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

        // Inicialización de nuevas matrículas a NULL

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

         parking[i] = (p_lot*) calloc(num_cols, sizeof(p_lot));
    }

    num_rows += n;
}

// Inserta un vehículo en el parking

void insert_vehicle(char* key, int row, int col) {

    if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) { // Out of bounds

        printf("La plaza no existe!\n");

        return;

    }

    if (parking[row][col].l_plate != NULL) {

        printf("La plaza está ocupada!\n");

        return;
    }

    parking[row][col].l_plate = key;

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

    if (parking[row][col].l_plate == NULL) {

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

            char* str = parking[i][j].l_plate;

            printf("[");

            if (str == NULL) {

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

            if (parking[i][j].l_plate != NULL) {

                clear_p_lot(i, j);
            }
        }

        free(parking[i]);

    }

    free(parking);

}
