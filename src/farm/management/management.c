#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdin_fix.h>
#include <console_config.h>

static float values[2]; // array común a los dos métodos (y a todo el file, así ahorramos memoria)

void read_from_ledger() {

  FILE* fp = fopen("balance.dat", "rb");

  if (fp == NULL){

    return;

  }

  fread(values, sizeof(float), 2, fp);
  fclose(fp);

}

void write_to_ledger() {

  FILE* fp = fopen("balance.dat", "wb");

  if (fp == NULL){

    return;
  }

  fwrite(values, sizeof(float), 2, fp);
  fclose(fp);

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
  int value = values[0];
  return value;

}

// Comprueba gastos

float check_expenses() {

  read_from_ledger();
  int value = values[1];
  return value;

}
