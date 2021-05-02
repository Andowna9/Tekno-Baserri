#ifndef CPP_UTILS_H
#define CPP_UTILS_H

#include <iostream>
using namespace std;

// Recibe un stream de entrada y una referencia a un tipo genérico donde almacenar la lectura y posteriormente limpiar el buffer

template<class T>
void readVar(istream& in, T& var) {

    in >> var;
    in.clear(); // Reinicia el estado del stream para que no siga buscando match
    in.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora todos los caracteres hasta el '\n'
}

#endif // CPP_UTILS_H
