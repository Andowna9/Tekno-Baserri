#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "animals.h"
#include "crops.h"
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

  if (!strcmp(input_buffer, "1")){

    //animals_menu(); // TODO - CPP

      printf("\nTO BE IMPLEMENTED IN CPP :)\n\n");
    

  } else if (!strcmp(input_buffer, "2")){

    //crops_menu(); // TODO - CPP

    printf("\nTO BE IMPLEMENTED IN CPP :)\n\n");


  } else if (!strcmp(input_buffer, "3")){
    lands_menu();


  } else if (!strcmp(input_buffer, "4")){
    management_menu();


  } else if (!strcmp(input_buffer, "v")) {
      break;
  }

  press_to_continue();

  }
}



