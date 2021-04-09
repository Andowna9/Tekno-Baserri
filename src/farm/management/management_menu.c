#include <stdio.h>
#include <string.h>
#include <stdin_fix.h>
#include <management.h>
#include <console_config.h>

void management_menu(){

    char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

    while (1) {

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- GESTIÓN ECONÓMICA -------\n\n");
    printf("1. Consultar ingresos.\n");
    printf("2. Consultar gastos.\n");
    printf("3. Consultar balance general.\n");

    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");

    scan_str(input_buffer, sizeof(input_buffer));
    putchar('\n');

    // Volver

    if (strcmp(input_buffer, "v") == 0 || strcmp(input_buffer, "V") == 0) {

        break;
    }

    // Comprobar ingresos

    else if (strcmp(input_buffer, "1") == 0) {

      printf("Ingresos: %.2f €\n", check_profit());

    }

    // Comprobar gastos

    else if (strcmp(input_buffer, "2") == 0) {

       printf("Gastos: %.2f €\n", check_expenses());

    }

    // Comprobar todo

    else if (strcmp(input_buffer, "3") == 0) {

      float expenses = check_expenses();
      float profit = check_profit();
      printf_c(LIGHT_MAGENTA_TXT, "- TOTAL ----------------------\n\n");
      printf_c(LIGHT_GREEN_TXT,"Ingresos: %.2f €\n", profit);
      printf_c(LIGHT_RED_TXT, "Gastos: %.2f €\n", expenses);
      printf_c(LIGHT_CYAN_TXT, "\nTotal: %.2f €\n", profit - expenses);
      printf_c(LIGHT_MAGENTA_TXT, "\n-----------------------------\n");

    }

    else { printf("Opción no válida!\n"); }

    putchar('\n');
    press_to_continue();

  }


}
