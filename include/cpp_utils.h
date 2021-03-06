#ifndef CPP_UTILS_H
#define CPP_UTILS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

// Recibe un stream de entrada y una referencia a un tipo genérico donde almacenar la lectura y posteriormente limpiar el buffer

template<class T>
void readVar(istream& in, T& var, const char* message) {

    while (true) {

        cout << message;

        // Formato correcto

        if (in >> var) {

            break;
        }

        // Formato incorrecto

        else {


            in.clear(); // Reinicia el estado del stream a uno correcto
            in.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora todos los caracteres hasta el '\n'

        }

    }

    in.ignore(numeric_limits<streamsize>::max(), '\n'); // Se eliman caracteres residuales tras input correcto
}

template<class K, class V>
void printMap(map<K,V> m) {

    for (const auto& x: m) {

        cout << x.first << ": " << x.second << endl;
    }
}

template<class K, class V>
K scanMapKey(map<K,V> m) {

    bool success = false;

    K key;

    while(!success) {

        readVar(cin, key, "Input: ");

        if (m.find(key) == m.end()) {

            cout << "La clave no existe!" << endl;

        }

        else {

            success = true;

        }

     }

    return key;

}

template<class T>
void removeVectorElement(vector<T> &v, T value) {

    v.erase(remove(v.begin(), v.end(), value), v.end());
}

#endif // CPP_UTILS_H
