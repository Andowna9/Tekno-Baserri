#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdin_fix.h>
#include <management.h>
#include "food.h"

#define MAX_SIZE 25

// LÓGICA

static int size = 0;

static Animal_Food arr [MAX_SIZE];

static const char* file_name = "food.csv";

// Guarda los tipos de comida en fichero csv con append - Más complicado y quizás no necesario

/*

int save_food_type(Animal_Food food) {

    FILE* fp = fopen(file_name, "a");

    if (fp == NULL) {

        return -1;
    }

    fseek(fp, 0, SEEK_END);

    // Si se trata de la primera vez que se escribe, se añade el nombre de las columnas

    if (ftell(fp) == 0) {

        fprintf(fp, "ID, Name, Price, Amount\n");
    }

    // A continuación se guarda el tipo de comida

    fprintf(fp, "%d, %s, %f, %f\n", food.id, food.name, food.price, food.amount);

    fclose(fp);

    return 0;

} */

// Guarda los alimentos borrando el contenido anterior

void write_food_types() {

    FILE* fp = fopen(file_name, "w");

    fprintf(fp, "ID, Name, Price, Amount\n");

    int i;

    for (i = 0; i < size; i++) {

        Animal_Food food = arr[i];

        fprintf(fp, "%d, %s, %f, %f\n", food.id, food.name, food.price, food.amount);

    }

    fclose(fp);

}

// Determina si el array está lleno (no hay más espacio)

int space_available() {

    return size < MAX_SIZE;
}

// Devuelve el número de alimentos registrados

int get_food_count() {

    return size;
}

// Registra comida para animales

void register_animal_food(Animal_Food food) {

    food.id = size + 1;

    food.amount = 0;

    // Guardado en memoria y fichero

    arr[size++] = food;

    write_food_types();

}

// Se obtiene el alimento por id (identificación)

Animal_Food* get_food_by_id(int id) {

    if (id < 1 || id > size) {

        return NULL;
    }

    return &arr[id - 1];
}

// Borra un alimento dado

void delete_animal_food(int id) {

    int i;

    // Desplazamiento hacia la izquierda de todos las estructuras posteriores al índice para mantener el orden

    for (i = id; i < size; i++) {

        arr[i - 1] = arr[i];

        arr[i -1].id--;
    }

    size--;

    // Guardado en fichero

    write_food_types();

}

// Imprime la comida y cantidad comprada si es superiora 0 kg

void check_animal_food() {

    int i;

    for (i = 0; i < size; i++) {

        Animal_Food food = arr[i];

        printf("ID: %d | Nombre: %s | Precio: %.2f €/kg", food.id, food.name, food.price);

        if (food.amount > 0) {

            printf(" | Cantidad: %.2f", food.amount);
        }

        putchar('\n');
    }
}

// Compra de comida, proporcionando cantidad en kg

int buy_animal_food(int id, float amount) {

   Animal_Food* ptr = get_food_by_id(id);

   if (ptr == NULL) return -1;

   ptr->amount += amount;

   // Registrar gasto

   register_expense(amount * ptr->price);

   return 0;

}



// Lectura de tipos de comida guardados de fichero

int read_food_types() {

    FILE* fp = fopen(file_name, "r");

    if (fp == NULL) {

        return -1;
    }

    char buffer[1024];

    size = 0;  // Tamaño a 0 para que cada vez que se llame a la función se lea de nuevo

    int row = 0;

    int column = 0;

    while(fgets(buffer, 1024, fp)) {

        row++;

        column = 0;

        if (row == 1) continue; // Saltamos la línea que contiene los nombres de las columnas

        char* token = strtok(buffer, ", ");

        Animal_Food food;

        while (token != NULL) {

            switch (column) {

                // ID

                case 0:

                    food.id = atoi(token);

                    break;

                // Nombre

                case 1:

                    food.name = (char*) malloc(sizeof(char) * (strlen(token) + 1));

                    strcpy(food.name, token);

                    break;

                // Precio

                case 2:

                    food.price = strtof(token, NULL);

                    break;

               // Cantidad

               case 3:

                    food.amount = atoi(token);

                    break;

            }

            token = strtok(NULL, ", ");
            column++;
        }

        arr[size++] = food;
    }

    fclose(fp);

    return 0;
}

// Libera la memoria asociada a punteros dinámicos: Nombre

void free_animal_food_memory() {

    int i;

    for (i = 0; i < size; i++) {

        free(arr[i].name);
    }
}

