#include "Terrain.h"
#include <iostream>
using namespace std;

Terrain::Terrain(float area, float cost) {

    this->area = area;
    this->cost = cost;
}

void Terrain::print() {


}

AnimalTerrain::AnimalTerrain(float area, float cost): Terrain(area, cost) {}


AnimalTerrain::AnimalTerrain(float area, vector<Animal> animals, float cost): Terrain(area, cost) {

    this->animals = animals;
}

void AnimalTerrain::print() {


}

CropTerrain::CropTerrain(float area, float cost): Terrain(area, cost) {}

CropTerrain::CropTerrain(float area, Crop crop, float cost): Terrain(area, cost) {

    //this->crop = crop;
}

void CropTerrain::print() {

}


