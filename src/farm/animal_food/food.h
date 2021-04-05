#ifndef FOOD_H
#define FOOD_H

typedef struct {

    int id; // Identificación
    char* name; // Nombre
    float price; // Precio por kg
    float amount; // Cantidad en kg

}Animal_Food;


void register_animal_food(Animal_Food food);
void delete_animal_food(int id);
void check_animal_food();
int get_food_count();
Animal_Food* get_food_by_id();
int buy_animal_food(int id, float amount);

int space_available();
int read_food_types();

#endif
