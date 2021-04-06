#ifndef STDIN_FIX_H
#define STDIN_FIX_H

#define DEFAULT_BUFFER_SIZE 10 // Tamaño por defecto para el buffer de caracteres

/**
 * @brief Limpia el buffer de entrada de la consola (stdin)
 */
void clear_stdin();

/**
 * @brief Si estamos usando un buffer que no es stdin, lo limpia
 * @param buffer El buffer a limpiar
 */
void clean_buffer(char* buffer);
void scan_str(char* buffer, int buffer_size);

// Lectura de datos concretos
char* read_str(const char* message);
int read_int(const char* message);
float read_float(const char* message);

/**
 * @brief Lanza por consola un mensaje de Sí/No
 * @param message Mensaje de confirmación a mostrar
 * @return 0 = no, 1 = sí
 */
int confirm_action(const char* message);

/**
 * @brief Espera a un enter del usario para continuar
 *
 * Muestra el mensaje "Pulsa intro para continuar..."
 * Es un putchar, así que al puslar enter/intro escapa.
 *
 */
void press_to_continue();

#endif
