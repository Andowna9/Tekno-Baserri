#include "Crop.h"
#include <cpp_utils.h>


Crop::Crop() {

    id = -1;
}

Crop::Crop(int id, string name)
{

    this->id = id;
    this->name = name;

}


int Crop::getId() const {

    return id;
}

string Crop::getName() const {

    return name;
}


// Sobrecarga de entrada
ostream & operator << (ostream &out, const Crop &a) {

    out << "ID: " << a.id << endl;
    out << "Nombre de cultivo: " << a.name << endl;

    return out;

}


