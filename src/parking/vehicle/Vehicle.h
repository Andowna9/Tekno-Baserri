#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
using namespace std;

// Clase que representa un vehículo aparcado en el parking

class Vehicle {

private:

    string l_plate; // Matrícula
    string color; // Color
    string brand; // Marca
    float height; // Altura x Anchura

public:

    Vehicle(); // Constructor por defecto
    Vehicle(string l_plate, string color, string brand, float height); // Constructor completo
    Vehicle(char* l_plate);

    // Getters

    string getLicensePlate() const;
    string getColor() const;
    string getBrand() const;
    float getHeight() const;

    // Setters

    void setLicensePLate(string lp);
    void setColor(string c);
    void setBrand(string b);
    void setHeight(float height);

    // NOTA: Ambas funciones se declaran como friends ya que necesitan acceso a todos los métodos y atributos privados
    // No son métodos de clase, por lo que en el .cpp no es necesario especificarla con ::

    // Sobrecarga de operador de inserción

    friend ostream & operator << (ostream &out, const Vehicle &v);

    // Sobrecarga de operador de extracción

    friend istream & operator >> (istream &in, Vehicle &v);


};

#endif // VEHICLE_H
