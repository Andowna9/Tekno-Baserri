#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include "alimentos.h"
#include "animales.h"
#include <console_config.h>


#define MAX_BUFFER_SIZE 10

void animals_menu() {
  char input_buffer [MAX_BUFFER_SIZE];

  while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "\n------- ANIMALES -------\n\n");
    printf("1. Gestionar comida\n");
    printf("2. Gestionar animales\n");
    
    printf("\nv. Volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")) {
      animal_food_menu(); // alimentos.h
    } 

    else if(!strcmp(input_buffer, "2")) {
      animals_management_menu();
    }
    
    else if (!strcmp(input_buffer, "v")) {
      return;
    }
  }


}

void animals_management_menu(){
  char input_buffer [MAX_BUFFER_SIZE];

  while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "\n------- GESTION ANIMALES -------\n\n");
    printf("1. Consultar animales\n");
    printf("2. Retirar animales\n");
    printf("3. Agregar animales\n");
    printf("4. Vender animales\n");
    printf("5. Comprar animales\n");
    
    printf("\nv. Volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")) {
      check_animals();
    } 

    else if(!strcmp(input_buffer, "2")) {
      remove_animals();
    }
    else if(!strcmp(input_buffer, "3")) {
      add_animals();
    }
    else if(!strcmp(input_buffer, "4")) {
      sell_animals();
    } 
    else if(!strcmp(input_buffer, "5")) {
      buy_animals();
    }       
    else if (!strcmp(input_buffer, "v")) {
      return;
    }
  }
}

void check_animals(){
  //TODO

}

void remove_animals(){
  //TODO

}

void add_animals(){
  //TODO

}

void sell_animals(){
  //TODO

}

void buy_animals(){
  //TODO

}
