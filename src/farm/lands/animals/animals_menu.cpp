extern "C" {
#include <stdio.h>
#include <string.h>
#include <std_utils.h>
#include "food/food_menu.h"
#include "animals_menu.h"
#include <console_config.h>
}

#include <iostream>
#include <DBManager.h>
#include <vector>
#include "Animal.h"
using namespace std;

void animals_menu() {

  vector<Animal> animals; // La lista se carga con los animales almacenados en la BD

  char input_buffer [DEFAULT_BUFFER_SIZE];

  while (1) {

    clear_screen();

    printf_c(LIGHT_CYAN_TXT, "------- ANIMALES -------\n\n");
    printf("1. Consultar animales.\n");
    printf("2. Retirar animales.\n");
    printf("3. Agregar animales.\n");
    printf("4. Vender animales.\n");
    printf("5. Comprar animales.\n");

    cout << endl << "Total de animales: " << animals.size() << endl;

    printf("\n6. [COMIDA] Gestionar comida.\n");
    
    printf("\nIntroduce 'v' para volver.\n\n");

    printf("Input: ");
    scan_str(input_buffer, sizeof(input_buffer));

    putchar('\n');

    if (strcmp(input_buffer, "v") == 0 || strcmp(input_buffer, "V") == 0 ) {

      break;
    }

    // Check animals

    else if (strcmp(input_buffer, "1") == 0) {


        if (animals.size() == 0) {

            cout << "Lista de animales vacía!" << endl;
        }

        else {

            for (const Animal & a: animals) {

                cout << a << endl;

            }

        }


    }

    else if(strcmp(input_buffer, "2") == 0) {


    }

    else if (strcmp(input_buffer, "3") == 0) {




    }

    else if (strcmp(input_buffer, "4") == 0) {

    }

    else if (strcmp(input_buffer, "5") == 0) {

    }

    else if (strcmp(input_buffer, "6") == 0) {

        animal_food_menu();
    }

    else { printf("Opción incorrecta!\n"); }


    putchar('\n');
    press_to_continue();

  }

}
