#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdin_fix.h>
#include <management.h>
#include <dynamic_array.h>
#include "food.h"

// LÓGICA

static dyn_array food_arr;

static const char* file_name = "food.csv";

static int order_type;

// Callbacks para ordenar de acuerdo a diferentes criterios

// Ordenar por precio

int order_by_price(const void* pa, const void* pb) {

    int ret = 0;

    Animal_Food a = *(Animal_Food*) (*(void**)pa);

    Animal_Food b = *(Animal_Food*) (*(void**)pb);

    if (a.price > b.price) ret = 1;

    else if (a.price < b.price) ret = -1;

    return ret * order_type;
}

// Ordenar por cantidad

int order_by_amount(const void* pa, const void* pb) {

    int ret = 0;

    Animal_Food a = *(Animal_Food*) (*(void**)pa);

    Animal_Food b = *(Animal_Food*) (*(void**)pb);

    if (a.amount > b.amount) ret = 1;

    else if (a.amount < b.amount) ret = -1;

    return ret * order_type;
}

// Copia dinámica sobre la cual se harán reordenacions, utilizando quick sort

Animal_Food* copy_arr() {

    Animal_Food* copy = (Animal_Food*) malloc(sizeof(Animal_Food) * food_arr.size);

    int i;

    for (i = 0; i < food_arr.size; i++) {

        copy[i] = *((Animal_Food*) get_elem(food_arr,i));
    }

    return copy;
}

void print_food(Animal_Food food, int index) {


    printf("ID: %d | Nombre: %s, Precio: %.2f €/kg", index + 1, food.name, food.price);

    if (food.amount > 0) {

        printf(" x%.2f KG", food.amount);
    }

    putchar('\n');

}

// Se obtiene el alimento por id (identificación)

Animal_Food* get_food(int index) {

    return (Animal_Food*) get_elem(food_arr, index);
}


// Guarda los alimentos borrando el contenido anterior

void write_food_types() {

    FILE* fp = fopen(file_name, "w");

    fprintf(fp, "ID, Name, Price, Amount\n");

    int i;

    for (i = 0; i < food_arr.size; i++) {

        Animal_Food food = *get_food(i);

        fprintf(fp, "%d, %s, %f, %f\n", i + 1, food.name, food.price, food.amount);

    }

    fclose(fp);

}


// Devuelve el número de alimentos registrados

int get_food_count() {

    return food_arr.size;
}

// Registra comida para animales

void register_animal_food(Animal_Food food) {

    food.amount = 0;

    Animal_Food* food_ptr = (Animal_Food*) malloc(sizeof(Animal_Food));

    *food_ptr = food;

    // Guardado en memoria y fichero

    add_elem(&food_arr, food_ptr);

    write_food_types();

}


// Borra un alimento dado

void delete_animal_food(int id) {

    remove_elem(&food_arr, id - 1);

    // Guardado en fichero

    write_food_types();

}


void check_ordered_food(int (*order_criterion)(const void* a, const void* b), bool ascending_order) {

    order_type = ascending_order? -1: 1;

    //Animal_Food* copy = copy_arr();

    //qsort(copy, food_arr.size, sizeof(Animal_Food), order_criterion);

    qsort(food_arr.data, food_arr.size, sizeof(void*), order_criterion);

   /*  int i;

    for (i = 0; i < food_arr.size; i++) {

        print_food(copy[i], i);
    }

    free(copy); */

}

Animal_Food* get_food_by_id(int id) {

    return get_elem(food_arr, id - 1);
}

// Compra de comida, proporcionando cantidad en kg

int buy_animal_food(int id, float amount) {

   Animal_Food* ptr = get_food_by_id(id);

   if (ptr == NULL) return -1;

   ptr->amount += amount;

   // Registrar gasto

   write_food_types();

   register_expense(amount * ptr->price);

   return 0;

}

void check_animal_food() {

    int i;

    for (i = 0; i < food_arr.size; i++) {

        Animal_Food food = *get_food(i);

        print_food(food, i);
    }
}



// Lectura de tipos de comida guardados de fichero

int read_food_types() {

    FILE* fp = fopen(file_name, "r");

    if (fp == NULL) {

        return -1;
    }

    char buffer[1024];

    init_arr(&food_arr, 15);  // Inicialización de array dinámico

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

        Animal_Food* ptr_food = malloc(sizeof(Animal_Food));

        *ptr_food = food;

        add_elem(&food_arr, ptr_food);
    }

    fclose(fp);

    return 0;
}

// Libera la memoria asociada a punteros dinámicos: Nombre

void free_animal_food_memory() {

    int i;

    for (i = 0; i < food_arr.size; i++) {

        Animal_Food* ptr_food = get_food(i);

        free(ptr_food->name);

        free(ptr_food);
    }

    free_mem(&food_arr);
}

