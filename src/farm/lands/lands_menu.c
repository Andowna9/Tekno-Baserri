#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <console_config.h>
#include <std_utils.h>
#include <dynamic_array.h>
#include "lands.h"


static void clear_and_title() {
    clear_screen(); // Limpiamos pantalla
    print_title_center("TERRENOS", 24, LIGHT_CYAN_TXT, '-');
}

static void clear_and_redraw() {
    clear_and_title();
    print_lands(); // Redibujamos el parking

}

void lands_menu() {

  read_lands();

  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while(1){

    clear_screen();

    print_title_center("TERRENOS", 24, LIGHT_CYAN_TXT, '-');
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

        print_banner('-', 33, LIGHT_CYAN_TXT);

        terr.name = read_str("Nombre: ");
        terr.area = read_float("Aréa (hectáreas): ");

        putchar('\n');

        if (confirm_action("Terreno de cultivo?")) {
            terr.in_use = true;

        } else {
            terr.in_use = false;
        }

        putchar('\n');
        terr.cost = read_float("Precio Pagado (euros): ");

        buy_lands(terr);

    // Vender terreno

    } else if(strcmp(input_buffer, "2") == 0) {

      // Limpiamos
        if (get_lands_arr_size()) {
            printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");

        } else {
            clear_and_redraw();

            // Preguntamos
            int i = read_int("\nID del terreno a vender: ");

            if (land_is_out_of_bounds(i)) {
                printf_c(LIGHT_RED_TXT, "\nÍndice no válido\n");
            } else {
                clear_and_title();
                print_land(i - 1);

                float f = read_float("\nPrecio de venta: ");
                putchar('\n');
                sell_lands(i, f);
            }
        }


    } else if(strcmp(input_buffer,"3") == 0){
        if (get_lands_arr_size()) {
            printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");

        } else {
            clear_and_redraw();
        }

    } else { printf("Opción incorrecta!\n"); }

    putchar('\n');
    press_to_continue();

  }
}
