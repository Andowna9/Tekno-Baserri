#include <stdlib.h>
#include <stdio.h>
#include <console_config.h>
#include "parking.h"


void create_parking(int rows, int cols) {

    num_rows = rows;

    num_cols = cols;

    parking =  malloc(sizeof(p_lot*) * num_rows);

    int i;

    for (i = 0; i < num_rows; i++) {

        parking[i] = calloc(num_cols, sizeof(p_lot));
    }

}

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


}

void remove_vehicle(int row, int col) {

    parking[row][col].l_plate = NULL;

}

void print_parking() {

    int i;

    printf("    "); // 4 espacios

    for (i = 1; i < num_rows + 1; i++) {

        printf("%d   ", i);
    }

    putchar('\n');

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
}

void free_parking_memory() {

    int i;

    int j;

    for (i = 0; i < num_rows; i++) {

        for (j = 0; j < num_cols; j++) {

            if (parking[i][j].l_plate != NULL) {

                free(parking[i][j].l_plate);

                parking[i][j].l_plate = NULL;
            }
        }

        free(parking[i]);

    }

    free(parking);

}
