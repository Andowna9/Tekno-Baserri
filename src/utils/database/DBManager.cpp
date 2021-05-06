#include <DBManager.h>
#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

const char* DBManager::DBPath = "teknobaserri.db"; // Inicialización de variable estática para la ruta de acceso
sqlite3* DBManager::DB;

// Método privado que crea las tablas correspondientes en caso de que no existan

void DBManager::prepareParkingDB() {

    // Tabla Vehículo

    string sql = "CREATE TABLE IF NOT EXISTS vehicle("
                 "license_plate TEXT PRIMARY KEY,"
                 "brand TEXT,"
                 "color TEXT)";

    int code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {

        cerr << "Error preparando la tabla Vehículo" << endl;
    }

}

void DBManager::prepareFarmDB() {

    // Tabla Tipo de Animal

    string sql = "CREATE TABLE IF NOT EXISTS animal_type("
          "id INTEGER PRIMARY KEY,"
          "name TEXT NOT NULL,"
          "life_expectancy INTEGER);"
          "INSERT INTO animal_type(id, name, life_expectancy) VALUES"
          "(1, 'Cerdo', 20),"
          "(2, 'Gallina', 15),"
          "(3, 'Oveja', 22);";

    int code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {

        cerr << "Error al preparar tabla de tipos de animales" << endl;
    }

    // Tabla Animal

    sql = "CREATE TABLE IF NOT EXISTS animal("
          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
          "name TEXT,"
          "weight REAL,"
          "birth_date TEXT,"
          "type INTEGER,"
          "FOREIGN KEY(type) REFERENCES animal_type(id),"
          "CHECK(weight > 0)"
          ")";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK) {

        cerr << "Error al preparar la tabla Animal" << endl;
    }

    // Tabla Cultivo

    sql = "CREATE TABLE IF NOT EXISTS crop("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "name TEXT,"
    ");"
    "INSERT INTO crop(id, name) VALUES"
    "(1, Lechuga),"
    "(2, Pepino),"
    "(3, Zanhaoria),"
    "(4, Tomate)";

    code = sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL);

    if (code != SQLITE_OK){

        cerr << "Error al preparar la tabla Cultivo" << endl;
    }

}

void DBManager::connect(DBName name) {

    int code = sqlite3_open(DBPath, &DB);

    if (code != SQLITE_OK) {

        cerr << "Error al abrir la base de datos " << DBPath << endl;
    }

    else {

        cout << "Base de datos abierta con éxito!" << endl;

        // Dependiendo de la constante proporcionada, se prepara la BD de la granja o el parking

        switch(name) {

            case PARKING:

                prepareParkingDB();
                break;

            case FARM:

                prepareFarmDB();
                break;
        }

    }

}

void DBManager::disconnect() {

     int code = sqlite3_close(DB);

     if (code != SQLITE_OK) {

         cerr << "Error al cerrar la base de datos!" << endl;
      }

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

    return Vehicle();
}

void DBManager::insertVehicle(Vehicle& v) {

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

void DBManager::retrieveAllVehicles() {

    sqlite3_stmt* stmt;

    string sql = "SELECT * FROM vehicle";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        Vehicle v = vehicleFromRow(stmt);

        cout << v;
    }

}

///////////////////// GRANJA ////////////////////////////

vector<Animal> DBManager::retriveAnimals() {

    vector<Animal> animals;

    sqlite3_stmt* stmt;

    string sql = "SELECT a.id, a.name, a.weight, t.name FROM animal a INNER JOIN animal_type t ON a.type = t.id";

    int code = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    if (code != SQLITE_OK) {

        cerr << sqlite3_errmsg(DB) << endl;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        string name((const char*)sqlite3_column_text(stmt, 1));
        float weight = (float) sqlite3_column_double(stmt, 2);
        string type((const char*)sqlite3_column_text(stmt, 3));

        Animal a(id, name, weight, type);
        animals.push_back(a);
    }

    sqlite3_finalize(stmt);

    return animals;
}

void DBManager::insertAnimal(Animal& a, int type_id) {


    sqlite3_stmt* stmt;

    string sql = "INSERT INTO animal(name, weight, birth_date, type) VALUES (?, ?, DATE('now'), ?)";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, a.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, a.getWeight());
    sqlite3_bind_int(stmt, 3, type_id);

    int code = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    if (code != SQLITE_DONE) {

        cerr << "Error al introducir animal" << endl;
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

            cerr << "Error al obtener el id del animal nuevo!" << endl;

        }

        sqlite3_finalize(stmt);

    }

}

void DBManager::removeAnimal(int id) {

    sqlite3_stmt* stmt;

    string sql = "DELETE FROM animal WHERE id=?";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    int code = sqlite3_step(stmt);

    if (code != SQLITE_DONE) {

        cerr << "Error al borrar animal" << endl;
    }

    sqlite3_finalize(stmt);

}



unordered_map<string, int> DBManager::getAnimalTypes() {

    unordered_map<string, int> available_types;

    sqlite3_stmt* stmt;

    string sql = "SELECT id, name FROM animal_type";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int type_id = sqlite3_column_int(stmt, 0);
        string type_name((const char*)sqlite3_column_text(stmt, 1));

        available_types[type_name] = type_id;

    }

    sqlite3_finalize(stmt);

    return available_types;

}

vector<Crop> DBManager::getCrops() {

    vector<Crop> crops;

    sqlite3_stmt* stmt;

    string sql = "SELECT id, name FROM crop ";

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        string name((const char*)sqlite3_column_text(stmt, 1));


        Crop c(id, name);
        crops.push_back(c);

    }

    sqlite3_finalize(stmt);

    return crops;

}

