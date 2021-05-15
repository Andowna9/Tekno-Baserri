#include "Animal.h"
#include <iostream>
#include <cpp_utils.h>
using namespace std;

Animal::Animal() {

    id = -1;
}

Animal::Animal(int id, string name, float weight, string type) {

    this->id = id;
    this->name = name;
    this->weight = weight;
    this->type = type;
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

    return type;
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
    out << "Especie: " << a.type << endl;

    return out;

}

istream & operator >> (istream &in, Animal &a) {

    cout << "Nombre propio: ";
    readVar(in, a.name);

    cout << "Peso: ";
    readVar(in, a.weight);

    cout << "Especie: ";
    readVar(in, a.type);


    return in;
}

