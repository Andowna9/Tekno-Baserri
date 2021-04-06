#ifndef LANDS_H
#define LANDS_H

#include <stdbool.h>

// Terreno que se usa para cultivos o animales, pero no ambos simultáneamente

typedef struct {

    bool in_use;
    char* name;
    float area; // Hectáreas
    float cost;

    union {

        void* animals; // Esto será en cpp
        void* crops;

    } content;

} Terrain;

// consultas terrenos
void buy_lands();
void sell_lands();
void check_lands();

#endif
