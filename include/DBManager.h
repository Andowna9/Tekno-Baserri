#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <sqlite3.h>
#include "src/parking/vehicle/Vehicle.h"
#include "src/farm/animals/animal/Animal.h"
#include <vector>
#include <unordered_map>

// Clase gestora de acceso a la base de datos

class DBManager {

    private:

        // Variables estáticas

        static const char* DBPath;
        static sqlite3* DB;

        DBManager() {} // Constructor privado, ya que no se requerirán instancias

        static void prepareParkingDB();
        static void prepareFarmDB();

    public:

        enum DBName {PARKING, FARM};

        // Métodos estáticos de utilidad

        static void connect(DBName name);
        static void disconnect();

        // Parking

        static Vehicle retrieveVehicle(const char* l_plate);
        static void insertVehicle(Vehicle& v);
        static void deleteVehicle(const char* l_plate);
        static bool isVehicleRegistered(const char* l_plate);
        static void retrieveAllVehicles();

        static string retrievePassword(const char* username);

        // Granja

        static vector<Animal> retriveAnimals();
        static void insertAnimal(Animal& a, int type_id);
        static void removeAnimal(int id);
        static unordered_map<string, int> getAnimalTypes();

};

#endif // DBMANAGER_H
