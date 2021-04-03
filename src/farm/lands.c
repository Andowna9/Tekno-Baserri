#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <stdin_fix.h>
#include "lands.h"

void lands_menu() {

  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while(1){
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- TERRENOS -------\n\n");
    printf("1. Comprar terrerno.\n");
    printf("2. Vender terreno.\n");
    
    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    if (!strcmp(input_buffer, "1")) {
    buy_lands();


    } else if(!strcmp(input_buffer, "2")) {
      sell_lands();


    } else if(!strcmp(input_buffer, "v")) {
      break;
    }

    putchar('\n');
    press_to_continue();

  }
}

void check_lands() {
    // Comprueba el estado de un terreno en concreto
}

void buy_lands(){
    // 1. Registra un nuevo terreno como nuestro
    // 2. Agrega al archivo de balance.dat el coste (management.c)

}

void sell_lands(){
    // 1. Desregistra un terreno como nuestro
    // 2. Agrega al archivo de balance.dat el beneficio (management.c)
}
