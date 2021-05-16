#include "Terrain.h"
#include "cpp_utils.h"
#include <iostream>
using namespace std;

Terrain::Terrain(float area, float cost) {

    this->area = area;
    this->cost = cost;
}

void Terrain::readFromConsole() {

    cout << "Área (hectáreas): ";
    readVar(cin, this->area);

    cout << "Precio Pagado (euros): ";
    readVar(cin, this->cost);
}

void Terrain::print() {

    cout << "Área: " << area << endl;
    cout << "Coste de compra: " << cost << endl;

}

AnimalTerrain::AnimalTerrain(float area, float cost): Terrain(area, cost) {}


AnimalTerrain::AnimalTerrain(float area, vector<Animal> animals, float cost): Terrain(area, cost) {

    this->animals = animals;
}

void AnimalTerrain::print() {


    cout << "TERRENO DE ANIMALES" << endl;
    cout << "-------------------" << endl;
    Terrain::print();
    cout << "Número de animales: " << animals.size() << endl;

}

map<int, string> CropTerrain::crop_types;


void CropTerrain::loadTypes(map<int, string> map) {

    crop_types = map;
}

CropTerrain::CropTerrain(float area, float cost): Terrain(area, cost) {}

CropTerrain::CropTerrain(float area, int crop_id, float cost): Terrain(area, cost) {

    this->crop_id = crop_id;
}

void CropTerrain::readFromConsole() {

    Terrain::readFromConsole();

    cout << "------------------------------" << endl;
    cout << "Tipos de cultivos disponibles: " <<  endl;
    cout << "------------------------------" << endl;
    printMap(crop_types);
    cout << "------------------------------" << endl;

    int type_id = scanMapKey(crop_types);
    this->crop_id = type_id;

}

void CropTerrain::print() {

    cout << "TERRENO DE CULTIVO" << endl;
    cout << "-------------------" << endl;
    Terrain::print();
    cout << "Cultivo: " << crop_types.at(crop_id) << endl;
}


