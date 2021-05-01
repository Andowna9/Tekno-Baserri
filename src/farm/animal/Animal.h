#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
using namespace std;

class Animal {

    private:

        int age;
        float weight;
        string name;


    public:

        Animal();

        // Sobrecarga de operadores de inserción y extracción

        friend ostream & operator<<(ostream &out, const Animal &a);
        friend istream & operator>>(istream &in, Animal &a);
};

#endif // ANIMAL_H
