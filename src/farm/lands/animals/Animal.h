#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
using namespace std;

class Animal {

    protected:

        int id; // Identificación única del animal
        float weight; // Peso
        string name; // Nombre propio
        string type; // Tipo de animal (raza y/o especie)


    public:

        Animal();
        Animal(int id, string name, float weight, string type);

        // Getters

        int getID() const;
        float getWeight() const;
        string getName() const;
        string getType() const;

        // Setters

        void setID(int id);


        // Sobrecarga de operadores de inserción y extracción

        friend ostream & operator<<(ostream &out, const Animal &a);
        friend istream & operator>>(istream &in, Animal &a);
};

#endif // ANIMAL_H
