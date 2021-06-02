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

        int getID() const;
        float getArea() const;
        float getCost() const;

        virtual void readFromConsole();
        virtual bool saveInDB() = 0;

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

        int getAnimalTypeID() const;

        void addAnimal(Animal a);
        vector<Animal> getAnimals();
        bool isEmpty();

        void readFromConsole();
        bool saveInDB();

        void printContent();
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
        bool saveInDB();

        void printContent();
        void print();

};

#endif // TERRAIN_H
