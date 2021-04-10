#include "lands.h"
#include <stdlib.h>
#include <stdio.h>
#include <std_utils.h>
#include <dynamic_array.h>
#include <management.h>

static dyn_array  lands_arr;

//TODO hacer una funcion serializar()
//TODO guardar en archivo .csv o .dat
void check_lands() {// Comprueba el estado de un terreno en concreto
 int i;
    for(i = 0;i < lands_arr.size ;i++) {
        Terrain* terr_ptr = (Terrain*) get_elem(lands_arr,i);
        printf("\n__________ TERRENO %i __________\n",i+1);
        print_terrain(*terr_ptr);


    }
}

void buy_lands(Terrain terr){
    // 1. Registra un nuevo terreno como nuestro
    // 2. Agrega al archivo de balance.dat el coste (management.c)
   Terrain* terr_ptr = (Terrain*) malloc(sizeof (Terrain));
   *terr_ptr = terr;
   //Guardado en memoria
    add_elem(&lands_arr,terr_ptr);
   //Guardado en archivo
    register_expense(terr.cost);
}

void sell_lands(int i){
    // 1. Desregistra un terreno como nuestro
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
   // TODO 2. Agrega al archivo de balance.dat el beneficio (management.c)
}
void print_terrain(Terrain terr){
    printf("Nombre: %s\n",terr.name);
    printf("Área: %.2f\n",terr.area);
    printf("Comprado por: %.2f\n",terr.cost);
    printf("Uso: %s \n",terr.in_use ? "Cultivos" : "Animales");
}
