#ifndef STDIN_FIX_H
#define STDIN_FIX_H

#define DEFAULT_BUFFER_SIZE 10 // Tamaño por defecto para el buffer de caracteres

void clear_stdin();
void clean_buffer(char* buffer);
void scan_str(char* buffer, int buffer_size);

// Lectura de datos concretos
char* read_str(const char* message);
int read_int(const char* message);
float read_float(const char* message);

// Confirmación del usuario
int confirm_action(const char* message);

// Esperar hasta entrada de usuario
void press_to_continue();

#endif
