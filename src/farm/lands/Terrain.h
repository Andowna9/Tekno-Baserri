#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "animals/Animal.h"
#include "crops/Crop.h"
using namespace std;

// Clase base

class Terrain {

    private:

        float area;
        float cost;


    public:

        Terrain(float area, float cost);
        virtual ~Terrain() {}

        virtual void print();
};

// Clases hijas: tipos concretos de terreno

class AnimalTerrain: public Terrain {

    private:

        vector<Animal> animals;

    public:

        AnimalTerrain(float area, float cost);
        AnimalTerrain(float area, vector<Animal> animals, float cost);

        void print();

};

class CropTerrain: public Terrain {

    private:

        string crop;

    public:

        CropTerrain(float area, float cost);
        CropTerrain(float area, Crop crop, float cost);

        void print();

};

#endif // TERRAIN_H
