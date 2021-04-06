/**
 *  @file console_config.h
 *  @brief Funciones para el output por consola
 *
 *  @author Jon Andoni Castillo
 *  @author León Abascal
 *  @bug Desconocidos
*/

#ifndef CONSOLE_CONFIG_H

    #define CONSOLE_CONFIG_H

    // Códigos de colores ANSI (enumeración -> +1 respecto al valor anterior)

    typedef enum {

        // Color por defecto

        RESET_COLOR, // 0
        UNDERLINE = 4,
        UNDERLINE_OFF = 24,

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

    /**
     * @brief Prepara la consola para que acepte códigos ANSI de colores
     *
     * La llamamos al principio del todo para que la consola sea capaz
     * de asimilar los colores ANSI y podamos usar la función printf_c
     * Para revertir este efecto hay que llamar a restore_console al
     * final del programa.
     *
     */
    void setup_console();

    /**
     * @brief Devuelve la consola a su configuración previa
     *
     * La llamamos después de setup_console, al final del programa
     */
    void restore_console();

    // Imprime el texto con un color dado
    /**
     * @brief Imprime por consola un mensaje, pero se formatea para que tenga color
     *
     * Permite formato como en printf con los argumentos variables.
     * Existe opción de que color sea subrayado (UNDERLINE) pero hay
     * que hacer saltos de línea en otro buffer para romperlo.
     *
     * @param color Puede ser un color de nuestra enum o puede ser sus valores en ANSI.
     * @param format Mensaje a mostrar con dicho color.
     */
    void printf_c(ANSI_COLOR color, const char* format, ...);

    // Limpia la pantalla (funciona en Linux y Windows (32 y 64), en otros OS la funcionalidad es nula)
    /**
     * @brief Limpia la pantalla
     *
     * Funciona para Linux y Windows (32 y 64 bits) como se espera
     * Para SO desconocidos, tiraremos un putchar('\n')
     */
    void clear_screen();


    // Imprime por pantalla todos los colores de consola posibles
    /**
     * @brief Imprime por consola los colores disponibles
     *        con sus respectivos números ANSI.
     *
     * Los colores son los estándar de ASNI para nuestro printf_c.
     * Este método es de muestra.
     */
    void test_nums_printf_c();

    /**
     * @brief Imprime por consola los colores disponibles
     *        con sus respectivos nombres
     *
     * Los colores son los estándar de ASNI para nuestro printf_c.
     * Este método es de muestra.
     */
    void test_each_printf_c();

#endif // CONSOLE_CONFIG_H
