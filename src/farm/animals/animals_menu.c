#include <stdio.h>
#include <string.h>
#include <std_utils.h>
#include "food/food_menu.h"
#include "animals_menu.h"
#include "animal/animals_management.h"
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

      animal_food_menu();

    } else if(strcmp(input_buffer, "2") == 0) {

      animals_management_menu();

    }

    else { printf("Opción incorrecta!\n\n"); press_to_continue();}

  }


}
