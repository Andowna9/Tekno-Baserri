extern "C" {
    #include <std_utils.h>
}
#include "Vehicle.h"


// CONSTRUCTORES
Vehicle::Vehicle(){

    l_plate = "";
    color = "";
    brand = "";
}

Vehicle::Vehicle(string l_plate, string color, string brand) {

      this->l_plate = l_plate;
      this->color = color;
      this->brand = brand;
}

Vehicle::Vehicle(char* l_plate) {

    this->l_plate = string(l_plate);
}


// GETTERS
string Vehicle::getLicensePlate() const {

    return this->l_plate;

}
string Vehicle::getColor() const {

    return this->color;

}
string Vehicle::getBrand() const {

    return this->brand;
}

float Vehicle::getHeight() const {
    return this->height;
}


// SETTERS
void Vehicle::setLicensePLate(string lp) {

    this->l_plate = lp;
}

void Vehicle::setColor(string c) {

    this->color = c;
}

void Vehicle::setBrand(string b) {

    this->brand = b;
}

void Vehicle::setHeight(float height) {

    this->height = height;
}


// OTROS

// Permite hacer cout con un vehículo - Referencia constante para evitar modificar la instancia
ostream & operator << (ostream &out, const Vehicle &v) {

    out << "Matrícula: " << v.l_plate << endl;
    out << "Color: " << v.color << endl;
    out << "Marca: " << v.brand << endl;
    out << "Altura: " << v.height << endl;
    print_title_center("", 18, RESET_COLOR, '-');

    return out;
}

// Permite hacer cin con un vehículo
istream & operator >> (istream &in, Vehicle &v) {

    //cout << "------------------" << endl << endl;
    print_title_center("", 33, RESET_COLOR, '-');

    cout << "Matrícula del vehículo: ";
    in >> v.l_plate;

    cout << "Color del vehículo: ";
    in >> v.color;

    cout << "Marca del vehículo: ";
    in >> v.brand;

    cout << "Altura del vehículo: ";
    in >> v.height;

    return in;
}

