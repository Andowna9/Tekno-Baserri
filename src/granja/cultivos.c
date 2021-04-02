#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "cultivos.h"

#define MAX_BUFFER_SIZE 10

void crops_menu() {
  char input_buffer [MAX_BUFFER_SIZE];
  
  while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "\n------- CULTIVOS -------\n\n");
    printf("1. Consultar terreno\n");
    printf("2. Cambiar cultivos\n");
    printf("3. Cultivar terreno\n");
    printf("4. Retirar terreno\n");
    printf("5. Vender cosecha\n");
    
    printf("\nv. volver\n");
    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);
  
  
    if (!strcmp(input_buffer, "1")){
      check_crops();
    }
    else if (!strcmp(input_buffer, "2")){
      change_crop();
    }    
    else if (!strcmp(input_buffer, "3")){
      seed_lands();
    }
    else if (!strcmp(input_buffer, "4")){
      remove_lands();
    }
    else if (!strcmp(input_buffer, "5")){
      harvest_and_sell();
    }    
    else if (!strcmp(input_buffer, "v")) {
      return;
    }
  }

}


void check_crops(){
    // comprueba qué hay en un terreno en concreto (maíz, trigo, fresas...)

    /*
     * Terreno: x, y
     * Contenido: %tipo de cultivo%
     *
    */
}

void change_crop(){
    // Cambia el cultivo de un terreno (maíz a trigo, por ejemplo)
}

void seed_lands(){
    // Plantar en un terreno vacío
}

void remove_lands(){
    // Desregistra un terreno de nuestra propiedad (retirado por el gobierno, vendido...)
}

void harvest_and_sell(){
    // Recoge la cosecha y la vende
    // Registra un terreno como vacío
    // Registra el beneficio de la venta (gestion.c)
  
}
