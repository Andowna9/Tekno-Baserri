#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <sqlite3.h>
#include "src/parking/vehicle/Vehicle.h"
#include "src/farm/lands/animals/Animal.h"
#include "src/farm/lands/Terrain.h"
#include <vector>
#include <map>

//void initDB();

// Clase gestora de acceso a la base de datos

class DBManager {

    private:

        // Variables estáticas

        static const char* DBPath;
        static sqlite3* DB;

        DBManager() {} // Constructor privado, ya que no se requerirán instancias

        static void prepareParkingDB();
        static void prepareFarmDB();
        static vector<Animal> retriveAnimals(int terrain_id);
        static string getCrop(int id);

    public:

        enum TypeTable {ANIMAL_TYPE, CROP_TYPE};

        // Métodos estáticos de utilidad

        static void initDB();
        static void connect();
        static void disconnect();
        static bool isDBOpen();

        // Parking

        static Vehicle retrieveVehicle(const char* l_plate);
        static bool insertVehicle(Vehicle& v);
        static bool deleteVehicle(const char* l_plate);
        static bool isVehicleRegistered(const char* l_plate);
        static void retrieveAllVehicles();

        static string retrievePassword(const char* username);

        // Granja

        static void insertAnimal(Animal& a, string birth_date, int animal_terrain_id);
        static void removeAnimal(int id);
        static int getAnimalAge(int id);
        static map<int, string> getAvailableTypes(TypeTable table);
        static vector<Terrain*> retrieveTerrains(vector<CropTerrain*> &crop_terrains, vector<AnimalTerrain*> &animal_terrains);

        static bool insertTerrain(Terrain& t);
        static bool insertAnimalTerrain(AnimalTerrain& t);
        static bool insertCropTerrain(CropTerrain& t);
        static bool removeTerrain(int id);
        static float getTerrainCost(int id);
        static float getTerrainArea(int id);

        friend void initDB();
};

#endif // DBMANAGER_H
