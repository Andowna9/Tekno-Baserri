#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <console_config.h>
#include <std_utils.h>
#include <dynamic_array.h>
#include "lands.h"


void lands_menu() {

  read_lands();

  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while(1){

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- TERRENOS -------\n\n");
    printf("1. Comprar terrerno.\n");
    printf("2. Vender terreno.\n");
    printf("3. Listar terrenos.\n");


    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    putchar('\n');

    if(!strcmp(input_buffer, "v")) {

      free_lands_mem();
      break;
    }

    // Comprar terreno

    else if (strcmp(input_buffer, "1") == 0) {

        Terrain terr;

        terr.name = read_str("Nombre: ");

        terr.area = read_float("Aréa (hectáreas): ");

        if (confirm_action("Terreno de cultivo?")) {

            terr.in_use = true;
        }

        else {

            terr.in_use = false;
        }

        terr.cost = read_float("Precio Pagado (euros): ");

        buy_lands(terr);

    // Vender terreno

    } else if(strcmp(input_buffer, "2") == 0) {
      int i = read_int("ID del terreno a vender: ");
      float f = read_float("Precio de venta: ");
      sell_lands(i, f);


    } else if(strcmp(input_buffer,"3") == 0){
        check_lands();
    }

    else { printf("Opción incorrecta!\n"); }

    putchar('\n');
    press_to_continue();

  }
}
