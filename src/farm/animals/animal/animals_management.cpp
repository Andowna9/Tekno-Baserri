// consultas animales

extern "C" {

#include <std_utils.h>
#include <stdio.h>
#include <console_config.h>
#include <string.h>
}

#include <iostream>
#include "Animal.h"
#include "DBManager.h"
using namespace std;
#include <vector>
#include <unordered_map>

// TODO Funcionalidades

void check_animals() {

}

void remove_animals() {

}

void add_animals() {

}

void sell_animals() {

}

void buy_animals() {

}

extern "C" void animals_management_menu(){

  char input_buffer [DEFAULT_BUFFER_SIZE];

  DBManager::connect(DBManager::FARM);

  vector<Animal> animals = DBManager::retriveAnimals(); // La lista se carga con los animales almacenados en la BD

  unordered_map<string, int> animal_types = DBManager::getAnimalTypes();

  while (1) {

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- GESTIÓN ANIMALES -------\n\n");
    printf("1. Consultar animales.\n");
    printf("2. Retirar animales.\n");
    printf("3. Agregar animales.\n");
    printf("4. Vender animales.\n");
    printf("5. Comprar animales.\n");

    cout << endl << "Total de animales: " << animals.size() << endl;

    printf("\nIntroduce 'v' para volver\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));
    putchar('\n');

    if (strcmp(input_buffer, "v") == 0 || strcmp(input_buffer, "V") == 0) {
        break;
    }

    // Check animals

    if (strcmp(input_buffer, "1") == 0) {


        if (animals.size() == 0) {

            cout << "Lista de animales vacía!" << endl;
        }

        else {

            for (const Animal & a: animals) {

                cout << a << endl;

            }

        }


    }

    // Remove animal

    else if(strcmp(input_buffer, "2") == 0) {




    }

    // Add animal

    else if(strcmp(input_buffer, "3") == 0) {

        // Se muestran los tipos de animales

        cout << "Tipos de animales disponibles: " << endl;

        for (auto & x: animal_types) {

            cout << "[" << x.first << "]" << endl;
        }

        Animal new_animal;
        cin >> new_animal;

        try {

            int type_id = animal_types.at(new_animal.getType());
            DBManager::insertAnimal(new_animal, type_id);
            animals.push_back(new_animal);

            cout << "Animal registrado sin problema" << endl;

        }

        // El mapa lanza una excepción si la clave no existe

        catch (const out_of_range& oor) {

            cout << "El tipo introducido no existe!" << endl;
        }


    }

    else if(strcmp(input_buffer, "4") == 0) {
      sell_animals();


    }

    else if(strcmp(input_buffer, "5") == 0) {
      buy_animals();

    }

    else printf("Opción no disponible!\n");

    putchar('\n');
    press_to_continue();
  }

  DBManager::disconnect();

}

