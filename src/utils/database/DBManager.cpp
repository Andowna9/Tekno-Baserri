extern "C" {
    #include <logger.h>
}

#include <DBManager.h>
#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

const char* DBManager::DBPath = "teknobaserri.db"; // Inicialización de variable estática para la ruta de acceso
sqlite3* DBManager::DB = NULL;
const char* log_file_txt = "database_errors.log";

// Método privado que crea las tablas correspondientes en caso de que no existan

void DBManager::prepareParkingDB() {

    open_logger(log_file_txt);
    string sql; int code;

    // Tabla Vehículo

    sql = "CREATE TABLE IF NOT EXISTS vehicle("
                 "license_plate TEXT PRIMARY KEY,"
                 "brand TEXT,"
                 "color TEXT)";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

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
    string sql; int code;

    // Tabla Cultivo

    sql = "CREATE TABLE IF NOT EXISTS crop_type("
    "id INTEGER PRIMARY KEY,"
    "name TEXT NOT NULL"
    ");"
    "INSERT OR IGNORE INTO crop_type(id, name) VALUES"
    "(1, 'Lechuga'),"
    "(2, 'Pepino'),"
    "(3, 'Zanahoria'),"
    "(4, 'Tomate');";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK){

        add_to_log("Error al preparar la tabla Cultivo. Código: %i", code);
    }

    // Tabla Terreno

    sql = "CREATE TABLE IF NOT EXISTS terrain("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "area REAL,"
          "cost REAL"
          ");";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK){

        add_to_log("Error al preparar la tabla Terreno. Código: %i", code);
    }

    // Tabla Terrenos Cultivo

    sql = "CREATE TABLE IF NOT EXISTS crop_terrain("
          "id TEXT PRIMARY KEY,"
          "type INT,"
          "FOREIGN KEY(id) REFERENCES terrain(id) ON DELETE CASCADE,"
          "FOREIGN KEY(type) REFERENCES crop_type(id)"
          ");";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK){

        add_to_log("Error al preparar la tabla Terreno-Cultivo. Código: %i", code);
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

    // Tabla Terrenos Animal

    sql = "CREATE TABLE IF NOT EXISTS animal_terrain("
          "id TEXT PRIMARY KEY,"
          "type INT,"
          "FOREIGN KEY(id) REFERENCES terrain(id) ON DELETE CASCADE,"
          "FOREIGN KEY(type) REFERENCES animal_type(id)"
          ");";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK){

        add_to_log("Error al preparar la tabla Terreno-Animal. Código: %i", code);
    }


    // Tabla Animal

    sql = "CREATE TABLE IF NOT EXISTS animal("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT,"
          "weight REAL,"
          "birth_date TEXT,"
          "terrain INTEGER,"
          "FOREIGN KEY(terrain) REFERENCES animal_terrain(id) ON DELETE CASCADE,"
          "CHECK(weight > 0)"
          ")";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {
        add_to_log("Error al preparar la tabla Animal. Código: %i", code);
    }

    close_logger();

}

void DBManager::initDB() {

    DBManager::connect();

    DBManager::prepareParkingDB();
    DBManager::prepareFarmDB();


    CropTerrain::loadTypes(DBManager::getAvailableTypes(DBManager::CROP_TYPE));
    AnimalTerrain::loadTypes(DBManager::getAvailableTypes(DBManager::ANIMAL_TYPE));

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

bool DBManager::isDBOpen() {

    return DB != NULL;
}

void DBManager::disconnect() {

     open_logger(log_file_txt);

     int code = sqlite3_close(DB);

     if (code != SQLITE_OK) {
         add_to_log("Error al cerrar la base de datos. Código: %i", code);
      }

     else {

         DB = NULL;
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

bool DBManager::insertVehicle(Vehicle& v) {

    open_logger(log_file_txt);

    sqlite3_stmt* stmt;
    bool success;

    string sql = "INSERT INTO vehicle(license_plate, brand, color) VALUES (?, ?, ?)";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, v.getLicensePlate().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, v.getBrand().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, v.getColor().c_str(), -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);
    if (code != SQLITE_DONE) {
        add_to_log("Error al introducir vehículo con mátricula %s. Código: %i", v.getLicensePlate().c_str(), code);
        success = false;

    } else {
        success = true;
    }

    sqlite3_finalize(stmt);

    close_logger();

    return success;
}

bool DBManager::deleteVehicle(const char* l_plate) {

    open_logger(log_file_txt);

    bool success;

    sqlite3_stmt* stmt;
    string sql = "DELETE FROM vehicle WHERE license_plate=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, l_plate, -1, SQLITE_STATIC);

    int code = sqlite3_step(stmt);
    if (code != SQLITE_DONE) {
        add_to_log("Error al borrar vehículo con matrícula %s. Código: %i", l_plate, code);
        success = false;

    } else {
        success = true;
    }

    sqlite3_finalize(stmt);

    close_logger();

    return success;
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

        Animal a(id, name, weight);
        animals.push_back(a);
    }

    sqlite3_finalize(stmt);

    close_logger();

    return animals;
}

void DBManager::insertAnimal(Animal& a, string birth_date) {

    open_logger(log_file_txt);

    sqlite3_stmt* stmt;

    string sql = "INSERT INTO animal(name, weight, birth_date) VALUES (?, ?, DATE(?))";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, a.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, a.getWeight());
    sqlite3_bind_text(stmt, 3, birth_date.c_str(),-1, SQLITE_STATIC);

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

int DBManager::getAnimalAge(int id) {

    int age = -1;

    open_logger(log_file_txt);

    sqlite3_stmt* stmt;

    string sql = "SELECT (julianday('now') - julianday(birth_date)) / 365 AS age FROM animal WHERE id=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    int code = sqlite3_step(stmt);

    if (code != SQLITE_ROW) {

        add_to_log("Error al obtener edad de animal. Código: %i", code);
    }

    else {

        age = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    close_logger();

    return age;

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

// TERRENOS //////

vector<Terrain*> DBManager::retrieveTerrains(vector<CropTerrain*> &crop_terrains, vector<AnimalTerrain*> &animal_terrains) {

    vector<Terrain*> terrains;
    string sql;

    sqlite3_stmt* stmt;

    sql = "SELECT t.id, area, cost, ct.type, at.type FROM terrain t LEFT OUTER JOIN crop_terrain ct ON t.id = ct.id LEFT OUTER JOIN animal_terrain at ON t.id = at.id;";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    while(sqlite3_step(stmt) == SQLITE_ROW) {

        int terrain_id = sqlite3_column_int(stmt, 0);
        float area = (float) sqlite3_column_double(stmt, 1);
        float cost = (float) sqlite3_column_double(stmt, 2);

        Terrain* t;

        if (sqlite3_column_type(stmt, 3) != SQLITE_NULL) {

            int cropType = sqlite3_column_int(stmt, 3);
            t = new CropTerrain(area, cropType, cost);

            crop_terrains.push_back((CropTerrain*) t);

        } else {

            int animalType = sqlite3_column_int(stmt, 4);
            vector<Animal> animals = retriveAnimals(terrain_id);

            t = new AnimalTerrain(area, animals, cost, animalType);

            animal_terrains.push_back((AnimalTerrain*) t);

        }

        terrains.push_back(t);
    }

    sqlite3_finalize(stmt);

    return terrains;
}

bool DBManager::insertTerrain(Terrain &t) {

    open_logger(log_file_txt);

    bool success;
    sqlite3_stmt* stmt;

    string sql = "INSERT INTO terrain(area, cost) VALUES (?, ?)";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_double(stmt, 1, t.getArea());
    sqlite3_bind_double(stmt, 2, t.getCost());

    int code = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    if (code != SQLITE_DONE) {
        add_to_log("Error al introducir terreno. Código: %i", code);
        success = false;
    }

    else {

        sql = "SELECT last_insert_rowid()";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        code = sqlite3_step(stmt);

        if (code == SQLITE_ROW) {

            int id = sqlite3_column_int(stmt, 0);
            t.setID(id);

            success = true;
        }

        else {
            add_to_log("Error al obtener el id del terreno nuevo. Código: %i", code);
            success = false;

        }

        sqlite3_finalize(stmt);

    }

    close_logger();

    return success;

}

bool DBManager::insertAnimalTerrain(AnimalTerrain& t) {

    open_logger(log_file_txt);

    bool success = insertTerrain(t);

    if (success) {
        sqlite3_stmt* stmt;
        int code;

        // Insertamos ahora dentro del AnimalTerrain
        string sql = "INSERT INTO animal_terrain(id, type) values (?, ?)";

        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

        sqlite3_bind_int(stmt, 1, t.getID()); // El ID se le acaba de asignar en insertTerrain(t)
        sqlite3_bind_int(stmt, 2, t.getAnimalTypeID());

        code = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (code!=SQLITE_DONE) {
            add_to_log("Error al insertar el terreno de animal. Código: %i", code);
            success = false;

        }

    } else {
        add_to_log("El terreno no se insertó de forma adecuada, abortada inserción de terreno animal.");

    }

    close_logger();

    return success;


}

bool DBManager::insertCropTerrain(CropTerrain& t) {

    open_logger(log_file_txt);

    bool success = insertTerrain(t);

    if (success) {
        sqlite3_stmt* stmt;
        int code;

        string sql = "INSERT INTO crop_terrain(id, type) values (?, ?)";

        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

        sqlite3_bind_int(stmt, 1, t.getID()); // El ID se le acaba de asignar en insertTerrain(t)
        sqlite3_bind_int(stmt, 2, t.getCropTypeID());

        code = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (code!=SQLITE_DONE) {
            add_to_log("Error al insertar el terreno de cultivo. Código: %i", code);
            success = false;

        }

    } else {
        add_to_log("El terreno no se insertó de forma adecuada, abortada inserción de terreno de cultivo.");

    }

    close_logger();

    return success;

}

bool DBManager::removeTerrain(int id) {

    open_logger(log_file_txt);

    bool success = true;

    sqlite3_stmt* stmt;
    string sql = "DELETE FROM terrain WHERE id = ?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1, id);

    int code = sqlite3_step(stmt);

    if (code != SQLITE_DONE) {

        add_to_log("Error al borrar terreno!. Código: %i", code);
        success = false;
    }

    close_logger();

    return success;
}

float DBManager::getTerrainCost(int id) {

    open_logger(log_file_txt);

    string sql = "SELECT cost from TERRAIN"
          "WHERE id = ?";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    float cost = -1; // Devolverá -1 en caso de error

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cost = sqlite3_column_double(stmt, 1);

    } else {
        add_to_log("Error al recuperar el coste del terreno.");
    }

    sqlite3_finalize(stmt);

    close_logger();
    return cost;

}

float DBManager::getTerrainArea(int id) {
    open_logger(log_file_txt);

    string sql = "SELECT area FROM terrain WHERE id = ?";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    float area = -1; // Devolverá -1 en caso de error

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        area = sqlite3_column_double(stmt, 1);
        add_to_log("Error al obtener el área del terreno.");

    }

    sqlite3_finalize(stmt);

    close_logger();
    return area;
}
