#ifndef CROP_H
#define CROP_H

#include <string>
using namespace std;

class Crop
{

private:

    string name; // Nombre


public:
    Crop() {}
    Crop(string name);


    // Getters

    string getName() const;
    void setName(string name);


    // Sobrecarga de operadores de inserciÃ³n y extracciÃ³n

    friend ostream & operator<<(ostream &out, const Crop &a);


};

#endif // CROP_H
