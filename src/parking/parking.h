#ifndef PARKING_H
#define PARKING_H

#define MAX_ROWS 26
#define MAX_COLS 26

// Estructura para cada aparcamiento

typedef struct {

    char* l_plate; // Matrícula

}p_lot; // Parking Lot

int num_rows;
int num_cols;

int num_vehicles;

p_lot** parking; // Parking - Matriz de 2 dimensiones

void create_parking(int rows, int cols);
void free_parking_memory();
void add_columns(int n);
void add_rows(int n);
void insert_vehicle(char* key, int row, int col);
void remove_vehicle(int row, int col);
void print_parking();

#endif // PARKING_H
