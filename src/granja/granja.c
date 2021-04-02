#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "animales.h"
#include "alimentos.h"
#include "cultivos.h"
#include "terrenos.h"
#include "gestion/gestion.h"

#define MAX_BUFFER_SIZE 10

void farm_menu() {
  setup_console();
  
  char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto

  while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "\n------- GRANJA -------\n\n"); // Ejemplo de salida de texto con color
    printf("1. Animales\n");
    printf("2. Cultivos\n");
    printf("3. Terrenos\n");
    printf("4. Gestión económica \n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

  if (!strcmp(input_buffer, "1")){
    animals_menu(); // animales.h
    
  }
  else if (!strcmp(input_buffer, "2")){
    crops_menu(); // cultivos.h

  }
  else if (!strcmp(input_buffer, "3")){
    lands_menu(); // terrenos.h

  }
  else if (!strcmp(input_buffer, "4")){
    management_menu(); // ../gestion/gestion.h

  }
  else if (!strcmp(input_buffer, "v")) {
    return;
  }

  }
}



