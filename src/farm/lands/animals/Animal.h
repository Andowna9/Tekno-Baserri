#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <map>
using namespace std;

class Animal {

    private:

        static map<int, string> animal_types;

        int id; // Identificación única del animal
        float weight; // Peso
        string name; // Nombre propio
        int type_id; // Tipo de animal (raza y/o especie)


    public:

        Animal();
        Animal(int id, string name, float weight, int type_id);

        // Getters

        int getID() const;
        float getWeight() const;
        string getName() const;
        string getType() const;
        int getTypeID() const;

        // Setters

        void setID(int id);

        static void loadTypes(map<int, string> map);


        // Sobrecarga de operadores de inserción y extracción

        friend ostream & operator<<(ostream &out, const Animal &a);
        friend istream & operator>>(istream &in, Animal &a);
};

#endif // ANIMAL_H
