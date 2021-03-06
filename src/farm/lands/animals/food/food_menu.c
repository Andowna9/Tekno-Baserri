#include <stdio.h>
#include <string.h>
#include<std_utils.h>
#include <console_config.h>
#include "food.h"

void print_food_with_clear() {
    clear_screen();
    printf_c(LIGHT_CYAN_TXT, "------- ALIMENTOS -------\n\n");
    check_all_food();
}

void animal_food_menu() {

  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while (1) {

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- ALIMENTOS -------\n\n");
    printf("--- Gestión\n\n");
    printf("1. Registrar alimentos.\n");
    printf("2. Eliminar alimentos.\n");
    printf("3. Comprar alimentos.\n\n");
    printf("--- Consultas\n\n");
    printf("4. Consultar alimentos.\n");
    printf("5. Ordenar alimentos por precio.\n");
    printf("6. Ordenar alimentos por cantidad.\n");
    printf("7. Ordenar alimentos por nombre.\n");


    printf_c(LIGHT_CYAN_TXT, "\nNúmero de alimentos registrados: %d\n", get_food_count());

    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    putchar('\n');

    // Salir

    if (strcmp(input_buffer, "v") == 0) {

      break;

    }

    // Registrar tipo de comida

    else if (strcmp(input_buffer, "1") == 0) {

         print_food_with_clear(); // Limpiamos pantalla

         printf_c(LIGHT_MAGENTA_TXT, "\n--- NUEVO ALIMENTO\n\n");

         char name [DEFAULT_BUFFER_SIZE];
         printf("Nombre: ");
         scan_str(name, sizeof(name));

         float price = read_float("\nPrecio(€/kg): ");

         register_animal_food(name, price, 0);

         printf_c(LIGHT_GREEN_TXT, "\nComida registrada correctamente.\n");


    }

    // Eliminar tipo de comida

    else if (strcmp(input_buffer, "2") == 0){

      int not_empty = get_food_count();
      if (not_empty) {

          print_food_with_clear();
          printf_c(LIGHT_YELLOW_TXT, "[ ID: 0 - Cancelar operación. ]\n\n");
          int id = read_int("ID: ");

          if(id == 0) {
            printf_c(LIGHT_RED_TXT, "\nOperación cancelada.\n");

          } else {
              Animal_Food* ptr = get_food_by_id(id);
              if (ptr == NULL) {
                    printf_c(LIGHT_RED_TXT, "\nEl ID = %d no existe!\n", id);

              }

              else if (ptr->amount != 0) {

                    printf_c(LIGHT_RED_TXT, "\nTodavía hay %.2f kg disponibles\n", ptr->amount);
                    int delete;
                    delete = confirm_action("¿Borrar igualmente?");

                    if (delete) {
                        delete_animal_food(id);
                        printf_c(LIGHT_GREEN_TXT, "\nComida borrada correctamente\n");

                    } else {
                        printf_c(LIGHT_GREEN_TXT, "No se borró la comida del registro.\n");

                    }
              }

              else {

                 delete_animal_food(id);
                 printf_c(LIGHT_GREEN_TXT, "\nComida borrada correctamente.\n");

              }
          }


      } else {
          printf_c(LIGHT_RED_TXT, "No hay comida registrada.\n");

      }


    }

    // Comprar comida

    else if (strcmp(input_buffer, "3") == 0) {

          clear_screen();
          printf_c(LIGHT_CYAN_TXT, "------- ALIMENTOS DE TERCEROS -------\n\n");
          check_third_party_food();
          printf_c(LIGHT_YELLOW_TXT, "[ ID: 0 - Cancelar operación. ]\n\n");
          int id = read_int("ID: ");

          if(id == 0) {
            printf_c(LIGHT_RED_TXT, "\nOperación cancelada.\n");

          } else { // Operación no cancelada
              Animal_Food* ptr = get_food_by_id(id);

              // Comprobamos si es un alimento que no existe o uno que no tiene precio (no se puede comprar)
              if (ptr == NULL || ptr->price == 0) {
                  printf_c(LIGHT_RED_TXT, "\nEl id proporcionado es incorrecto!\n");
              }

              else {
                  float amount = read_float("\nCantidad(kg): ");
                  buy_animal_food(id, amount);
                  printf_c(LIGHT_GREEN_TXT, "\nAlimento comprado correctamente.\n");

              }
          }

    }

    // Comprobar tipos de comida

    else if (strcmp(input_buffer, "4") == 0) {

        int not_empty = get_food_count();
        if (not_empty) {

            print_food_with_clear();

        }

        else {

            printf_c(LIGHT_RED_TXT, "No hay comida registrada.\n");
        }
    }

    // Listado ordenado por precio

    else if (strcmp(input_buffer, "5") == 0) {

        int opt = choose_option("Elige Ascendente(A) o Descendente(D): ", 2, "A", "D");

        check_ordered_food(order_by_price, opt == 1);

        printf_c(LIGHT_GREEN_TXT, "Lista ordenada por precio.\n");

    }

    // Listado ordenado por cantidad

    else if (strcmp(input_buffer, "6") == 0) {

        int opt = choose_option("Elige Ascendente(A) o Descendente(D): ", 2, "A", "D");

        check_ordered_food(order_by_amount, opt == 1);

        printf_c(LIGHT_GREEN_TXT, "Lista ordenada por cantidad.\n");
    }

    // Listado ordenado alfabeticamente por nombre

    else if (strcmp(input_buffer, "7") == 0) {

        check_ordered_food(order_by_amount, true);

        printf_c(LIGHT_GREEN_TXT, "Lista ordenada por nombre.\n");

    }

    else { printf("Opción incorrecta!\n"); }

    putchar('\n');
    press_to_continue();

  }
}
