#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "animal_food.h"


void animal_food_menu() {
  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- ALIMENTOS -------\n\n");
    printf("1. Consultar alimentos\n");
    printf("2. Añadir alimentos \n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    if (!strcmp(input_buffer, "1")){
      check_animal_food();
      
    }
    else if (!strcmp(input_buffer, "2")){
      buy_animal_food();

    }
    else if (!strcmp(input_buffer, "v")) {
      break;
    }

    putchar('\n');
    press_to_continue();

  }
}

void check_animal_food(){
  // TODO
}

void buy_animal_food(){
  // TODO
}
