extern "C" {
    #include <logger.h>
}

#include <DBManager.h>
#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

const char* DBManager::DBPath = "teknobaserri.db"; // Inicialización de variable estática para la ruta de acceso
sqlite3* DBManager::DB;
const char* log_file_txt = "database_errors.log";

// Método privado que crea las tablas correspondientes en caso de que no existan

void DBManager::prepareParkingDB() {

    open_logger(log_file_txt);

    // Tabla Vehículo

    string sql = "CREATE TABLE IF NOT EXISTS vehicle("
                 "license_plate TEXT PRIMARY KEY,"
                 "brand TEXT,"
                 "color TEXT)";

    int code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {
        add_to_log("Error preparando la tabla Vehículo. Código: %d", code);
    }

    sql = "CREATE TABLE IF NOT EXISTS user("
          "username TEXT NOT NULL PRIMARY KEY,"
          "pswdSHA1 TEXT NOT NULL);"
          "INSERT OR IGNORE INTO user VALUES ('admin', 'd033e22ae348aeb5660fc2140aec35850c4da997');";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {
        add_to_log("Error preparando la tabla de usuarios. Código: %d", code);
    }

    close_logger();

}

void DBManager::prepareFarmDB() {

    open_logger(log_file_txt);

    // Tabla Cultivo

    string sql = "CREATE TABLE IF NOT EXISTS crop_type("
    "id INTEGER PRIMARY KEY,"
    "name TEXT NOT NULL"
    ");"
    "INSERT OR IGNORE INTO crop_type(id, name) VALUES"
    "(1, 'Lechuga'),"
    "(2, 'Pepino'),"
    "(3, 'Zanahoria'),"
    "(4, 'Tomate');";

    int code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK){

        add_to_log("Error al preparar la tabla Cultivo. Código: %i", code);
    }

    // Tabla Terreno

    sql = "CREATE TABLE IF NOT EXISTS terrain("
          "id TEXT PRIMARY KEY,"
          "area REAL,"
          "cost REAL,"
          "crop_in_use INTEGER,"
          "FOREIGN KEY(crop_in_use) REFERENCES crop_type(id)"
          ");";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK){

        add_to_log("Error al preparar la tabla Terreno. Código: %i", code);
    }

    // Tabla Tipo de Animal

    sql = "CREATE TABLE IF NOT EXISTS animal_type("
          "id INTEGER PRIMARY KEY,"
          "name TEXT NOT NULL,"
          "life_expectancy INTEGER);"
          "INSERT OR IGNORE INTO animal_type(id, name, life_expectancy) VALUES"
          "(1, 'Cerdo', 20),"
          "(2, 'Gallina', 15),"
          "(3, 'Oveja', 22);";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {
        add_to_log("Error al preparar tabla de tipos de animales. Código: %d", code);
    }

    // Tabla Animal

    sql = "CREATE TABLE IF NOT EXISTS animal("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT,"
          "weight REAL,"
          "birth_date TEXT,"
          "type INTEGER,"
          "terrain INTEGER,"
          "FOREIGN KEY(type) REFERENCES animal_type(id),"
          "FOREIGN KEY(terrain) REFERENCES terrain(id),"
          "CHECK(weight > 0)"
          ")";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {
        add_to_log("Error al preparar la tabla Animal. Código: %i", code);
    }


}

void DBManager::initDB() {

    DBManager::connect();

    DBManager::prepareParkingDB();
    DBManager::prepareFarmDB();


    CropTerrain::loadTypes(DBManager::getAvailableTypes(DBManager::CROP_TYPE));
    Animal::loadTypes(DBManager::getAvailableTypes(DBManager::ANIMAL_TYPE));

    DBManager::disconnect();

}

void DBManager::connect() {

    open_logger(log_file_txt);

    int code = sqlite3_open(DBPath, &DB);

    if (code != SQLITE_OK) {
        add_to_log("Error al abrir la base de datos. Código: %i", code);
    }

    close_logger();

}

void DBManager::disconnect() {

     open_logger(log_file_txt);

     int code = sqlite3_close(DB);

     if (code != SQLITE_OK) {
         add_to_log("Error al cerrar la base de datos. Código: %i", code);
      }

     close_logger();

}

///////////////////// PARKING ////////////////////////////

bool DBManager::isVehicleRegistered(const char* l_plate) {

    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM vehicle WHERE license_plate=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, l_plate, -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return code == SQLITE_ROW;

}

// Vehículo a partir de fila SQLite

Vehicle vehicleFromRow(sqlite3_stmt* stmt) {

    string license((const char*) sqlite3_column_text(stmt, 0));
    string brand((const char*) sqlite3_column_text(stmt, 1));
    string color((const char*) sqlite3_column_text(stmt, 2));

    return Vehicle(license, brand, color);
}


Vehicle DBManager::retrieveVehicle(const char* l_plate) {

    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM vehicle WHERE license_plate=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, l_plate, -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);

    if (code == SQLITE_ROW) {

        return vehicleFromRow(stmt);
    }

    sqlite3_finalize(stmt);

    return Vehicle();
}

void DBManager::insertVehicle(Vehicle& v) {

    open_logger(log_file_txt);

    sqlite3_stmt* stmt;
    string sql = "INSERT INTO vehicle(license_plate, brand, color) VALUES (?, ?, ?)";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, v.getLicensePlate().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, v.getBrand().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, v.getColor().c_str(), -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);
    if (code != SQLITE_DONE) {
        add_to_log("Error al introducir vehículo con mátricula %s. Código: %i", v.getLicensePlate().c_str(), code);
    }

    sqlite3_finalize(stmt);

    close_logger();
}

void DBManager::deleteVehicle(const char* l_plate) {

    open_logger(log_file_txt);

    sqlite3_stmt* stmt;
    string sql = "DELETE FROM vehicle WHERE license_plate=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, l_plate, -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);
    if (code != SQLITE_DONE) {
        add_to_log("Error al borrar vehículo con matrícula %s. Código: %i", l_plate, code);
    }

    sqlite3_finalize(stmt);

    close_logger();
}

void DBManager::retrieveAllVehicles() {

    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM vehicle";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        Vehicle v = vehicleFromRow(stmt);

        cout << v;
    }

    sqlite3_finalize(stmt);

}

string DBManager::retrievePassword(const char* username) {

    sqlite3_stmt* stmt;
    string sql = "SELECT pswdSHA1 FROM user WHERE username=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);

    if (code == SQLITE_ROW) {

        string password = (const char*) sqlite3_column_text(stmt, 0);
        sqlite3_finalize(stmt);

        return password;
    }

    sqlite3_finalize(stmt);

    return "";
}

///////////////////// GRANJA ////////////////////////////

vector<Animal> DBManager::retriveAnimals(int terrain_id) {

    open_logger(log_file_txt);

    vector<Animal> animals;
    sqlite3_stmt* stmt;
    string sql = "SELECT id, name, weight, type WHERE terrain=?";
    int code = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, terrain_id);
    if (code != SQLITE_OK) {
        add_to_log("Error al acceder a la consulta: %s. Código: %i", sqlite3_errmsg(DB), code);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        string name((const char*)sqlite3_column_text(stmt, 1));
        float weight = (float) sqlite3_column_double(stmt, 2);
        int type = sqlite3_column_int(stmt, 3);

        Animal a(id, name, weight, type);
        animals.push_back(a);
    }

    sqlite3_finalize(stmt);

    close_logger();

    return animals;
}

void DBManager::insertAnimal(Animal& a, int type_id) {

    open_logger(log_file_txt);

    sqlite3_stmt* stmt;

    string sql = "INSERT INTO animal(name, weight, birth_date, type) VALUES (?, ?, DATE('now'), ?)";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, a.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, a.getWeight());
    sqlite3_bind_int(stmt, 3, type_id);

    int code = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    if (code != SQLITE_DONE) {
        add_to_log("Error al introducir animal. Código: %i", code);
    }

    else {

        sql = "SELECT last_insert_rowid()";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        code = sqlite3_step(stmt);

        if (code == SQLITE_ROW) {

            int id = sqlite3_column_int(stmt, 0);
            a.setID(id);
        }

        else {
            add_to_log("Error al obtener el id del animal nuevo. Código: %i", code);

        }

        sqlite3_finalize(stmt);

    }

    close_logger();

}

void DBManager::removeAnimal(int id) {

    open_logger(log_file_txt);

    sqlite3_stmt* stmt;

    string sql = "DELETE FROM animal WHERE id=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    int code = sqlite3_step(stmt);

    if (code != SQLITE_DONE) {
        add_to_log("Error al borrar animal. Código: %i", code);
    }

    sqlite3_finalize(stmt);

    close_logger();
}



map<int, string> DBManager::getAvailableTypes(TypeTable type_table) {

    map<int, string> available_types;

    string table_name;

    switch (type_table) {

        case ANIMAL_TYPE:

            table_name = "animal_type";

            break;

        case CROP_TYPE:

            table_name = "crop_type";

            break;
    }

    sqlite3_stmt* stmt;

    string sql = "SELECT id, name FROM " + table_name;

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int type_id = sqlite3_column_int(stmt, 0);
        string type_name((const char*)sqlite3_column_text(stmt, 1));

        available_types[type_id] = type_name;

    }

    sqlite3_finalize(stmt);

    return available_types;

}

string DBManager::getCrop(int id) {


    sqlite3_stmt* stmt;

    string sql = "SELECT name FROM crop WHERE id=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    string s;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        s = (const char*)sqlite3_column_text(stmt, 1);

    }

    sqlite3_finalize(stmt);

    return s;

}

vector<Terrain*> DBManager::retrieveTerrains() {

    vector<Terrain*> terrains;

    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM terrain";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    while(sqlite3_step(stmt) == SQLITE_ROW) {

        int terrain_id = sqlite3_column_int(stmt, 0);
        float area = (float) sqlite3_column_double(stmt, 1);
        float cost = (float) sqlite3_column_double(stmt, 2);
        int crop_id = sqlite3_column_int(stmt, 3);

        Terrain* t;

        // Si id del cultivo es NULL, se trata de un terreno de animales

        if (sqlite3_column_type(stmt, 2) == SQLITE_NULL) {

            vector<Animal> animals = retriveAnimals(terrain_id);
            t = new AnimalTerrain(area, animals, cost);


        }

        // En caso contrario, se trata de un terreno de cultivo

        else {


            t = new CropTerrain(area, crop_id, cost);

        }

        terrains.push_back(t);
    }

    sqlite3_finalize(stmt);

    return terrains;
}

