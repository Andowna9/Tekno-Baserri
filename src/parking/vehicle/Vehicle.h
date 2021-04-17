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
    pair<float, float> dim; // Altura x Anchura

public:

    Vehicle(); // Constructor por defecto
    Vehicle(string l_plate, string color, string brand, pair<float, float> dimensions); // Constructor completo

    // NOTA: Ambas funciones se declaran como friends ya que necesitan acceso a todos los métodos y atributos privados
    // No son métodos de clase, por lo que en el .cpp no es necesario especificarla con ::

    // Sobrecarga de operador de inserción

    friend ostream & operator << (ostream &out, const Vehicle &v);

    // Sobrecarga de operador de extracción

    friend istream & operator >> (istream &in, Vehicle &v);


};

#endif // VEHICLE_H
