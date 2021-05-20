#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <map>
using namespace std;

class Animal {

    private:

        int id; // Identificación única del animal
        float weight; // Peso
        string name; // Nombre propio


    public:

        Animal();
        Animal(int id, string name, float weight);

        // Getters

        int getID() const;
        float getWeight() const;
        string getName() const;

        // Setters

        void setID(int id);

        // Sobrecarga de operadores de inserción y extracción

        friend ostream & operator<<(ostream &out, const Animal &a);
        friend istream & operator>>(istream &in, Animal &a);
};

#endif // ANIMAL_H
