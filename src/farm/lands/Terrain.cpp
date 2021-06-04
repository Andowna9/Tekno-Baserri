#include "Terrain.h"
#include "cpp_utils.h"
#include <iostream>
#include <DBManager.h>
using namespace std;

Terrain::Terrain(int id, float area, float cost) {

    this->id = id;
    this->area = area;
    this->cost = cost;
}

void Terrain::setID(int id) {
    this->id = id;
}

int Terrain::getID() const {
    return id;
}

float Terrain::getArea() const {
    return this->area;

}

float Terrain::getCost() const {
    return this->cost;
}

void Terrain::readFromConsole() {

    readVar(cin, this->area, "Área (hectáreas): ");

    readVar(cin, this->cost, "Precio Pagado (euros): ");
}

void Terrain::print() {

    cout << "Área: " << area << " hectáreas" << endl;
    cout << "Coste de compra: " << cost << " €" << endl;

}

AnimalTerrain::AnimalTerrain(int id, float area, float cost): Terrain(id, area, cost) {}


map<int, string> AnimalTerrain::animal_types;

AnimalTerrain::AnimalTerrain(int id, float area, vector<Animal> animals, float cost, int type_id): Terrain(id, area, cost) {

    this->animal_type_id = type_id;
    this->animals = animals;
}

int AnimalTerrain::getAnimalTypeID() const {
    return this->animal_type_id;
}

void AnimalTerrain::loadTypes(map<int, string> map) {

    animal_types = map;
}

void AnimalTerrain::readFromConsole() {

    Terrain::readFromConsole();

    cout << endl;
    cout << "------------------------------" << endl;
    cout << "Tipos de cultivos disponibles: " <<  endl;
    cout << "------------------------------" << endl;
    printMap(animal_types);
    cout << "------------------------------" << endl;

    int type_id = scanMapKey(animal_types);
    this->animal_type_id = type_id;
}

bool AnimalTerrain::saveInDB() {

    if (DBManager::isDBOpen()) {

        return DBManager::insertAnimalTerrain(*this);
    }

    return false;
}

void AnimalTerrain::printContent() {

    cout << "Especie: " << animal_types.at(animal_type_id) << endl;
    cout << "Número de animales: " << animals.size() << endl;
}

void AnimalTerrain::print() {

    cout << "TERRENO DE ANIMALES" << endl;
    cout << "----------------------" << endl;
    Terrain::print();

}

void AnimalTerrain::addAnimal(Animal a) {

    this->animals.push_back(a);
}

vector<Animal> AnimalTerrain::getAnimals() const {

    return this->animals;
}

bool AnimalTerrain::isEmpty() const {

    return this->animals.size() == 0;
}

int AnimalTerrain::getNumAnimals() const {

    return this->animals.size();
}

string AnimalTerrain::getAnimalType() const {

    return this->animal_types[animal_type_id];
}

Animal AnimalTerrain::getAnimal(int index) {

    Animal a = animals.at(index);

    return a;
}

void AnimalTerrain::calculateWeightStatistics() {

    if (animals.size() == 0) {

        cout << "Sin estadísticas" << endl;
    }

    else {


        float max = animals[0].getWeight();
        float min = animals[0].getWeight();
        float sum = animals[0].getWeight();

        for (unsigned int i = 1; i < animals.size(); i++) {

            Animal a = animals[i];

            sum += a.getWeight();

            if (a.getWeight() > max) {

                max = a.getWeight();
            }

            if (a.getWeight() < min) {

                min = a.getWeight();
            }
        }

        cout << "// Peso //" << endl << endl;

        cout << "Máximo: " << max << endl;
        cout << "Mínimo: " << min << endl;
        cout << "Media: " << sum / animals.size() << endl;

    }
}

void AnimalTerrain::removeAnimal(int index) {

  animals.erase(animals.begin() + index);

}


map<int, string> CropTerrain::crop_types;

void CropTerrain::loadTypes(map<int, string> map) {

    crop_types = map;
}

int CropTerrain::getCropTypeID() const {
    return crop_type_id;
}

string CropTerrain::getCropType() const {

    return crop_types[crop_type_id];
}

CropTerrain::CropTerrain(int id, float area, float cost): Terrain(id, area, cost) {}

CropTerrain::CropTerrain(int id, float area, int crop_id, float cost): Terrain(id, area, cost) {

    this->crop_type_id = crop_id;
}

void CropTerrain::readFromConsole() {

    Terrain::readFromConsole();

    cout << endl;
    cout << "------------------------------" << endl;
    cout << "Tipos de cultivos disponibles: " <<  endl;
    cout << "------------------------------" << endl;
    printMap(crop_types);
    cout << "------------------------------" << endl;

    int type_id = scanMapKey(crop_types);
    this->crop_type_id = type_id;

}

bool CropTerrain::saveInDB() {

    if (DBManager::isDBOpen()) {

        return DBManager::insertCropTerrain(*this);
    }

    return false;
}

void CropTerrain::printContent() {

    cout << "Producto: " << crop_types.at(crop_type_id) << endl;

}

void CropTerrain::print() {

    cout << "TERRENO DE CULTIVO" << endl;
    cout << "----------------------" << endl;
    Terrain::print();
}


