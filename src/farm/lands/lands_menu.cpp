extern "C" {
#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <std_utils.h>
#include "management.h"
#include "animals/animals_menu.h"
}

#include <DBManager.h>
#include <cpp_utils.h>
#include "Terrain.h"


static void clear_and_title(const char* title) {
    clear_screen(); // Limpiamos pantalla
    print_title_center(title, 24, LIGHT_CYAN_TXT, '-');
}

// Métodos para visualizar los distintos tipos de terreno

static void show_terrains(const vector<Terrain*> &terrains) {

    clear_and_title("TERRENOS");

    // Mostrar terrenos

    for(int i = 0; i < (int) terrains.size(); i++) {

        Terrain* terr = terrains[i];
        cout << i + 1 << ". ";
        terr->print();
        cout << endl;
    }
}


static void show_crop_terrains(const vector<CropTerrain*> &crop_terrains) {

    clear_and_title("CULTIVOS");

    for (unsigned int i = 0; i < crop_terrains.size(); i++) {

        cout << "Cultivo " << i + 1 << endl;
        cout << "-------------------" << endl;
        crop_terrains[i]->printContent();
        cout << endl;
    }

}

static void show_animal_terrains(const vector<AnimalTerrain*> &animal_terrains) {

    clear_and_title("CORRALES");

    for (unsigned int i = 0; i < animal_terrains.size(); i++) {

        cout << "Corral " << i + 1 << endl;
        cout << "-------------------" << endl;
        animal_terrains[i]->printContent();
        cout << endl;
    }

}


extern "C" void lands_menu() {

  DBManager::connect();

  // Vectores auxiliares

  vector<CropTerrain*> crop_terrains;
  vector<AnimalTerrain*> animal_terrains;

  // Carga de Base de Datos

  vector<Terrain*> terrains = DBManager::retrieveTerrains(crop_terrains, animal_terrains);

  char input_buffer [DEFAULT_BUFFER_SIZE]; // Buffer de lectura por defecto

  while(1){

    clear_screen();

    print_title_center("TERRENOS", 24, LIGHT_CYAN_TXT, '-');
    printf("1. Comprar terreno.\n");
    printf("2. Vender terreno.\n");
    printf("3. Listar terrenos.\n");

    printf("\n--Terrenos de cultivo\n");
    printf("\n4. Listar cultivos.\n");
    printf("5. Registrar cosechas.\n");

    printf("\n--Terrenos de animales\n");
    printf("\n6. Listar corrales.\n");
    printf("7. Gestionar corral.\n");

    //printf("\n4. [Animales] Gestionar animales.\n");


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

        bool saved = t->saveInDB(); // Comprueba si hay conexión a la BD y guarda el terreno

        if (saved) {

            cout << endl;
            printf_c(LIGHT_GREEN_TXT, "Terreno guardado correctamente");
            cout << endl;

            // Registrar gasto
            register_expense(t->getCost());

            // Añadir terreno a vector en memoria
            terrains.push_back(t);

            if (typeid(t).hash_code() == typeid(CropTerrain).hash_code()) {

                crop_terrains.push_back((CropTerrain*) t);
            }

            else {

                animal_terrains.push_back((AnimalTerrain*) t);
            }


        }

        else {

            printf_c(LIGHT_RED_TXT, "Error al guardar terreno!");
        }


    // Vender terreno

    } else if(strcmp(input_buffer, "2") == 0) {

      // Limpiamos
        if (terrains.size() > 0) {

            show_terrains(terrains);

            // Preguntamos
            int i;
            do {
                i = read_int("\nTerreno a vender: ");
            } while(i <= 0 || i > (int) terrains.size());

            i--; // El índice interno empieza en cero, la lista que ve el usuario en 1
            float price = read_float("Precio de venta: ");

            // Borrar terreno de BD y memoria

            Terrain* t = terrains.at(i);
            bool success = DBManager::removeTerrain(t->getID());

            if (success) {

                delete t; //Liberación de memoria
                terrains.erase(terrains.begin() + i); //Borrado de puntero en el vector

                // Borrado de lista auxiliar
                // Como se trata de punteros son iguales si apuntan a la misma dirección de memoria

                if (typeid (t).hash_code() == typeid(CropTerrain).hash_code()) {

                    removeVectorElement(crop_terrains, (CropTerrain*)t);
                }

                else {

                    removeVectorElement(animal_terrains, (AnimalTerrain*)t);
                }

                register_profit(price);

                cout << endl;
                printf_c(LIGHT_GREEN_TXT, "Venta realizada");
                cout << endl;
            }

            else {

                printf_c(LIGHT_RED_TXT, "Error al realizar venta!");
            }


        } else {
            printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");
        }


    } else if(strcmp(input_buffer,"3") == 0){
        if (terrains.size() > 0) {

           show_terrains(terrains);

        } else {
            printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");
        }

    }

    // Listar cultivos

    else if(strcmp(input_buffer, "4") == 0) {

        show_crop_terrains(crop_terrains);
    }

    // TODO Registrar cosechas

    else if (strcmp(input_buffer, "5") == 0) {

    }

    // Listar corrales

    else if (strcmp(input_buffer, "6") == 0) {

        show_animal_terrains(animal_terrains);

    }

    // TODO Métodos para corrales adicionales


    else { printf("Opción incorrecta!\n"); }

    putchar('\n');
    press_to_continue();

  }

  DBManager::disconnect();
}
