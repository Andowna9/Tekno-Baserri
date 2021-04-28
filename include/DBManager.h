#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "sqlite3.h"
#include "src/parking/vehicle/Vehicle.h"

// Clase gestora de acceso a la base de datos

class DBManager {

    private:
        // Variables estáticas

        static const char* DBPath;
        static sqlite3* DB;

        DBManager() {} // Constructor privado, ya que no se requerirán instancias

        static void initDB();

    public:

        // Métodos estáticos de utilidad

        static void connect();
        static void disconnect();

        static Vehicle retrieveVehicle(const char* l_plate);
        static void insertVehicle(Vehicle v);
        static void deleteVehicle(const char* l_plate);

};

#endif // DBMANAGER_H
