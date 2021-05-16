extern "C" {
#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <std_utils.h>
#include "management.h"
#include "animals/animals_menu.h"
}

#include <DBManager.h>
#include "Terrain.h"


static void clear_and_title() {
    clear_screen(); // Limpiamos pantalla
    print_title_center("TERRENOS", 24, LIGHT_CYAN_TXT, '-');
}

static void clear_and_redraw(vector<Terrain*> terrains) {

    clear_and_title();

    // Mostrar terrenos

    for(Terrain* terr: terrains) {

        terr->print();
    }
}


extern "C" void lands_menu() {

  DBManager::connect();

  vector<Terrain*> terrains = DBManager::retrieveTerrains();

  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while(1){

    clear_screen();

    print_title_center("TERRENOS", 24, LIGHT_CYAN_TXT, '-');
    printf("1. Comprar terreno.\n");
    printf("2. Vender terreno.\n");
    printf("3. Listar terrenos.\n");

    printf("\n4. [Animales] Gestionar animales.\n");


    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    putchar('\n');

    if(!strcmp(input_buffer, "v")) {

      // Liberación de memoria

      for (Terrain* terr: terrains) {

          delete terr;

      }

      break;
    }

    // Comprar terreno

    else if (strcmp(input_buffer, "1") == 0) {

        print_banner('-', 33, LIGHT_CYAN_TXT);

        Terrain* t;

        int opt = choose_option("Terreno de cultivo (C) o animales (A)? ", 2, "C", "A");

        if (opt == 1) {

            t = new CropTerrain();
        }

        else {

            t = new AnimalTerrain();
        }

        t->readFromConsole();

        terrains.push_back(t);

        // TODO Registrar gasto

    // Vender terreno

    } else if(strcmp(input_buffer, "2") == 0) {

      // Limpiamos
        if (terrains.size() > 0) {
            clear_and_redraw(terrains);

            // Preguntamos
            //int i = read_int("\nTerreno a vender: ");

            // Todo

        } else {
            printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");
        }


    } else if(strcmp(input_buffer,"3") == 0){
        if (terrains.size() > 0) {

            clear_and_redraw(terrains);

        } else {
            printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");
        }

    }

    else if(strcmp(input_buffer, "4") == 0) {

        animals_menu();
    }


    else { printf("Opción incorrecta!\n"); }

    putchar('\n');
    press_to_continue();

  }

  DBManager::disconnect();
}
