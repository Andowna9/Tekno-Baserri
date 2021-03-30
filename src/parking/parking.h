#ifndef PARKING_H
#define PARKING_H

// Estructura para cada aparcamiento

typedef struct {

    char* l_plate; // Matrícula

}p_lot; // Parking Lot

int num_rows;
int num_cols;

p_lot** parking; // Parking - Matriz de 2 dimensiones

void create_parking(int rows, int cols);
void free_parking_memory();
void insert_vehicle(char* key, int row, int col);
void remove_vehicle(int row, int col);
void print_parking();

#endif // PARKING_H
