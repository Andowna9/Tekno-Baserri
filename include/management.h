/**
 *  @file management.h
 *  @brief Funciones para gestionar gastos y beneficios
 *
 *  @author Jon Andoni Castillo
 *  @author León Abascal
 *  @bug Desconocidos
*/

#ifndef MANAGEMENT_H
#define MANAGEMENT_H

void reset_ledger();

/**
 * @brief Dado un beneficio, lo registra en el archivo de balance
 *
 * Pensado para usarse cuando se realize una operación que nos
 * dé dinero.
 *
 * @param profit Beneficio de la operación
 */
void register_profit(float profit);

/**
 * @brief Dado un gasto, lo registra en el archivo de balance
 *
 * Pensado para usarse cuando se realize una operación en la
 * que gastemos dinero.
 *
 * @param expense Gasto realizado en la operación
 */
void register_expense(float expense);


/**
 * @brief Nos da el beneficio total (solo positivos)
 *
 * No confundirse con el beneficio neto (beneficio - gasto).
 *
 * @return Regresa beneficio total que hemos acumulado
 */
float check_profit();

/**
 * @brief Nos da el gasto total (solo negativo)
 * @return Regresa gasto total que hemos acumulado
 */
float check_expenses();

#endif
