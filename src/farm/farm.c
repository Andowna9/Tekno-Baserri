#include <stdio.h>
#include <string.h>
#include <std_utils.h>
#include <console_config.h>
#include "animals/animals_menu.h"
#include "crops/crops.h"
#include "lands/lands_menu.h"
#include "management/management_menu.h"

void farm_menu() {
  
  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while (1) {

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- GRANJA -------\n\n"); // Ejemplo de salida de texto con color
    printf("1. Animales.\n");
    printf("2. Cultivos.\n");
    printf("3. Terrenos.\n");
    printf("4. Gestión económica.\n");
    
    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    putchar('\n');

  if (strcmp(input_buffer, "v") == 0 || strcmp(input_buffer, "V") == 0) {

      break;
  }

  if (strcmp(input_buffer, "1") == 0){

      animals_menu();

  } else if (strcmp(input_buffer, "2") == 0){

    crops_menu();

  } else if (strcmp(input_buffer, "3") == 0){

    lands_menu();


  } else if (strcmp(input_buffer, "4") == 0){

    management_menu();

  }

  else { printf("Opción no válida!\n\n"); press_to_continue();}

  }
}



