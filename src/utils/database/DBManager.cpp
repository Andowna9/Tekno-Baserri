#include <DBManager.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const char* DBManager::DBPath = "teknobaserri.db"; // Inicialización de variable estática para la ruta de acceso
sqlite3* DBManager::DB;

// Método privado que crea las tablas correspondientes en caso de que no existan

void DBManager::initDB() {

    // Tabla Vehículo

    string sql = "CREATE TABLE IF NOT EXISTS vehicle("
                 "license_plate TEXT PRIMARY KEY,"
                 "brand TEXT,"
                 "color TEXT)";

    int code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {

        cerr << "Error preparando la tabla Vehículo" << endl;
    }

    // TODO Resto de tablas

}

void DBManager::connect() {

    int code = sqlite3_open(DBPath, &DB);

    if (code != SQLITE_OK) {

        cerr << "Error al abrir la base de datos " << DBPath << endl;
    }

    else {

        cout << "Base de datos abierta con éxito!" << endl;

        initDB();
    }

}

void DBManager::disconnect() {

     int code = sqlite3_close(DB);

     if (code != SQLITE_OK) {

         cerr << "Error al cerrar la base de datos!" << endl;
      }

}

Vehicle DBManager::retrieveVehicle(const char* l_plate) {

    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM vehicle WHERE license_plate=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, l_plate, -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);

    Vehicle v;

    if (code == SQLITE_DONE) {

        string license_plate(l_plate);
        string brand((const char*)sqlite3_column_text(stmt, 2));
        string color((const char*)sqlite3_column_text(stmt, 3));

        v.setLicensePLate(license_plate);
        v.setBrand(brand);
        v.setColor(color);
    }

    return v;
}

void DBManager::insertVehicle(Vehicle v) {

    sqlite3_stmt* stmt;

    string sql = "INSERT INTO vehicle(license_plate, brand, color) VALUES (?, ?, ?)";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, v.getLicensePlate().c_str(), -1, SQLITE_STATIC);

    sqlite3_bind_text(stmt, 2, v.getBrand().c_str(), -1, SQLITE_STATIC);

    sqlite3_bind_text(stmt, 3, v.getColor().c_str(), -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);

    if (code != SQLITE_DONE) {

        cerr << "Error al introducir vehículo con mátricula " << v.getLicensePlate() << endl;
    }

    sqlite3_finalize(stmt);
}

void DBManager::deleteVehicle(const char* l_plate) {

    sqlite3_stmt* stmt;

    string sql = "DELETE FROM vehicle WHERE license_plate=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, l_plate, -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);

    if (code != SQLITE_DONE) {

        cerr << "Error al borrar vehículo con matrícula " << l_plate << endl;
    }

    sqlite3_finalize(stmt);

}

