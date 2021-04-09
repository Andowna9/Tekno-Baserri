#ifndef FOOD_H
#define FOOD_H

#include <stdbool.h>

typedef struct {

    char* name; // Nombre
    float price; // Precio por kg
    float amount; // Cantidad en kg

}Animal_Food;

int order_by_price(const void* a, const void* b);

int order_by_amount(const void* a, const void* b);

void check_ordered_food(int (*order_criterion)(const void* a, const void* b), bool ascending_order);

void register_animal_food(Animal_Food food);
void delete_animal_food(int id);
void check_animal_food();
int get_food_count();
Animal_Food* get_food_by_id(int id);
void buy_animal_food(int id, float amount);

int read_food_types();

void free_animal_food_memory();

#endif
