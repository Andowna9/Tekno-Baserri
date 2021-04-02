#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include "alimentos.h"
#include "animales.h"
#include <console_config.h>


#define MAX_BUFFER_SIZE 10

void menuAnimales() {
  char input_buffer [MAX_BUFFER_SIZE];

  while (1) {
    printf_c(DARK_CYAN_TXT, "\n------- ANIMALES -------\n");     
    printf("1. Gestionar comida\n");
    printf("2. Gestionar animales\n");
    
    printf("\nv. Volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")) {
      menuAlimentos(); // alimentos.h
    } 

    else if(!strcmp(input_buffer, "2")) {
      menuGestionAnimales();
    }
    
    else if (!strcmp(input_buffer, "v")) {
      return;
    }
  }


}

void menuGestionAnimales(){
  char input_buffer [MAX_BUFFER_SIZE];

  while (1) {
    printf_c(DARK_CYAN_TXT, "\n------- GESTION ANIMALES -------\n");     
    printf("1. Consultar animales\n");
    printf("2. Retirar animales\n");
    printf("3. Agregar animales\n");
    printf("4. Vender animales\n");
    printf("5. Comprar animales\n");
    
    printf("\nv. Volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")) {
      consultarAnimales();
    } 

    else if(!strcmp(input_buffer, "2")) {
      retirarAnimales();
    }
    else if(!strcmp(input_buffer, "3")) {
      agregarAnimales();
    }
    else if(!strcmp(input_buffer, "4")) {
      venderAnimales();
    } 
    else if(!strcmp(input_buffer, "5")) {
      comprarAnimales();
    }       
    else if (!strcmp(input_buffer, "v")) {
      return;
    }
  }
}

void consultarAnimales(){
  //TODO

}

void retirarAnimales(){
  //TODO

}

void agregarAnimales(){
  //TODO

}

void venderAnimales(){
  //TODO

}

void comprarAnimales(){
  //TODO

}
