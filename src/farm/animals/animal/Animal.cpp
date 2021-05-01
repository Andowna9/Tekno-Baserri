#include "Animal.h"
#include <iostream>
using namespace std;

Animal::Animal() {

}


ostream & operator << (ostream &out, const Animal &a) {

    out << "Animal: " << a.name << endl;
    out << "Peso: " << a.weight << " kg" << endl;
    out << "Edad: " << a.age << endl;

    return out;

}

istream & operator >> (istream &in, Animal &a) {

    cout << "Animal: ";
    in >> a.name;

    cout << "Peso: ";
    in >> a.weight;

    cout << "Edad: ";
    in >> a.age;

    return in;
}
