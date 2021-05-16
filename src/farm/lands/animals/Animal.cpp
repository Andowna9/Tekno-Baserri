#include "Animal.h"
#include <iostream>
#include <cpp_utils.h>
using namespace std;

map<int, string> Animal::animal_types;

void Animal::loadTypes(map<int, string> map) {

    animal_types = map;
}

Animal::Animal() {

    id = -1;
}

Animal::Animal(int id, string name, float weight, int type_id) {

    this->id = id;
    this->name = name;
    this->weight = weight;
    this->type_id = type_id;
}

// Getters

int Animal::getID() const {

    return id;
}

float Animal::getWeight() const {

    return weight;
}

string Animal::getName() const {

    return name;
}

string Animal::getType() const {

    return animal_types.at(this->type_id);
}

// Setters

void Animal::setID(int id) {

    // Si todavía no hay un id asociado, es posible asignar uno

    if (this->id == -1) {

        this->id = id;

    }
}

// Sobrecarga de streams de input y output

ostream & operator << (ostream &out, const Animal &a) {

    out << "ID: " << a.id << endl;
    out << "Nombre propio: " << a.name << endl;
    out << "Peso: " << a.weight << " kg" << endl;
    out << "Especie: " << a.getType() << endl;

    return out;

}

istream & operator >> (istream &in, Animal &a) {

    cout << "Nombre propio: ";
    readVar(in, a.name);

    cout << "Peso: ";
    readVar(in, a.weight);

    // Se muestran los tipos de animales

    cout << "Tipos de animales disponibles: " << endl;

    for (auto & x: Animal::animal_types) {

        cout << x.first << ". " << x.second << endl;
    }

    int type_id = -1;

    do {

        readVar(in, type_id);

        if (Animal::animal_types.find(type_id) == Animal::animal_types.end()) {

            cout << "El tipo de animal introducido no existe!" << endl;
            type_id = -1;
        }

    } while (type_id == -1);


    return in;
}

