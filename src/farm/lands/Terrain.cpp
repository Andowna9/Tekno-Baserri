#include "Terrain.h"
#include "cpp_utils.h"
#include <iostream>
#include <DBManager.h>
using namespace std;

Terrain::Terrain(float area, float cost) {

    this->id = -1;
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

    cout << "Área (hectáreas): ";
    readVar(cin, this->area);

    cout << "Precio Pagado (euros): ";
    readVar(cin, this->cost);
}

void Terrain::print() {

    cout << "Área: " << area << " hectáreas" << endl;
    cout << "Coste de compra: " << cost << " €" << endl;

}

AnimalTerrain::AnimalTerrain(float area, float cost): Terrain(area, cost) {}


map<int, string> AnimalTerrain::animal_types;

AnimalTerrain::AnimalTerrain(float area, vector<Animal> animals, float cost, int type_id): Terrain(area, cost) {

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

CropTerrain::CropTerrain(float area, float cost): Terrain(area, cost) {}

CropTerrain::CropTerrain(float area, int crop_id, float cost): Terrain(area, cost) {

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


