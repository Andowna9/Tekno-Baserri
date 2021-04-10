#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "stdin_fix.h"
#include <console_config.h>

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

void scan_str(char* buffer, int buffer_size) { // Forma segura de leer strings del teclado

    fgets(buffer, buffer_size, stdin);
    clean_buffer(buffer);
}

int read_format(const char* format, ...) {

    char buff [DEFAULT_BUFFER_SIZE];

    scan_str(buff, sizeof(buff));

    va_list args;

    va_start(args, format);

    int matches = vsscanf(buff, format, args);

    va_end(args);

    return matches;

}

char* read_str(const char* message) {

    // Internal buffer scanning

    char buff [DEFAULT_BUFFER_SIZE];
    printf("%s", message);
    scan_str(buff, sizeof(buff));

    while(buff[0] == '\0') {
        printf_c(LIGHT_YELLOW_TXT, "\nLa entrada está vacía.\n\n");
        printf("%s", message);
        scan_str(buff, sizeof(buff));
    }

    char* str = (char*) malloc(sizeof(char) * (strlen(buff) + 1));

    strcpy(str, buff);

    return str;
}

int read_int(const char* message) {

    int ret;

    int n;

    do {

        printf("%s", message);
        ret = read_format("%2d", &n);

    } while(ret != 1);

    return n;
}

float read_float(const char* message) {

    int ret;

    float f;

    do {

        printf("%s", message);
        ret = read_format("%f", &f);

    } while(ret != 1);

    return f;
}


// Crea un menú de confirmación en consola
// Devuelve 1 o 0 (true o false) de acuerdo con la elección

int confirm_action(const char* message) {

    char buff [3]; // Con tres caracteres es necesario para saber si se ha introducido únicamente 's/n' y '\0'

    while(1) {

        printf_c(LIGHT_YELLOW_TXT, "%s (s/n): ", message);
        scan_str(buff, sizeof(buff));

        // Sí
        if (strcmp(buff, "s") == 0 || strcmp(buff, "S") == 0) {
            return 1;
        }

        // No
        else if (strcmp(buff, "n") == 0 || strcmp(buff, "N") == 0) {
            return 0;

        }

        printf("Opción no disponible!\n");

    }

}

int choose_option(const char* message, int num_options, ...) {

    char buff [DEFAULT_BUFFER_SIZE];

    va_list args;

    int selected;

    int loop = 1;

    while(loop) {

        printf("%s", message);

        scan_str(buff, sizeof(buff));

        va_start(args, num_options);

        int i;

        for (i = 0; i < num_options; i++) {

            const char* option = va_arg(args, const char*);

            if (strcmp(buff, option)) {

                selected = i + 1;

                loop = 0;

                break;
            }
        }

        va_end(args);

        putchar('\n');
    }

    return selected;

}

void press_to_continue() {
    printf_c(LIGHT_YELLOW_TXT, "Pulsa intro para continuar...");
    clear_stdin(); // Con hacer un clear es suficiente, ya que se encargará de pedir input y limpiar hasta encontrar el '\n'
}

void align_title_to_center(char* title) {
    // hay 33 guiones (-) en la barra de abajo
    // en el nuestro 2 son espacios (=31),
    // el centro es nuestro título (31 - len)
    // le resto 1 porque se ve mejor así

    int len = strlen(title);
    if (strcmp(title, "") == 0) { // Si el título está vacío
        printf_c(LIGHT_MAGENTA_TXT, "---------------------------------");


    } else if (len >= 31) { // Si excede nuestro límite de la barra de abajo
        printf_c(LIGHT_MAGENTA_TXT, "- %s -", title);


    } else {
        int i;
        for (i = 0; i < ((31 - len)/2)-1; i++) {
            printf_c(LIGHT_MAGENTA_TXT, "-");
        }
        printf_c(LIGHT_MAGENTA_TXT," %s ", title);
        for (i = i + 0; i < 31 - len; i++) { // hasta el final (31 caracteres)
            printf_c(LIGHT_MAGENTA_TXT, "-");
        }
        printf("\n\n");
    }

}

char* format_str(const char* format, ...) {

    va_list args;

    // Obtenemos el número de caracteres que se necesitan para formatear

    va_start(args, format);

    int num_c = vsnprintf(NULL, 0, format, args);

    va_end(args);

    char* f_str = (char*) malloc((num_c + 1) * sizeof(char)); // +1 para '\0'

    // Recorremos de nuevo la lista de argumentos, esta vez pasando el resultado a la zona dinámica reservada

    va_start(args, format);

    vsnprintf(f_str, num_c + 1, format, args);

    va_end(args);

    return f_str;


}
