#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>
#include "gestion.h"

#define MAX_BUFFER_SIZE 10

float dinero = 0;
void inicializarValores();

void menuGestion(){
    char input_buffer [MAX_BUFFER_SIZE]; // Buffer de lectura por defecto


    while (1) {
    printf_c(DARK_CYAN_TXT, "\n------- GESTION -------\n");
    printf("1. Consultar ingresos\n");
    printf("2. Consultar gastos\n");
    printf("3. Consultar beneficios \n");
    printf("4. Consultar balance general \n");
    
    printf("\nv. volver\n");

    printf("Input: ");
    fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(input_buffer);

    if (!strcmp(input_buffer, "1")){
      printf("[ Neto: %i ]\n", consultarIngresos());
      
    }
    else if (!strcmp(input_buffer, "2")){
      printf("[ Gastos: %i ]\n", consultarGastos());

    }
    else if (!strcmp(input_buffer, "3")){
      printf("[ Beneficios: %i ]\n", consultarBeneficios());

    }
    else if (!strcmp(input_buffer, "4")){
      printf("[ Neto: %i ]\n", consultarIngresos());
      printf("[ Gastos: %i ]\n", consultarGastos());
      printf("[ Beneficios: %i ]\n", consultarBeneficios());
      
    }    
    else if (!strcmp(input_buffer, "v")) {
      return;
    }

    else if(!strcmp(input_buffer, "i")) {
      inicializarValores();
    }

  }


}

int consultarIngresos() {
  int* valores = leerFicheroDinero();
  int valor = valores[0];
  free(valores);
  return valor;
}

int consultarGastos() {
  int* valores = leerFicheroDinero();
  int valor = valores[2];
  free(valores);
  return valor;
}

int consultarBeneficios() {
  int* valores = leerFicheroDinero();
  int valor = valores[1];
  free(valores);
  return valor;
}

void inicializarValores() {
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


void escribirFicheroDinero(int neto, int beneficio, int gasto){
  FILE* file = fopen("balance.dat", "wb");
  
  if (file == NULL){
    printf("No se pudo abrir balance.dat\n");
    return;
  }

  int valores[3] = {neto, beneficio, gasto};
  fwrite(valores, sizeof(int), 3, file);
  fclose(file);
  
}

int* leerFicheroDinero() {
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
