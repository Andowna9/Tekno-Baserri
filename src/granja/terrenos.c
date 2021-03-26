#include <stdio.h>
#include <string.h>
#include "../console/console_config.h"
#include "../fixStdin.h"
#include "terrenos.h"

#define MAX_BUFFER_SIZE 10

void menuTerrenos() {

  char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto

  while(1){
    printf_c(DARK_CYAN_TXT, "\n------- TERRENOS -------\n");
    printf("1. Comprar terrerno\n");
    printf("2. Vender terreno\n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")) {
    comprarTerreno();  
    }

    else if(!strcmp(input_buffer, "2")) {
      venderTerreno();
    }

    else if(!strcmp(input_buffer, "v")) {
      return;
    }
  }
}

void comprarTerreno(){
  //TODO

}

void venderTerreno(){
  //TODO

}