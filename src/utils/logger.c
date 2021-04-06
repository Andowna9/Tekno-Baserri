#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdin_fix.h>
#include <console_config.h>
#include <string.h>
#include <stdin_fix.h>

#define STACK_SIZE 16

// Variables
static char* log_file_txt;
unsigned char counter = 0;
char* filename_stack[STACK_SIZE];

void set_log_file(char* file_name) {
    if (log_file_txt == NULL) {
        printf_c(LIGHT_RED_TXT, "No existe un logger inicializado.\n");

    }

    log_file_txt = file_name;

}

char* get_log_file_name() {
    if (log_file_txt == NULL) {
        return "N/A";
    }

    return log_file_txt;
}

void add_to_log(char* message, ...) {
    FILE* log_file = fopen(log_file_txt, "a");

    //fprintf(log_file, ""); // TODO aquí irá la hora del log
    // Formateamos el string
    va_list arg;
    va_start (arg, message);
    vfprintf(log_file, message, arg);
    va_end (arg);

    // Escribimos en el fichero
    fputc('\n', log_file);
    fclose(log_file);
}

void read_log(char* title) {
    FILE* log_file = fopen(log_file_txt, "r");

    align_title_to_center(title); //printf_c(LIGHT_MAGENTA_TXT, "------------- %s --------------\n\n", title);

    // content of the log
    char c;
    do {
        c = fgetc(log_file);
        printf_c(LIGHT_MAGENTA_TXT, "%c", c);
    } while (c != EOF);
    printf_c(LIGHT_MAGENTA_TXT, "---------------------------------\n\n");

    fclose(log_file);
}

void clear_log() {
    FILE* log_file = fopen(log_file_txt, "w");
    fclose(log_file);
}

int push_filename() {

    if (counter == STACK_SIZE) { // ya no hay espacio
        printf_c(LIGHT_RED_TXT, "Maximum amount of pushes reached. Need to pop.\n");
        return 0;

    } else if (log_file_txt == NULL) { // no se ha configurado ningún logger
        printf_c(LIGHT_RED_TXT, "Nothing to be pushed. You need to set the log file first.\n");
        return 0;

    } else {
        filename_stack[counter] = log_file_txt;
        counter++;
    }

    return 1;

}

int pop_filename() {

    if (counter == 0) {
        //printf_c(LIGHT_RED_TXT, "Filename stack clean. Can't pop.\n");
        return 0;

    } else {
        counter--;
        log_file_txt = filename_stack[counter];

    }

    return 1;

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
    push_filename();

    printf("Sets logger to programa.log and logs its name\n");
    set_log_file("programa.log");
    add_to_log("[MAIN] This is %s", get_log_file_name());
    read_log("LOG");

    printf("After displaying it, we will clean the file\n\n");
    clear_log();

    printf("Now we pop (should be prog4.log)\n");
    pop_filename();

    printf("Now we introduce a message.\n");
    add_to_log("[%s] I've been popped.", get_log_file_name());

    printf("We show it and then clear the file.\n");
    read_log("LOG");
    clear_log();

    press_to_continue();
}
