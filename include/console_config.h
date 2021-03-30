#ifndef CONSOLE_CONFIG_H

    #define CONSOLE_CONFIG_H

    // Códigos de colores ANSI (enumeración -> +1 respecto al valor anterior)

    typedef enum {

        // Color por defecto

        RESET_COLOR, // 0

        // Colores de texto

        DARK_BLACK_TXT = 30,
        DARK_RED_TXT,
        DARK_GREEN_TXT,
        DARK_YELLOW_TXT,
        DARK_BLUE_TXT,
        DARK_MAGENTA_TXT,
        DARK_CYAN_TXT,
        WHITE_TXT,
        DARK_GRAY_TXT = 90,
        LIGHT_RED_TXT,
        LIGHT_GREEN_TXT,
        LIGHT_YELLOW_TXT,
        LIGHT_BLUE_TXT,
        LIGHT_MAGENTA_TXT,
        LIGHT_CYAN_TXT

    } ANSI_COLOR;

    // FUNCIONES DE UTILIDAD

    // Prepara la consola para que acepte códigos ANSI de colores

    void setup_console();

    void restore_console();

    // Imprime el texto con un color dado

    void printf_c(ANSI_COLOR color, const char* format, ...);

#endif // CONSOLE_CONFIG_H
