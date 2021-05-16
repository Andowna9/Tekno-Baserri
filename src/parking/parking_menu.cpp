extern "C" {

    #include <std_utils.h>
    #include <console_config.h>
    #include "parking.h"
    #include <logger.h>
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>

#include <iostream>
#include <DBManager.h>
#include <QCryptographicHash>

using namespace std;

// Variables del file
bool save_needed;
static const char* log_file_txt = "parking_saves.log";

// Función para pedir por teclado la plaza
void scan_p_plot(int* row_ptr, int* col_ptr) {

    int ret;

    char row;
    int column;

    do {

        printf("Letra y Número. Ejemplo: A3\n");
        printf("Plaza: ");
        ret = read_format("%c%2d", &row, &column);

    } while(ret != 2);

    // A partir de los datos del usuario se obtienen la fila y columna como enteros

    *row_ptr = toupper(row) - 'A';
    *col_ptr = column - 1;

}


// Pide al usuario datos para determinar la configuración del parking
void scan_parking() {

    int w = 0;   // Altura y anchura (filas y columnas)
    int h = 0;
    int ret;

    while(1) {

        do {

            printf("Tamaño (filas, columnas): ");
            ret = read_format("%2d, %2d", &h, &w);

            // printf("%i %i,",h,w);
            // Comprobación de que el tamaño no se sale de los límites establecidos

            if (h > MAX_ROWS || w > MAX_COLS) {

                printf_c(LIGHT_RED_TXT, "Máximo número de filas/columnas superado!\n");

                ret = 0;
            }

            if (h < 0 || w < 0) {

                printf_c(LIGHT_RED_TXT, "No se aceptan números negativos!\n");

                ret = 0;
            }

            if (h == 0 || w == 0) {
                printf_c(LIGHT_RED_TXT, "No se aceptan filas/columnas nulas!\n");

                ret = 0;
            }

        } while(ret != 2);

        putchar('\n');
        printf("Número de aparcamientos posibles: %d\n", w * h);

        if (confirm_action("¿Desea continuar?")) {

            create_parking(h, w); // Creación de parking en memoria
            add_to_log("Creado parking");
            save_needed = true;
            putchar('\n');

            break;

        }

        putchar('\n');

    }


}

// Inicializa el parking a partir de fichero de texto si existe

void init_parking() {

    if (load_parking() != -1) {

        printf_c(LIGHT_MAGENTA_TXT, "Configuración encontrada!\n\n");
    }

    else {

        // Si no hay una configuarción de parking registrada

        printf_c(LIGHT_MAGENTA_TXT, "No hay ningún parking registrado.\n\n");

        scan_parking();

    }

    press_to_continue();

}

// Métodos para dibujar el parking de cero
static void clear_and_redraw() {
    clear_screen(); // Limpiamos pantalla
    print_title_center("PARKING", 24, LIGHT_MAGENTA_TXT, '-');
    printf("\n\n");
    print_parking(); // Redibujamos el parking
}

static void clear_redraw_and_highlight(int r, int c) {
    set_highlighted_point(r, c); // Destacamos el punto
    clear_and_redraw();
    reset_highlighted_point(); // Dejamos de destacar
}
// endof Métodos para dibujar el parking de cero


// MENÚS (MODULARIZADOS)
// Menú 1. Introducir vehículo.
void insert_vehicle_op() {
    int r, c;
    scan_p_plot(&r, &c);

    if (!out_of_bounds(r, c)) {

        // Limpiamos y redibujamos para destacar el punto
        clear_redraw_and_highlight(r, c);

        if (vehicle_inside(r, c)) {
            printf_c(LIGHT_RED_TXT, "La plaza ya está ocupada.\n");

        } else {
            char* l_plate = read_str("Matrícula: ");

            if (!DBManager::isVehicleRegistered(l_plate)) {
                printf_c(LIGHT_RED_TXT, "\nEl vehículo no tiene acceso al parking");

            } else {
                // Confirmamos que quiera guardar
                int save = confirm_action("Aparcar coche?");

                if (save) {
                    int parked = insert_vehicle(l_plate, r, c);
                    if (parked) {
                        save_needed = true;
                        add_to_log("Vehículo encontrado: %s en %c%i", l_plate, r + 'A', c + 1);
                    }

                } else {
                    printf_c(LIGHT_RED_TXT, "Operación cancelada. Coche no agregado\n");
                }
            }
        }

    }

    putchar('\n');
}

// Menú 2. Sacar vehículo
void remove_vehicle_op() {
    int r, c;
    scan_p_plot(&r, &c);

    if (!out_of_bounds(r, c)) {

        // Limpiamos y redibujamos para destacar el punto
        clear_redraw_and_highlight(r, c);

        if (!vehicle_inside(r, c)) {
            printf_c(LIGHT_RED_TXT, "Plaza de parking vacía.");


        } else {
            // Confirmamos que quiera guardar
            int save = confirm_action("Retirar coche?");

            if (save) { // Caso afirmativo
                int unparked = remove_vehicle(r, c); // Aquí se incluye el aviso de que el coche se ha retirado con éxito (o lo contrario)
                if (unparked) {
                    add_to_log("Vehículo retirado en %c%i", r + 'A', c + 1);
                    save_needed = true;
                }



            } else { // Caso negativo
                printf_c(LIGHT_RED_TXT, "Operación cancelada. Coche no retirado\n");
            }
        }



    }


    putchar('\n');
}

// Menú 3. Consultar información de plaza
void check_parking_lot() {
    int r, c;
    scan_p_plot(&r, &c);

    if(!out_of_bounds(r, c)) {

        // Limpiamos y redibujamos para destacar el punto
        clear_redraw_and_highlight(r, c);

        // Datos de la plaza
        putchar('\n');
        printf_c(UNDERLINE, "Datos de plaza");
        printf(":\n\n"); // Necesario caracter adicional para que el subrayado no se extienda


        // Comprueba si la plaza está vacía para que no imprima "null" por pantalla
        char* plate = parking[r][c].l_plate;

        if (plate == NULL) {
            printf_c(LIGHT_CYAN_TXT, "Plaza libre\n");
            printf("Tiempo en parking: -\n");

        } else {
            // Matrícula
            printf("Vehículo con matrícula: ");
            printf_c(LIGHT_YELLOW_TXT, "%s\n", plate);

            // Tiempo en el parking
            char* ptr = get_time_passed(parking[r][c].t_stamp);
            printf("Tiempo en parking: %s\n", ptr);
            free(ptr);

            // Información del vehículo

            Vehicle v_info = DBManager::retrieveVehicle(plate);

            cout << v_info;

        }

    }

    putchar('\n');
}

//Menú 4. Obtener estadísticas generales
void check_statistics() {
    printf_c(UNDERLINE, "Datos estadísticos");
    printf(":\n\n");

    // Cálculo de total de plazas, num disponibles y ocupadas

    int total = num_rows * num_cols;

    printf("Plazas ocupadas: %d\n", num_vehicles);
    printf("Plazas libres: %d\n", total - num_vehicles);
    printf("-------------------\n");
    printf("Total de plazas: %d\n", total);
}

// Menús 5 & 6
void modify_parking(void(*modify)(int)) { // Función que modifica filas o columnas dependiendo del puntero a una función que se pase

    int dn = read_int("Incremento: ");

    putchar('\n');

    if (dn == 0) {

        printf_c(LIGHT_MAGENTA_TXT, "Incremento nulo!\n");
    }

    else if (dn < 0) {

        printf_c(LIGHT_MAGENTA_TXT, "No se admiten decrementos!\n");
    }

    else {

        if (confirm_action("¿Está seguro/a?")) {

            modify(dn);
            printf_c(LIGHT_GREEN_TXT, "\nAñadida(s) con éxito.\n");
            add_to_log("Changed parking size.");
            save_needed = true;
        }

    }

}

// Menú 7. Crear nueva configuración.
void confirm_new_config() {
    if (confirm_action("Se perderá la configuración actual. ¿Confirmar?")) {
        free_parking_memory(); // Desalojamos la memoria dinámica actual del parking
        scan_parking(); // Pedimos nueva configuración y alojamos la cantidad memoria necesaria
        save_parking(); // Realizamos el cambio también en disco
        clear_log(); // Limpiamos el log de los últimos cambios

    }
}

// Menú 8. Configuración de la BDD del parking
void manage_parking_access() {
    char i_buffer [20];

    // logger
    open_logger("fichero_de_auditoria.log");

    clear_screen();
    printf_c(LIGHT_MAGENTA_TXT, "-- PARKING  /  ACCESO --\n\n");

    // Entrada de usuario y contraseña
    printf("Usuario: ");
    scan_str(i_buffer, sizeof(i_buffer));
    string user (i_buffer, strlen(i_buffer));

    // Recuperación de la contraseña de la BDD
    string passwordSha1 = DBManager::retrievePassword(user.c_str());
    if (passwordSha1 == "") {
        printf_c(LIGHT_RED_TXT, "\nNo se localizó el usuario.\n");
        close_logger();
        return;

    } else if (user != "admin") {
        printf_c(LIGHT_RED_TXT, "\nEl usuario no cuenta con los privilegios adecuados.\n");
        close_logger();
        return;
    }

    printf("Contraseña: ");
    scan_str(i_buffer, sizeof(i_buffer));
    char pswd[strlen(i_buffer)];
    strcpy(pswd, i_buffer);

    // Calculamos el hash de la contraseña
    QCryptographicHash hash(QCryptographicHash::Sha1);

    hash.addData(pswd, strlen(pswd));
    string inputSha1(hash.result().toHex());
    //string passwordSha1("d033e22ae348aeb5660fc2140aec35850c4da997"); // contraseña hardcodeada en SHA1

    // Comprobamos que la contraseña coincida
    if (inputSha1.compare(passwordSha1) != 0) {

        add_to_log("Intento de acceso a la BDD. Contraseña incorrecta. Usuario: admin.");
        printf_c(LIGHT_RED_TXT, "\nContraseña incorrecta. Volviendo al menú principal.\n");
        close_logger();
        return;
    }

    add_to_log("Intento de acceso a la BDD. Contraseña correcta. Usuario: admin");

    printf_c(LIGHT_GREEN_TXT, "\nContraseña correcta.\n\n");
    press_to_continue();

    // Submenú de la gestión del acceso
    while(1) {

        clear_screen();
        printf_c(LIGHT_MAGENTA_TXT, "-- PARKING  /  ACCESO --\n\n");
        printf(" 1. Permitir acceso a nuevos vehículos\n");
        printf(" 2. Retirar acceso al parking a vehículos ya registrados\n");
		printf(" 3. Mostrar todos los vehículos con acceso al parking\n");
		
        printf("\nIntroduce 'v' para volver.\n");

        printf("\nInput: ");
        scan_str(i_buffer, sizeof(i_buffer));

        if (strcmp(i_buffer, "v") == 0 || strcmp(i_buffer, "V") == 0) break;

        else if (strcmp(i_buffer, "1") == 0) {

            Vehicle v;

            putchar('\n');

            cin >> v;
            cout << v << endl;

            DBManager::insertVehicle(v);

            cout << "Finalizado sin errores" << endl;


        } else if (strcmp(i_buffer, "2") == 0) {

            cout << "Matrícula: ";
            scan_str(i_buffer, sizeof(i_buffer));
            DBManager::deleteVehicle(i_buffer);

        } else if (strcmp(i_buffer, "3") == 0) {

            cout << endl;
            print_title_center("", 18, RESET_COLOR, '-');

            DBManager::retrieveAllVehicles();


        } else {
            printf_c(LIGHT_RED_TXT, "Opción no válida.\n");

        }

        press_to_continue();

    }

    cout << "\nRegresando al menú principal." << endl;
    close_logger();

}

// LOGGER del parking_menu
static void configure_logger() {
    open_logger(log_file_txt);
    clear_log(); // limpiamos cualquier contenido residual posible (crashes, etc.)
}

// MENÚ

void parking_menu() {

    // Inicialización
    configure_logger();
    save_needed = false;
    init_parking();
    char i_buffer [DEFAULT_BUFFER_SIZE];
    reset_highlighted_point();

    // Conexión con BD
    DBManager::connect();


    // Programa
    while(1) {

        clear_screen();

        printf_c(LIGHT_MAGENTA_TXT,"------- PARKING -------\n");

        // Imprimir representación del parking

        print_parking();

        // Imprimir opciones disponibles por categorías

        printf("--- Gestión");
        printf("\n\n");

        printf(" 1. Introducir vehículo.\n");
        printf(" 2. Sacar vehículo.\n");
        printf(" 3. Consultar información de plaza.\n");
        printf(" 4. Obtener estadísticas generales.\n");
        putchar('\n');

        printf("--- Mantenimiento\n\n");

        printf(" 5. Añadir filas.\n");
        printf(" 6. Añadir columnas.\n");
        printf(" 7. Crear nueva configuración.\n");
        printf(" 8. [ADMIN] Gestionar acceso al parking\n");
        putchar('\n');

        printf("\nIntroduce 's' para guardar los cambios.\n");
        printf("Introduce 'v' para volver.\n");

        printf("\nInput: ");
        scan_str(i_buffer, sizeof(i_buffer));


        printf("\n----------------------\n\n"); // Separador


        if (strcmp(i_buffer, "v") == 0 || strcmp(i_buffer, "V") == 0) {

            if (save_needed) {
                read_log("PARKING");
                int dont_save = confirm_action("Existen cambios sin guardar. ¿Salir?");

                if (dont_save) {
                    printf_c(LIGHT_RED_TXT, "\nNo se han guardado los cambios.\n\n");
                    save_needed = false;
                    free_parking_memory();
                    clear_log();
                    break;
                } else {
                    printf_c(LIGHT_GREEN_TXT, "\nVolviendo al menú anterior.\n");
                }
            } else {
                free_parking_memory();
                break;
            }



        }

        else if (strcmp(i_buffer, "s") == 0 || strcmp(i_buffer, "S") == 0) {

            if (save_needed) {
                save_parking();
                save_needed = false;
                clear_log();
                printf_c(LIGHT_GREEN_TXT, "Guardado con éxito\n");

            } else {
                printf_c(LIGHT_MAGENTA_TXT, "Nada que guardar.\n");
            }

        }

        else if (strcmp(i_buffer,"1") == 0) insert_vehicle_op(); // Introducir vehículo en plaza

        else if (strcmp(i_buffer, "2") == 0) remove_vehicle_op(); // Quitar vehículo de la plaza

        else if (strcmp(i_buffer, "3") == 0) check_parking_lot(); // Consultar información de plaza

        else if (strcmp(i_buffer, "4") == 0) check_statistics();// Consultar estadísticas generales

        else if (strcmp(i_buffer, "5") == 0) modify_parking(modify_rows); // Cambiar número de filas

        else if (strcmp(i_buffer, "6") == 0) modify_parking(modify_columns); // Cambiar número de columnas

        else if (strcmp(i_buffer, "7") == 0) confirm_new_config(); //Crear nueva configuración

        else if (strcmp(i_buffer, "8") == 0) manage_parking_access(); // Acceso al parking (ADMIN)

        else printf("Opción no válida!\n"); // Opción incorrecta

        putchar('\n'); // Nueva línea

        press_to_continue();
    }

    close_logger();

    // Se desconecta la BD

    DBManager::disconnect();
}
