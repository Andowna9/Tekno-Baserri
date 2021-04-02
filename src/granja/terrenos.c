#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <stdin_fix.h>
#include "terrenos.h"

#define MAX_BUFFER_SIZE 10

void lands_menu() {

  char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto

  while(1){
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "\n------- TERRENOS -------\n\n");
    printf("1. Comprar terrerno\n");
    printf("2. Vender terreno\n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")) {
    buy_lands();
    }

    else if(!strcmp(input_buffer, "2")) {
      sell_lands();
    }

    else if(!strcmp(input_buffer, "v")) {
      return;
    }
  }
}

void check_lands() {
    // Comprueba el estado de un terreno en concreto
}

void buy_lands(){
    // Registra un nuevo terreno como nuestro
    // Agrega al archivo de balance.dat el coste (gestion.c)

}

void sell_lands(){
    // Desregistra un terreno como nuestro
    // Agrega al archivo de balance.dat el beneficio (gestion.c)
}
