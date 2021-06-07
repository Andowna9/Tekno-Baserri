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

int order_by_name(const void* pa, const void* pb);

void check_ordered_food(int (*order_criterion)(const void* a, const void* b), bool ascending_order);

int find_food_id_by_name(const char* name);

void register_animal_food(const char* name, float price, float init_amount);
void delete_animal_food(int id);
void check_all_food();
void check_available_food();
void check_third_party_food();
int get_food_count();
Animal_Food* get_food_by_id(int id);
void add_animal_food(int id, float amount);
void buy_animal_food(int id, float amount);
void consume_animal_food(int id, float amount);

void read_food_types();

void free_animal_food_memory();

#endif
