#include <stdio.h>
#include <string.h>
#include <std_utils.h>
#include "animal_food/food_menu.h"
#include "animals.h"
#include <console_config.h>

void animals_menu() {

  char input_buffer [DEFAULT_BUFFER_SIZE];

  while (1) {

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- ANIMALES -------\n\n");
    printf("1. Gestionar comida.\n");
    printf("2. Gestionar animales.\n");
    
    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    putchar('\n');

    if (strcmp(input_buffer, "v") == 0 || strcmp(input_buffer, "V") == 0 ) {

      break;
    }

    else if (strcmp(input_buffer, "1") == 0) {

      animal_food_menu(); // alimentos.h


    } else if(strcmp(input_buffer, "2") == 0) {

      //animals_management_menu();

      printf("TO BE IMPLEMENTED IN CPP :)\n\n");

      press_to_continue();

    }

    else { printf("Opción incorrecta!\n\n"); press_to_continue();}

  }


}

void animals_management_menu(){
  char input_buffer [DEFAULT_BUFFER_SIZE];

  while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- GESTION ANIMALES -------\n\n");
    printf("1. Consultar animales\n");
    printf("2. Retirar animales\n");
    printf("3. Agregar animales\n");
    printf("4. Vender animales\n");
    printf("5. Comprar animales\n");
    
    printf("\nv. Volver\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    if (!strcmp(input_buffer, "1")) {
      check_animals();


    } else if(!strcmp(input_buffer, "2")) {
      remove_animals();


    } else if(!strcmp(input_buffer, "3")) {
      add_animals();


    } else if(!strcmp(input_buffer, "4")) {
      sell_animals();


    } else if(!strcmp(input_buffer, "5")) {
      buy_animals();


    } else if (!strcmp(input_buffer, "v")) {
      break;
    }

    putchar('\n');
    press_to_continue();
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
