#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "management.h"

#define MAX_BUFFER_SIZE 10

float dinero = 0;
void initializate_values();

void management_menu(){
    char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto


    while (1) {
    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- GESTION -------\n\n");
    printf("1. Consultar ingresos\n");
    printf("2. Consultar beneficios \n");
    printf("3. Consultar gastos\n");
    printf("4. Consultar balance general \n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);
    putchar('\n');

    if (!strcmp(input_buffer, "1")){
      printf("[ Neto: %i ]\n", check_income());
      

    } else if (!strcmp(input_buffer, "2")){
     printf("[ Beneficios: %i ]\n", check_benefits());


    } else if (!strcmp(input_buffer, "3")){
       printf("[ Gastos: %i ]\n", check_expenses());


    } else if (!strcmp(input_buffer, "4")){
      printf("[ Neto: %i ]\n", check_income());
      printf("[ Beneficios: %i ]\n", check_benefits());
      printf("[ Gastos: %i ]\n", check_expenses());

      

    } else if (!strcmp(input_buffer, "v")) {
      break;


    } else if(!strcmp(input_buffer, "i")) { // funcionalidad oculta
      initializate_values();

    } else { printf("Opción no válida!\n"); }

    putchar('\n');
    press_to_continue();

  }


}

static int valores[3]; // array común a los dos métodos (y a todo el file, así ahorramos memoria)
// Funciones recomendadas
int check_income() {
  read_from_ledger(); // actualizamos el contenido del array valores. Como es común al file no hace falta recoger el puntero de retorno. Si fuera externo sí.
  int valor = valores[0];
  return valor;
}

int check_benefits() {
  read_from_ledger(); // actualizamos el contenido del array valores
  int valor = valores[1];
  return valor;
}

int check_expenses() {
  read_from_ledger(); // actualizamos el contenido del array valores
  int valor = valores[2];
  return valor;
}

void register_expense(int expense) {
    read_from_ledger();
    valores[2] += expense;
    write_to_ledger(valores[0], valores[1], valores[2]);
}

void register_profit(int profit) {
    read_from_ledger();
    valores[1] += profit;
    write_to_ledger(valores[0], valores[1], valores[2]);
}

// endof funciones recomendadas

void initializate_values() {

    printf("Primer valor: ");
    scanf(" %10i", valores);
    printf("Segundo valor: ");
    scanf(" %10i", valores + 1);
    printf("Tercer valor:");
    scanf(" %10i", valores + 2);
    clear_stdin();

    write_to_ledger(valores[0], valores[1], valores[2]);
}


void write_to_ledger(int neto, int beneficio, int gasto) {
  FILE* file = fopen("balance.dat", "wb");
  
  if (file == NULL){
    printf_c(LIGHT_RED_TXT, "No se pudo abrir balance.dat\n");
    return;
  }

  valores[0] = neto;
  valores[1] = beneficio;
  valores[2] = gasto;
  fwrite(valores, sizeof(int), 3, file);
  fclose(file);
  
}

int* read_from_ledger() {
  FILE* file = fopen("balance.dat", "rb");

  if (file == NULL){
    printf("No se pudo abrir balance.dat\n");
    return NULL;
  }

  fread(valores, sizeof(int), 3, file);
  fclose(file);

  return valores;
}
