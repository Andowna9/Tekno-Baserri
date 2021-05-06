#ifndef CROP_H
#define CROP_H

#include <string>
using namespace std;

class Crop
{

private:

    int id; // IdentificaciÃ³n Ãºnica del animal
    string name; // Nombre


public:
    Crop();
    Crop(int id, string name);


    // Getters

    int getId() const;
    string getName() const;


    // Sobrecarga de operadores de inserciÃ³n y extracciÃ³n

    friend ostream & operator<<(ostream &out, const Crop &a);


};

#endif // CROP_H
