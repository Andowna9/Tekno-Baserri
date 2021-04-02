#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "cultivos.h"

#define MAX_BUFFER_SIZE 10

void menuCultivos() {
  char input_buffer [MAX_BUFFER_SIZE];
  
  while (1) {
    printf_c(DARK_CYAN_TXT, "\n------- CULTIVOS -------\n");
    printf("1. Consultar cultivos\n");
    printf("2. Consultar terreno (localización)\n");
    printf("3. Cambiar cultivos\n");
    printf("4. Cultivar terreno\n");
    printf("5. Retirar terreno\n");
    printf("6. Vender cosecha\n");
    
    printf("\nv. volver\n");
    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);
  
  
    if (!strcmp(input_buffer, "1")){
      consultarCultivos();
    }
    else if (!strcmp(input_buffer, "2")){
      consultarTerreno();
    }
    else if (!strcmp(input_buffer, "3")){
      cambiarCultivos();
    }    
    else if (!strcmp(input_buffer, "4")){
      cultivarTerreno();
    }
    else if (!strcmp(input_buffer, "5")){
      retirarTerreno();
    }
    else if (!strcmp(input_buffer, "6")){
      venderCosecha();
    }    
    else if (!strcmp(input_buffer, "v")) {
      return;
    }
  }

}

void consultarCultivos(){
  // TODO
  
}

void consultarTerreno(){
  // TODO

}

void cambiarCultivos(){
  // TODO
  
}

void cultivarTerreno(){
  // TODO
  
}

void retirarTerreno(){
  // TODO
  
}

void venderCosecha(){
  // TODO
  
}
