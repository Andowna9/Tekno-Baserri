#ifdef _WIN32
    #include <windows.h> // Si la compilación es en Windows incluimos un header para configurar la consola
#endif

#include <stdio.h>
#include <stdarg.h>
#include "console_config.h"

#ifdef _WIN32

    // Algunas distribuciones de MinGW no lo definen
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif

    // Variables globales (en memoria mientras el programa está en ejecución)
    // También son estáticas para que no se puden usar fuera del fichero actual
    // Importantes porque guardan la configuración inicial de la consola!

    static UINT oldCp;
    static HANDLE hOut;
    static DWORD dwModeInit;

    void setup_console() {

        // ENCODING UTF-8

        // Gurdado de encoding inicial

        oldCp = GetConsoleOutputCP();

        SetConsoleOutputCP(CP_UTF8);

        // SALIDA PARA TERMINALES VIRTUALES

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        if (hOut == INVALID_HANDLE_VALUE) {
               exit(GetLastError());
        }

        DWORD dwMode = 0;

        if (!GetConsoleMode(hOut, &dwMode)) {
               exit(GetLastError());
           }

        // Guardado de modo inicial

        dwModeInit = dwMode;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        if (!SetConsoleMode(hOut, dwMode)) {
               exit(GetLastError());
           }
    }

    // Devolvemos la configuración de la consola a su estado original al finalizar la ejecución

    void restore_console() {

        // Vuelta al encoding inicial

        SetConsoleOutputCP(oldCp);

        // Vuelta al modo de consola inicial

        if(!SetConsoleMode(hOut, dwModeInit)) {
            exit(GetLastError());
        }
    }


 #else // En sistemas operativos Unix-like (Linux y MacOS) no es necearia una configuración previa
    void setup_console() {}
    void restore_console() {}
 #endif

 // Implementación de funciones para todas las plataformas

 void printf_c(ANSI_COLOR color, const char* format, ...) {

     // Color de texto proporcionado
     printf("\x1b[%dm", color);
     // Se recorre la lista indefinida de argumentos (código que printf() utiliza internamente)
     va_list argptr;
     va_start(argptr, format);
     vfprintf(stdout, format, argptr);
     va_end(argptr);
     // Una vez imprimido el texto, se establece de nuevo el color por defecto
     printf("\x1b[%dm", RESET_COLOR);

 }
