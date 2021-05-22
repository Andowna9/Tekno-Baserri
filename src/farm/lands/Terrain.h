#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <map>
#include "animals/Animal.h"

using namespace std;

// Clase base

class Terrain {

    protected:

        float area;
        float cost;
        int id;


    public:

        Terrain() {}
        Terrain(float area, float cost);
        virtual ~Terrain() {}

        void setID(int id);

        int getID();
        float getArea();
        float getCost();

        virtual void readFromConsole();
        virtual void print();
};

// Clases hijas: tipos concretos de terreno

class AnimalTerrain: public Terrain {

    protected:

        vector<Animal> animals;
        int animal_type_id;
        static map<int, string> animal_types;

    public:

        AnimalTerrain() {}
        AnimalTerrain(float area, float cost);
        AnimalTerrain(float area, vector<Animal> animals, float cost, int type_id);

        static void loadTypes(map<int, string> types_map);

        int getAnimalTypeID();

        void readFromConsole();
        void print();

};

class CropTerrain: public Terrain {

    protected:

        static map<int, string> crop_types;
        int crop_type_id;

    public:

        CropTerrain() {}
        CropTerrain(float area, float cost);
        CropTerrain(float area, int crop_id, float cost);

        static void loadTypes(map<int, string> types_map);

        int getCropTypeID();

        void readFromConsole();
        void print();

};

#endif // TERRAIN_H
