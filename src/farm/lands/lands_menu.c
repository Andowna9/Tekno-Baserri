#include <stdio.h>
#include <stdbool.h>
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
    printf("3. Listar terrenos.\n");


    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    if (!strcmp(input_buffer, "1")) {

        Terrain terr;

        terr.name = read_str("Nombre: ");

        terr.area = read_float("Aréa: ");

        if (confirm_action("Terreno de cultivo?")) {

            terr.in_use = true;
        }

        else {

            terr.in_use = false;
        }

        terr.cost = read_float("Precio Pagado: ");

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
