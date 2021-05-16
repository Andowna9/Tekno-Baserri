#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <map>
#include "animals/Animal.h"

using namespace std;

// Clase base

class Terrain {

    private:

        float area;
        float cost;


    public:

        Terrain() {}
        Terrain(float area, float cost);
        virtual ~Terrain() {}

        virtual void readFromConsole();
        virtual void print();
};

// Clases hijas: tipos concretos de terreno

class AnimalTerrain: public Terrain {

    private:

        vector<Animal> animals;

    public:

        AnimalTerrain() {}
        AnimalTerrain(float area, float cost);
        AnimalTerrain(float area, vector<Animal> animals, float cost);

        void print();

};

class CropTerrain: public Terrain {

    private:

        static map<int, string> crop_types;

        int crop_id;

    public:

        CropTerrain() {}
        CropTerrain(float area, float cost);
        CropTerrain(float area, int crop_id, float cost);

        static void loadTypes(map<int, string> map);

        void readFromConsole();
        void print();

};

#endif // TERRAIN_H
