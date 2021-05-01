// consultas animales

extern "C" {

#include <std_utils.h>
#include <stdio.h>
#include <console_config.h>
#include <string.h>
}

#include <iostream>
using namespace std;

// TODO Funcionalidades

void check_animals() {

}

void remove_animals() {

}

void add_animals() {

}

void sell_animals() {

}

void buy_animals() {

}

extern "C" void animals_management_menu(){

  char input_buffer [DEFAULT_BUFFER_SIZE];

  while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- GESTIÓN ANIMALES -------\n\n");
    printf("1. Consultar animales.\n");
    printf("2. Retirar animales.\n");
    printf("3. Agregar animales.\n");
    printf("4. Vender animales.\n");
    printf("5. Comprar animales.\n");

    printf("\nIntroduce 'v' para volver\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));
    putchar('\n');

    if (strcmp(input_buffer, "v") == 0 || strcmp(input_buffer, "V") == 0) {
        break;
    }

    if (strcmp(input_buffer, "1") == 0) {
      check_animals();


    }

    else if(strcmp(input_buffer, "2") == 0) {
      remove_animals();


    }

    else if(strcmp(input_buffer, "3") == 0) {
      add_animals();


    }

    else if(strcmp(input_buffer, "4") == 0) {
      sell_animals();


    }

    else if(strcmp(input_buffer, "5") == 0) {
      buy_animals();

    }

    else printf("Opción no disponible!\n");

    putchar('\n');
    press_to_continue();
  }
}

