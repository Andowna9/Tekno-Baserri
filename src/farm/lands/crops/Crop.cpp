#include "Crop.h"
#include <cpp_utils.h>


Crop::Crop(string name) {

    this->name = name;

}


string Crop::getName() const {

    return name;
}

void Crop::setName(string name) {

    this->name = name;
}


// Sobrecarga de entrada
ostream & operator << (ostream &out, const Crop &a) {

    out << "Nombre de cultivo: " << a.name << endl;

    return out;

}


