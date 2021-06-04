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
        Terrain(int id, float area, float cost);
        virtual ~Terrain() {}

        void setID(int id);

        int getID() const;
        float getArea() const;
        float getCost() const;

        virtual void readFromConsole();
        virtual bool saveInDB() = 0;

        virtual void print();
        virtual void printContent() = 0;
};

// Clases hijas: tipos concretos de terreno

class AnimalTerrain: public Terrain {

    protected:

        vector<Animal> animals;
        int animal_type_id;
        static map<int, string> animal_types;

    public:

        AnimalTerrain() {}
        AnimalTerrain(int id, float area, float cost);
        AnimalTerrain(int id, float area, vector<Animal> animals, float cost, int type_id);

        static void loadTypes(map<int, string> types_map);

        int getAnimalTypeID() const;
        string getAnimalType() const;

        void addAnimal(Animal a);
        void removeAnimal(int index);
        Animal getAnimal(int index);
        vector<Animal> getAnimals() const;
        int getNumAnimals() const;
        bool isEmpty() const;

        void readFromConsole();
        bool saveInDB();

        void calculateWeightStatistics();

        void printContent();
        void print();

};

class CropTerrain: public Terrain {

    protected:

        static map<int, string> crop_types;
        int crop_type_id;

    public:

        CropTerrain() {}
        CropTerrain(int id, float area, float cost);
        CropTerrain(int id, float area, int crop_id, float cost);

        static void loadTypes(map<int, string> types_map);

        int getCropTypeID() const;
        string getCropType() const;

        void readFromConsole();
        bool saveInDB();

        void printContent();
        void print();

};

#endif // TERRAIN_H
