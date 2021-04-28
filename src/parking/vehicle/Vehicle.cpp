#include "Vehicle.h"

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

string Vehicle::getLicensePlate() const {

    return this->l_plate;

}
string Vehicle::getColor() const {

    return this->color;

}
string Vehicle::getBrand() const {

    return this->brand;
}

void Vehicle::setLicensePLate(string lp) {

    this->l_plate = lp;
}

void Vehicle::setColor(string c) {

    this->color = c;
}

void Vehicle::setBrand(string b) {

    this->brand = b;
}

// Permite hacer cout con un vehículo - Referencia constante para evitar modificar la instancia

ostream & operator << (ostream &out, const Vehicle &v) {

    out << "Color: " << v.color << endl;
    out << "Marca: " << v.brand << endl;
    // out << "Dimensiones: " << v.dim.first << " x " << v.dim.second << endl;

    return out;
}

// Permite hacer cin con un vehículo

istream & operator >> (istream &in, Vehicle &v) {

    cout << "--Introduce la información del vehículo--" << endl;

    cout << "Color: ";
    in >> v.color;

    cout << "Marca: ";
    in >> v.brand;

    cout << "Dimensiones: ";
    in >> v.dim.first >> v.dim.second;

    return in;
}

