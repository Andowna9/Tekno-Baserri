#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "alimentos.h"

#define MAX_BUFFER_SIZE 10

void menuAlimentos() {
  char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto

  while (1) {
    printf_c(DARK_CYAN_TXT, "\n------- ALIMENTOS -------\n\n");
    printf("1. Consultar alimentos\n");
    printf("2. Añadir alimentos \n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")){
      consultarAlimentos();
      
    }
    else if (!strcmp(input_buffer, "2")){
      comprarAlimentos();

    }
    else if (!strcmp(input_buffer, "v")) {
      return;
    }

  }
}

void consultarAlimentos(){
  // TODO
}

void comprarAlimentos(){
  // TODO
}
