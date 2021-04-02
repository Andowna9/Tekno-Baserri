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

void menuGranja() {
  setup_console();
  
  char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto

  while (1) {
    printf_c(LIGHT_CYAN_TXT, "\n------- GRANJA -------\n\n"); // Ejemplo de salida de texto con color
    printf("1. Animales\n");
    printf("2. Cultivos\n");
    printf("3. Terrenos\n");
    printf("4. Gestión económica \n");
    
    printf_c(LIGHT_CYAN_TXT, "\nv. volver\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

  if (!strcmp(input_buffer, "1")){
    menuAnimales(); // animales.h
    
  }
  else if (!strcmp(input_buffer, "2")){
    menuCultivos(); // cultivos.h

  }
  else if (!strcmp(input_buffer, "3")){
    menuTerrenos(); // terrenos.h

  }
  else if (!strcmp(input_buffer, "4")){
    menuGestion(); // ../gestion/gestion.h

  }
  else if (!strcmp(input_buffer, "v")) {
    return;
  }

  }
}



