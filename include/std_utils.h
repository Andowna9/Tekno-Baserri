/**
 *  @file stdin_fix.h
 *  @brief Funciones para mejorar y facilitar la entrada estándar por teclado
 *
 *  @author Jon Andoni Castillo
 *  @author León Abascal
 *  @bug Desconocidos
*/


#ifndef STDIN_FIX_H
#define STDIN_FIX_H
#include <console_config.h>
#define DEFAULT_BUFFER_SIZE 10 // Tamaño por defecto para el buffer de caracteres

/**
 * @brief Limpia el buffer de entrada de la consola (stdin)
 */
void clear_stdin();

/**
 * @brief Limpia buffer de caracteres leido
 *
 * Elimina salto de línea si existe y caso contrario limpia stdin hasta encontrarlo
 *
 * @param buffer El buffer a limpiar
 */
void clean_buffer(char* buffer);

/**
 * @brief Almacena un string leido de stdin en un buffer
 * @param buffer El buffer donde guardar los caracteres leidos
 * @param buffer_size Tamaño de buffer
 */

void scan_str(char* buffer, int buffer_size);

/**
 * @brief Versión de scanf para cada línea introducida por el usuario
 *
 * Si no encuentra los formatos específicados,
 * no sigue buscando en las líneas sucesivas de forma indefinida.
 *
 */

int read_format(const char* format, ...);

// Lectura de datos concretos

/**
 * @brief Lee un string de stdin
 * @param message Mensaje que mostrar
 * @return char* Puntero a string dinámico (importante liberar cuando no se necesite)
 */
char* read_str(const char* message);

/**
 * @brief Lee un entero de stdin
 * @param message Mensaje que mostrar
 * @return int Entero leido
 */
int read_int(const char* message);

/**
 * @brief Lee un float de stdin
 * @param message Mensaje que mostrar
 * @return float Float leido
 */
float read_float(const char* message);

/**
 * @brief Lanza por consola un mensaje de Sí/No
 * @param message Mensaje de confirmación a mostrar
 * @return 0 = no, 1 = sí
 */
int confirm_action(const char* message);

/**
 * @brief Lanza por consola un mensaje de Sí/No
 * @param message Mensaje que se muestra al usuario
 * @param num_options Número de opciones
 * @param ... Opciones ordenadas (formato string)
 * @return Entero >= 1 que representa el número de opción
 */
int choose_option(const char* message, int num_options, ...);

/**
 * @brief Espera a un enter del usario para continuar
 *
 * Muestra el mensaje "Pulsa intro para continuar..."
 * Es un putchar, así que al puslar enter/intro escapa.
 *
 */
void press_to_continue();


// Funciones para imprimir títulos y demás
void print_banner(char filler, int size, ANSI_COLOR color);
void print_title_center(char* title, int size, ANSI_COLOR color, char filler);
void print_title_left(char* title, int size, ANSI_COLOR color, char filler);

char* format_str(const char* format, ...);

#endif
