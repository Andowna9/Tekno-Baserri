#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <std_utils.h>
#include <console_config.h>
#include <string.h>
#include <time.h>
#include <std_utils.h>

#define STACK_SIZE 16

// Variables
static const char* log_file_txt;
unsigned char stack_index = 0;
int num_pushes = 0;
const char* filename_stack[STACK_SIZE];
const char* stack_trace_file = "logger_stack_trace.log";

void set_log_file(const char* file_name) {
    if (log_file_txt == NULL) {
        printf_c(LIGHT_RED_TXT, "No existe un logger inicializado.\n");

    }

    log_file_txt = file_name; // TODO hacer un append de la carpeta

}

const char* get_log_file_name() {
    if (log_file_txt == NULL) {
        return "N/A";
    }

    return log_file_txt;
}

void add_to_log(const char* message, ...) {

    FILE* log_file = fopen(log_file_txt, "a");

    // Hora del log

    time_t rawtime;
    struct tm *info;
    char time_buff [80];

    time(&rawtime);
    info = localtime(&rawtime);
    strftime(time_buff, 80, "%X - %x", info); // Formateo de fecha y hora (%X para la hora y %x para la fecha)


    fprintf(log_file, "| %s | ", time_buff);
    // Formateamos el string
    va_list arg;
    va_start (arg, message);
    vfprintf(log_file, message, arg);
    va_end (arg);

    // Escribimos en el fichero
    fputc('\n', log_file);
    fclose(log_file);
}

void read_log(const char* title) {
    FILE* log_file = fopen(log_file_txt, "r");
    int size = 40;
    int color = LIGHT_MAGENTA_TXT;
    char filler = '-';

    print_title_center(title, size, color, filler);

    // content of the log
    char c;
    do {
        c = fgetc(log_file);
        printf_c(color, "%c", c);

    } while (c != EOF);
    print_banner(filler, size, color);

    fclose(log_file);
}

void clear_log() {
    FILE* log_file = fopen(log_file_txt, "w");
    fclose(log_file);
}

int push_filename() {

    if (stack_index == STACK_SIZE) { // ya no hay espacio
        printf_c(LIGHT_RED_TXT, "Maximum amount of pushes reached. Need to pop.\n");
        return 0;

    } else if (log_file_txt == NULL) { // no se ha configurado ningún logger
        printf_c(LIGHT_RED_TXT, "Nothing to be pushed. You need to set the log file first.\n");
        return 0;

    } else {
        filename_stack[stack_index] = log_file_txt;
        stack_index++;
        return 1;
    }

}

int pop_filename() {

    if (stack_index == 0) {
        //printf_c(LIGHT_RED_TXT, "Filename stack clean. Can't pop.\n");
        return 0;

    } else {
        stack_index--;
        log_file_txt = filename_stack[stack_index];

    }

    return 1;

}

void open_logger(const char* file_name) {
    push_filename();
    set_log_file(file_name);
    num_pushes++;

    // Registro para detectar errores
    FILE* file = fopen(stack_trace_file, "a");

    // formateamos con tabuladores
    int i;
    for(i = 0; i < stack_index; i++) {
        fprintf(file, "\t");
    }

    fprintf(file, "Pusheado %s\n", file_name);
    fclose(file);
}

void close_logger() {
    // Registro para detectar errores
    FILE* file = fopen(stack_trace_file, "a");
    // formateamos con tabuladores
    int i;
    for(i = 0; i < stack_index; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "Popeado %s\n\n", get_log_file_name());
    fclose(file);
    num_pushes--;

    pop_filename();

}

void logger_demo() {
    printf("CHECK THE SOURCE CODE!\n");
    printf("This demo should aid you on having a clear idea of what does each method of this file\n\n");
    printf("Sets logger to prog4.log and logs its name\n");
    set_log_file("prog4.log"); // setting is always required!
    add_to_log("[MAIN] This is: %s", get_log_file_name()); // add_to_log will include the \n, so you don't have to worry
    read_log("LOG");

    printf("Clears and prints (yes, should be empty)\n");
    clear_log();
    read_log("LOG");

    printf("Push prog4.log (we will recover it calling pop)\n"); // push up to STACK_SIZE times (defined at the top of the file)
    // if you wonder why should you be doing this, this is like a "pause" function that allowys you to pause (push) the main log
    // to temporarily use another and resume it later (pop)
    // -main.c [m] ---*log*------> parking.c [pc] ----*log [pc]*----*log [m]*---> main.c -- X
    push_filename(); // open_logger()

    printf("Sets logger to programa.log and logs its name\n");
    set_log_file("programa.log");
    add_to_log("[MAIN] This is %s", get_log_file_name());
    read_log("LOG");

    printf("After displaying it, we will clean the file\n\n");
    clear_log();

    printf("Now we pop (should be prog4.log)\n");
    pop_filename(); //close_logger

    printf("Now we introduce a message.\n");
    add_to_log("[%s] I've been popped.", get_log_file_name());

    printf("We show it and then clear the file.\n");
    read_log("LOG");
    clear_log();

    press_to_continue();
}

int verify_logger_integrity() {

    FILE* file;

    // si el número de pushes es > 0, entonces no se ha popeado el mismo número de veces que pusheado
    // lo cual implica que existe algún logger que no se ha cerrado de forma adecuada.
    if (num_pushes > 0) {

        file = fopen(stack_trace_file, "r");
        char buffer[1024];

        clear_screen();
        printf_c(LIGHT_RED_TXT, "Algún logger no se cerró de forma adecuada.\n\n");

        // Imprimimos la stack trace entera
        int i = 0;
        while(fgets(buffer, 1024, file) != NULL) {
            printf("[ %.3i ] %s", i, buffer);
            i++;
        }

        putchar('\n');
        printf_c(LIGHT_CYAN_TXT, "Número de loggers mal cerrados: %i\n", num_pushes);
        press_to_continue();

        fclose(file);
    }



    // vaciamos el fichero
    file = fopen(stack_trace_file, "w");
    fclose(file);

    return 0;
}
