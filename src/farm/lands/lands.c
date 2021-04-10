#include "lands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <std_utils.h>
#include <dynamic_array.h>
#include <management.h>

static dyn_array  lands_arr;

void print_terrain(Terrain terr){

   printf("Nombre: %s\n",terr.name);
    printf("Área: %.2f\n",terr.area);
    printf("Comprado por: %.2f\n",terr.cost);
    printf("Uso: %s \n",terr.in_use ? "Cultivos" : "Animales");
}

// Comprueba el estado de un terreno en concreto

void check_lands() {

    int i;

    for(i = 0;i < lands_arr.size ;i++) {

        Terrain* terr_ptr = (Terrain*) get_elem(lands_arr,i);
        printf("\n___ TERRENO %i ___\n\n",i+1);
        print_terrain(*terr_ptr);

    }

}

void buy_lands(Terrain terr){

   Terrain* terr_ptr = (Terrain*) malloc(sizeof (Terrain));
   *terr_ptr = terr;

    add_elem(&lands_arr,terr_ptr);

    save_lands();

    // Registrar gastos

    register_expense(terr.cost);
}

void sell_lands(int i, float price){

   printf("Estás borrando el terreno %i \n",i);
   Terrain* terr_ptr = (Terrain*) get_elem(lands_arr,i-1);
   print_terrain(*terr_ptr);
   if (confirm_action("Seguro que quieres borrar? :\n")) {

       remove_elem(&lands_arr ,i-1);
       printf("Se ha borrado");
   }
   else {
       printf("No se ha borrado");
   }

   save_lands();

   // Registrar beneficios

   register_profit(price);

}

// Lee y carga los terrenos en memoria

void read_lands() {

    FILE* fp = fopen("terrain.csv", "r");

    if (fp == NULL) {

        return;
    }

    init_arr(&lands_arr, 15);

    char buff [1024];

    int row = 0;

    int column = 0;

    while(fgets(buff, 1024, fp)) {

        row++;

        column = 0;

        if (row == 1) {

            continue;
        }

        char* token = strtok(buff, ", ");

        Terrain* terr_ptr = (Terrain*) malloc(sizeof(Terrain));

        while(token != NULL) {

            switch (column) {

                // Nombre

                case 1:

                    terr_ptr->name = (char*) malloc(strlen(token) + 1);

                    strcpy(terr_ptr->name, token);

                    break;

                // Área

                case 2:

                    terr_ptr->area = strtof(token, NULL);

                    break;

                // Coste

                case 3:

                    terr_ptr->cost = strtof(token, NULL);

                    break;

                case 4:

                      terr_ptr->in_use = atoi(token);

                     break;

            }

            token = strtok(NULL, ", ");
            column++;
        }

        add_elem(&lands_arr, terr_ptr);

    }


    fclose(fp);

}

// Guarda los terrenos en un fichero

void save_lands() {

    FILE* fp = fopen("terrain.csv", "w");

    if (fp == NULL) {

        return;
    }

    fprintf(fp, "ID, Name, Area, Cost, In_Use\n");

    int i;

    for (i = 0; i < lands_arr.size; i++) {

        Terrain* terr_ptr = (Terrain*) get_elem(lands_arr, i);

        fprintf(fp, "%d, %s, %f, %f, %d\n", i + 1, terr_ptr->name, terr_ptr->area, terr_ptr->cost, terr_ptr->in_use);
    }

    fclose(fp);

}

// Libera la memoria dinámica empleada por el array de terrenos

void free_lands_mem() {

    int i;

    for (i = 0; i < lands_arr.size; i++) {

        Terrain* terr_ptr = (Terrain*) get_elem(lands_arr, i);

        free(terr_ptr->name);

        free(terr_ptr);
    }

    free_mem(&lands_arr);
}
