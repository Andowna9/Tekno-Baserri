#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdin_fix.h"

void clear_stdin(); // Llamar cuando estemos seguros de que una limpieza de stdin es necesaria (si no puede pausar la ejecución esperando input)
void clean_buffer(char* buffer); // Elimina el caracter de nueva línea de un buffer de caracteres (string)

// Definición de funciones

void clear_stdin() {
    char c;
    while((c = getchar()) != '\n'); // Se eliminan caracteres hasta alcanzar el salto de línea
}

void clean_buffer(char* buffer) {

    int pos = strlen(buffer) - 1; // Buscamos el salto de línea en la penúltima posición (la última es '\0')
    if (buffer[pos] == '\n') {
        buffer[pos] = '\0'; // Si existe, se reemplaza por el caracter final
    }

    else {
        clear_stdin(); // Ha habido un overflow, ya que no se ha incluido el salto de línea y es necesaria una limpieza
    }
}

void scan_str(char* buffer) { // Forma segura de leer strings del teclado

    fgets(buffer, MAX_BUFFER_SIZE, stdin);
    clean_buffer(buffer);
}

char* read_str() {

    // Internal buffer scanning

    char buff [MAX_BUFFER_SIZE];

    scan_str(buff);

    char* str = (char*) malloc(sizeof(char) * (strlen(buff) + 1));

    strcpy(str, buff);

    return str;
}

int read_int(const char* message) {

    int ret;

    int n;

    do {

        printf("%s", message);
        ret = scanf("%2d", &n);
        clear_stdin();

    } while(ret != 1);

    return n;
}

// Crea un menú de confirmación en consola
// Devuelve 1 o 0 (true o false) de acuerdo con la elección

int confirm_action(const char* message) {

    char buff [3]; // Con tres caracteres es necesario para saber si se ha introducido únicamente 's/n' y '\0'

    while(1) {

        printf("%s (s/n): ", message);

        scan_str(buff);

        // Sí

        if (strcmp(buff, "s") == 0) {

            return 1;
        }

        // No

        else if (strcmp(buff, "n") == 0) {

            return 0;

        }

        printf("Opción no disponible!\n");

    }

}
