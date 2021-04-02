#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "gestion.h"

#define MAX_BUFFER_SIZE 10

float dinero = 0;
void initializate_values();

void management_menu(){
    char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto


    while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "\n------- GESTION -------\n\n");
    printf("1. Consultar ingresos\n");
    printf("2. Consultar gastos\n");
    printf("3. Consultar beneficios \n");
    printf("4. Consultar balance general \n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")){
      printf("[ Neto: %i ]\n", check_income());
      
    }
    else if (!strcmp(input_buffer, "2")){
      printf("[ Gastos: %i ]\n", check_expenses());

    }
    else if (!strcmp(input_buffer, "3")){
      printf("[ Beneficios: %i ]\n", check_benefits());

    }
    else if (!strcmp(input_buffer, "4")){
      printf("[ Neto: %i ]\n", check_income());
      printf("[ Gastos: %i ]\n", check_expenses());
      printf("[ Beneficios: %i ]\n", check_benefits());
      
    }    
    else if (!strcmp(input_buffer, "v")) {
      return;
    }

    else if(!strcmp(input_buffer, "i")) {
      initializate_values();
    }

  }


}

int check_income() {
  int* valores = read_from_ledger();
  int valor = valores[0];
  free(valores);
  return valor;
}

int check_expenses() {
  int* valores = read_from_ledger();
  int valor = valores[2];
  free(valores);
  return valor;
}

int check_benefits() {
  int* valores = read_from_ledger();
  int valor = valores[1];
  free(valores);
  return valor;
}

void initializate_values() {
  FILE* file = fopen("balance.dat", "wb");

  if (file == NULL) {
    printf("balance.dat\n");
    return;

  }
  
  int valores[3];


  scanf(" %i", valores);
  scanf(" %i", valores + 1);
  scanf(" %i", valores + 2);
  clear_stdin();

  fclose(file);
}


void write_to_ledger(int neto, int beneficio, int gasto){
  FILE* file = fopen("balance.dat", "wb");
  
  if (file == NULL){
    printf_c(LIGHT_RED_TXT, "No se pudo abrir balance.dat\n");
    return;
  }

  int valores[3] = {neto, beneficio, gasto};
  fwrite(valores, sizeof(int), 3, file);
  fclose(file);
  
}

int* read_from_ledger() {
  FILE* file = fopen("balance.dat", "rb");

  if (file == NULL){
    printf("No se pudo abrir balance.dat\n");
    return NULL;
  }

  int* valores = malloc(3 * sizeof(int));
  fread(valores, sizeof(int), 3, file);
  fclose(file);

  return valores;
}
