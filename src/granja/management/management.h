#ifndef MANAGEMENT_H
#define MANAGEMENT_H

// Menú
void management_menu();

// Funciones públicas
int check_income();
int check_expenses();
int check_benefits();
void register_profit(int profit);
void register_expense(int expense);

// Funciones privadas (escribir sobre el fichero)
void write_to_ledger(int neto, int beneficio, int gasto);
int* read_from_ledger();
void initializate_values();

#endif
