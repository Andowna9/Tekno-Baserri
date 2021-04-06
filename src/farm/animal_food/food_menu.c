#include <stdio.h>
#include <string.h>
#include<stdin_fix.h>
#include <console_config.h>
#include "food.h"

void animal_food_menu() {

  read_food_types();

  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while (1) {

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- ALIMENTOS -------\n\n");
    printf("1. Registrar alimentos.\n");
    printf("2. Eliminar alimentos.\n");
    printf("3. Consultar alimentos.\n");
    printf("4. Comprar alimentos.\n");
    printf("5. Ordenar alimentos por precio.\n");
    printf("6. Ordenar alimentos por cantidad.\n");


    printf("\nNúmero de alimentos registrados: %d\n", get_food_count());

    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    putchar('\n');

    // Salir

    if (strcmp(input_buffer, "v") == 0) {

      free_animal_food_memory();

      break;

    }

    // Registrar tipo de comida

    else if (strcmp(input_buffer, "1") == 0) {

         Animal_Food food;

         food.name = read_str("Nombre: ");

         food.price = read_float("\nPrecio: ");

         register_animal_food(food);

         printf_c(LIGHT_GREEN_TXT, "Comida registrada correctamente\n");

    }

    // Eliminar tipo de comida

    else if (strcmp(input_buffer, "2") == 0){

      int id = read_int("ID: ");

      Animal_Food* ptr = get_food_by_id(id);

      if (ptr == NULL) {

            printf_c(LIGHT_RED_TXT, "El ID = %d no existe!\n", id);

      }

      else if (ptr->amount != 0) {

            printf_c(LIGHT_RED_TXT, "Todavía hay %d kg disponibles\n", ptr->amount);
      }

      else {

         delete_animal_food(id);

         printf_c(LIGHT_GREEN_TXT, "Comida borrada correctamente\n");

      }

    }

    // Comprobar tipos de comida

    else if (strcmp(input_buffer, "3") == 0) {

        check_animal_food();
    }

    // Comprar comida

    else if (strcmp(input_buffer, "4") == 0) {

      int id = read_int("ID: ");

      float amount = read_float("Cantidad: ");

      int ret = buy_animal_food(id, amount);

      if (ret != 0) {

            printf_c(LIGHT_RED_TXT, "El alimento con ID = %d no existe!\n", id);
      }

      else {

          printf_c(LIGHT_GREEN_TXT, "Alimento comprado correctamente\n");
      }

    }

    // Listado ordenado por precio

    else if (strcmp(input_buffer, "5") == 0) {

        int opt = choose_option("Elige Ascendente(A) o Descendente(D): ", 2, "A", "B");

        check_ordered_food(order_by_price, opt == 1);

        printf_c(LIGHT_GREEN_TXT, "Lista ordenada correctamente por precio");

    }

    // Listado ordenado por cantidad

    else if (strcmp(input_buffer, "6") == 0) {

        int opt = choose_option("Elige Ascendente(A) o Descendente(D): ", 2, "A", "B");

        check_ordered_food(order_by_amount, opt == 1);

        printf_c(LIGHT_GREEN_TXT, "Lista ordenada correctamente por cantidad");
    }

    else { printf("Opción incorrecta!\n"); }

    putchar('\n');
    press_to_continue();

  }
}
