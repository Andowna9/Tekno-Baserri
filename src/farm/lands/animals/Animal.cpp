#include "Animal.h"
#include <iostream>
#include <cpp_utils.h>
using namespace std;

Animal::Animal() {

    id = -1;
}

Animal::Animal(int id, string name, float weight) {

    this->id = id;
    this->name = name;
    this->weight = weight;
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

void Animal::setID(int id) {
    this->id = id;
}

// Sobrecarga de streams de input y output

ostream & operator << (ostream &out, const Animal &a) {

    out << "ID: " << a.id << endl;
    out << "Nombre propio: " << a.name << endl;
    out << "Peso: " << a.weight << " kg" << endl;

    return out;

}


istream & operator >> (istream &in, Animal &a) {


    readVar(in, a.name, "Nombre propio: ");

    readVar(in, a.weight, "Peso: ");

    return in;


}

