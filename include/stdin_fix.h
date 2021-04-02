#ifndef STDIN_FIX_H
#define STDIN_FIX_H

#define DEFAULT_BUFFER_SIZE 10 // Tamaño por defecto para el buffer de caracteres

void clear_stdin();
void clean_buffer(char* buffer);
void scan_str(char* buffer, int buffer_size);

// Lectura de datos concretos
char* read_str();
int read_int(const char* message);
int confirm_action(const char* message);

#endif
