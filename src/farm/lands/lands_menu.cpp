extern "C" {
#include <stdio.h>
#include <string.h>
#include <console_config.h>
#include <std_utils.h>
#include "management.h"
#include "animals/food/food.h"
#include "animals/food/food_menu.h"
}

#include <DBManager.h>
#include <QDate>
#include "WeatherForecast.h"
#include <cpp_utils.h>
#include "Terrain.h"


static void clear_and_title(const char* title) {
    clear_screen(); // Limpiamos pantalla
    print_title_center(title, 24, LIGHT_CYAN_TXT, '-');
}

// Funciones para visualizar los distintos tipos de terreno

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

            cout << "-- Cultivo " << i + 1 << " --" << endl;
            crop_terrains[i]->printContent();
            cout << endl;
      }


}

static void show_animal_terrains(const vector<AnimalTerrain*> &animal_terrains) {


     clear_and_title("CORRALES");

     for (unsigned int i = 0; i < animal_terrains.size(); i++) {

          cout << "-- Corral " << i + 1 << " --" << endl;
          animal_terrains[i]->printContent();
          cout << endl;
     }

}

static void show_animals(AnimalTerrain* at) {

    if (at->isEmpty()) {

        cout << "Lista de animales vacía!" << endl;
    }

    else {

        vector<Animal> animals = at->getAnimals();

        for (unsigned int i = 0; i < animals.size(); i++) {

            cout << "-- " << at->getAnimalType() << " " << i + 1 << " --" << endl;
            cout << animals[i];
            cout<< "Edad " << DBManager::getAnimalAge(animals[i].getID()) << endl << endl;

        }

    }


}

// Menú para la gestión de un corral dado

static void animal_terrain_management(AnimalTerrain* at) {

    char i_buffer [DEFAULT_BUFFER_SIZE];

    while (1) {

        clear_screen();
        print_title_center("GESTIÓN DE CORRAL", 30,  LIGHT_CYAN_TXT, '-');

        // Imprimimos el corral vacío o con animales

        cout << "[Corral de " << at->getAnimalType() << "s]" << endl;
        cout << endl;

        if (at->isEmpty()) {

            cout << "+-------+" << endl;
            cout << "| Vacío |" << endl;
            cout << "+-------+" << endl;
        }

        else {

            cout << "x" << at->getNumAnimals() << " animales" << endl;

        }

        printf("\n1. Añadir animal.\n");
        printf("2. Retirar animal\n");
        printf("3. Listar detalles de animales.\n");
        printf("4. Alimentar animales.\n");
        printf("5. Estadísticas.\n");


        printf("\nIntroduce 'v' para volver.\n\n");

        printf("Input: ");
        scan_str(i_buffer, sizeof(i_buffer));

        putchar('\n');

        if (strcmp(i_buffer, "v") == 0 || strcmp(i_buffer, "V") == 0) {

            break;
        }

        // Añadir animal

        else if (strcmp(i_buffer, "1") == 0) {

            Animal a;
            cin >> a;

            unsigned int y;
            unsigned int m;
            unsigned int d;

            int n;

            do {
                cout << "Fecha de nacimiento (Formato aaaa-mm-dd): ";
                n = read_format("%4u-%2u-%2u", &y, &m, &d);

            } while(n != 3);

            QDate date(y, m, d);
            string birth_date = date.toString(Qt::ISODate).toStdString();

            putchar('\n');

            // Registro en BD y memoria

            if (DBManager::insertAnimal(a, birth_date, at->getID())) {

                at->addAnimal(a);

                printf_c(LIGHT_GREEN_TXT, "Animal registrado correctamente.\n");

            }

            else {

                printf_c(LIGHT_RED_TXT, "Problema al registrar animal!\n");

            }

        }

        // Retirar animal

        else if (strcmp(i_buffer, "2") == 0) {

            show_animals(at);

            int num = read_int("Número de animal: ");
            int index = num - 1;
            putchar('\n');

            try {

                Animal a = at->getAnimal(index);
                if (DBManager::removeAnimal(a.getID())) {

                        printf_c(LIGHT_GREEN_TXT, "Animal retirado.\n");
                        at->removeAnimal(index);
                }

               else {

                    printf_c(LIGHT_RED_TXT, "Error al retirar animal!.\n");

                }

            }

            catch (const out_of_range &oor) {

                printf_c(LIGHT_RED_TXT, "Número incorrecto!\n");
            }

        }

        // Listar animales con detalle

        else if (strcmp(i_buffer, "3") == 0) {


            show_animals(at);
        }

        // Alimentar animales

        else if (strcmp(i_buffer, "4") == 0) {

            if (at->getNumAnimals() > 0) {

                    while (true) {

                        clear_screen();

                        printf_c(LIGHT_CYAN_TXT, "Alimentos disponibles: \n\n");

                        check_available_food();

                        printf_c(LIGHT_YELLOW_TXT, "[ ID: 0 - Cancelar operación. ]\n\n");

                        int id = read_int("ID: ");
                        putchar('\n');

                        if (id == 0) {

                            printf_c(LIGHT_RED_TXT, "Operación cancelada!\n");

                            break;
                        }

                        Animal_Food* food = get_food_by_id(id);

                        // Out Of Bounds Check

                        if (food == NULL || food->amount == 0) {

                            printf_c(LIGHT_RED_TXT, "ID incorrecto!\n");
                        }

                        else {

                            float max_avg = food->amount / at->getNumAnimals();

                            printf("Máxima cantidad por animal: %.2f kg\n", max_avg);

                            float avg_amount = read_float("Cantidad para alimentar: ");
                            putchar('\n');

                            if (avg_amount > max_avg) {

                                printf_c(LIGHT_RED_TXT, "No hay tanta cantidad de alimento disponible!\n");
                            }

                            else {

                                consume_animal_food(id, avg_amount * at->getNumAnimals());

                                printf_c(LIGHT_GREEN_TXT, "Animales alimentados.\n");

                                break;
                            }

                        }

                        putchar('\n');

                        press_to_continue();
                    }

            }

            else {

                printf_c(LIGHT_RED_TXT, "No hay animales que alimentar!\n");
            }
        }

        else if (strcmp(i_buffer, "5") == 0) {

            at->calculateWeightStatistics();

            DBManager::printTerrainAgeStatistics(at->getID());
        }

        else { printf("La opción introducida no existe!\n"); }

        putchar('\n');
        press_to_continue();

    }


}


extern "C" void lands_menu() {

  // Carga de comidas de animales de fichero

  read_food_types();

  // Carga de terrenos en BD

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

    // Terrenos genérico
    printf("--General\n\n");
    printf("1. Comprar terreno.\n");
    printf("2. Vender terreno.\n");
    printf("3. Listar terrenos.\n");

    // Terreno de cultivo

    printf("\n--Terrenos de cultivo\n\n");

    if (crop_terrains.size() > 0) {

        printf("4. Listar cultivos.\n");
        printf("5. Recoger cosechas.\n");
        printf("6. Estadísticas.\n");

    }

    else {

        printf_c(LIGHT_YELLOW_TXT, "De momento no hay ningún cultivo.\n");
    }

    // Terreno de animales

    printf("\n--Terrenos de animales\n\n");

    if (animal_terrains.size() > 0) {

        printf("7. Listar corrales.\n");
        printf("8. Gestionar corral.\n");
        printf("9. Estadísticas.\n");

    }

    else {

        printf_c(LIGHT_YELLOW_TXT, "De momento no hay ningún corral.\n");

    }

    // Menú de comida de animales

    printf_c(LIGHT_CYAN_TXT, "\n[10. Comida de Animales]\n");

    printf_c(LIGHT_MAGENTA_TXT, "\n* Pronóstico de tiempo.\n");


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
            printf_c(LIGHT_GREEN_TXT, "Terreno guardado correctamente.");
            cout << endl;

            // Registrar gasto
            register_expense(t->getCost());

            // Añadir terreno a vector en memoria
            terrains.push_back(t);

            if (typeid(*t).hash_code() == typeid(CropTerrain).hash_code()) {

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

            clear_screen();
            printf_c(LIGHT_CYAN_TXT, "Se va a vender el siguiente terreno:\n\n");

            Terrain* t = terrains.at(i);

            t->print();
            cout << endl;
            cout << "[ CONTENIDO ]" << endl;
            t->printContent();
            cout << endl;


            float price = read_float("Precio de venta: ");
            putchar('\n');

            if (typeid(*t).hash_code() == typeid(AnimalTerrain).hash_code()) {

                AnimalTerrain* at = (AnimalTerrain*) t;

                if (at->getNumAnimals() > 0) {

                    printf_c(LIGHT_RED_TXT, "AVISO: Se retirarán %d animales asociados!\n\n", at->getNumAnimals());
                }

             }

            int sell = confirm_action("¿Confirmar venta?");

            // Borrar terreno de BD y memoria

            if (sell) {

                bool success = DBManager::removeTerrain(t->getID());

                if (success) {


                    // Borrado de lista auxiliar

                    // Como se trata de punteros son iguales si apuntan a la misma dirección de memoria

                    if (typeid(*t).hash_code() == typeid(CropTerrain).hash_code()) {

                        removeVectorElement(crop_terrains, (CropTerrain*)t);
                    }

                    else {

                        removeVectorElement(animal_terrains, (AnimalTerrain*)t);
                    }


                    // Borrado de lista principal

                    delete t; //Liberación de memoria dinámica
                    terrains.erase(terrains.begin() + i); //Borrado de puntero en el vector

                    register_profit(price);

                    cout << endl;
                    printf_c(LIGHT_GREEN_TXT, "Venta realizada.");
                    cout << endl;
                }

                else {

                    printf_c(LIGHT_RED_TXT, "Error al realizar venta!\n");
                }

            } else {
                printf_c(LIGHT_RED_TXT, "\nVenta cancelada.\n");

            }


        } else {
            printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");
        }


    } else if(strcmp(input_buffer,"3") == 0){

        if (terrains.size() > 0) {

           show_terrains(terrains);

        }

         else {

              printf_c(LIGHT_RED_TXT, "No hay terrenos registrados.\n");

         }

    }

    // Listar cultivos

    else if(strcmp(input_buffer, "4") == 0 && crop_terrains.size() > 0) {


         show_crop_terrains(crop_terrains);
    }

    // Registrar cosechas

    else if (strcmp(input_buffer, "5") == 0 && crop_terrains.size() > 0) {

        // Los productos cosechados pueden venderse o añadirse como mida para animales

        show_crop_terrains(crop_terrains);

        int index = read_int("Número de cultivo: ");
        putchar('\n');

        try {

            CropTerrain* ct = crop_terrains.at(index - 1);

            clear_and_title("CULTIVOS");
            printf_c(LIGHT_CYAN_TXT, "Cosechando %ss ...\n\n", ct->getCropType().c_str());

            crop_terrains[index-1]->printContent();

            float amount = read_float("Cantidad (kg): ");

            putchar('\n');

            int opt = choose_option("¿Qué desea hacer?\n\na)Vender.\nb)Guardar como comida de animales.\n\nRespuesta: ", 2, "a", "b");

            // Opción 1: Vender

            if (opt == 1) {

                float price = read_float("Precio por kilogramo (€/kg): ");
                putchar('\n');

                register_profit(price * amount);

                printf_c(LIGHT_GREEN_TXT, "Venta realizada correctamente.\n");

            }

            // Opción 2: Añadir producto como comida de animales

            else if (opt == 2) {

                int id = find_food_id_by_name(ct->getCropType().c_str());

                // Todavía no existe

                if (id == - 1) {

                    printf_c(LIGHT_CYAN_TXT, "Detectado nuevo alimento: %s\n", ct->getCropType().c_str());

                    register_animal_food(ct->getCropType().c_str(), 0, amount);

                }

                // Si ya existe, se añade la cantidad correspondiente

                else {


                    add_animal_food(id, amount);

                }

                cout << endl;
                printf_c(LIGHT_GREEN_TXT, "Añadida cantidad a comida de animales.\n");

           }



        }

        catch(out_of_range &oor) {

            printf_c(LIGHT_RED_TXT, "El número de cultivo no existe!\n");
        }

    }

    // Estadísticas de cultivos

    else if (strcmp(input_buffer, "6") == 0 && crop_terrains.size() > 0) {
        clear_and_title("ESTADÍSTICAS");
        DBManager::printCropTerrainCount();
    }

    // Listar corrales

    else if (strcmp(input_buffer, "7") == 0 && animal_terrains.size() > 0) {


         show_animal_terrains(animal_terrains);

    }

    // Gestionar corral

    else if (strcmp(input_buffer, "8") == 0 && animal_terrains.size() > 0) {

        show_animal_terrains(animal_terrains);

        int index = read_int("Número de corral: ");

        try {

            AnimalTerrain* at = animal_terrains.at(index - 1);

            // Acceso a pequeño menú

            animal_terrain_management(at);
            continue; // Empieza el bucle de nuevo para evitar la espera de "press to continue"
        }

        catch (out_of_range &oor) {

            printf_c(LIGHT_RED_TXT, "El número de corral no es válido!\n");
        }


    }

    // Estadísticas de corrales

    else if (strcmp(input_buffer, "9") == 0 && animal_terrains.size() > 0) {
        clear_and_title("ESTADÍSTICAS");
        DBManager::printAnimalTerrainCount();
    }


    // Acceso a menú de alimentos de animales

    else if (strcmp(input_buffer, "10") == 0) {

        animal_food_menu();
        continue;
    }

    else if (strcmp(input_buffer, "*") == 0) {

        WeatherForecast wf;
        wf.addLocation("Vitoria-Gasteiz", 8043);
        wf.addLocation("Bilbao", 8050);
        wf.addLocation("Donostia-San Sebastián", 4917);

        if (wf.chooseLocation()) {

            clear_and_title("PRONÓSTICO DEL TIEMPO");
            wf.displayForecast();
        }

    }

    else { printf("Opción incorrecta!\n"); }

    putchar('\n');
    press_to_continue();

  }

  DBManager::disconnect();

  free_animal_food_memory(); // Liberación de memoria en lista dinámica de comida de animales
}
