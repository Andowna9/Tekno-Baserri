#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <std_utils.h>
#include <console_config.h>

static float values[2]; // array común a los dos métodos (y a todo el file, así ahorramos memoria)

void read_from_ledger() {

  FILE* balance_file = fopen("balance.dat", "rb");

  if (balance_file == NULL) {
      printf_c(LIGHT_RED_TXT, "No existen datos aún para leer.\n");
      return;
  }

  fread(values, sizeof(float), 2, balance_file);
  fclose(balance_file);

}

void write_to_ledger() {

  FILE* balance_file = fopen("balance.dat", "wb");

  if (balance_file == NULL) {
    printf_c(LIGHT_RED_TXT, "Fichero no encontrado, creando nuevo.\n");
    return;
  }

  fwrite(values, sizeof(float), 2, balance_file);
  fclose(balance_file);

}

void reset_ledger() {
    values[0] = 0;
    values[1] = 0;

    write_to_ledger();
}

// Registra los beneficios

void register_profit(float profit) {
    read_from_ledger();
    values[0] += profit;
    write_to_ledger();
}


// Registra los gastos

void register_expense(float expense) {
    read_from_ledger();
    values[1] += expense;
    write_to_ledger();
}

// Comprueba beneficios

float check_profit() {

  read_from_ledger();
  return values[0];

}

// Comprueba gastos

float check_expenses() {

  read_from_ledger();
  return values[1];

}

float check_total() {
    read_from_ledger();
    return values[0] - values[1];
}
