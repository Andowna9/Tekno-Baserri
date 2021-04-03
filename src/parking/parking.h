#ifndef PARKING_H
#define PARKING_H

#include <time.h>

#define MAX_ROWS 26
#define MAX_COLS 26

// Estructura para cada aparcamiento

typedef struct {

    char* l_plate; // Matrícula
    time_t t_stamp; // Tiempo de entrada

}p_lot; // Parking Lot

int num_rows;
int num_cols;

int num_vehicles;

p_lot** parking; // Parking - Matriz de 2 dimensiones

void create_parking(int rows, int cols);
void free_parking_memory();
void modify_columns(int dn);
void modify_rows(int dn);
int out_of_bounds(int row, int col);
void save_parking();
int load_parking();
void insert_vehicle(char* key, int row, int col);
void remove_vehicle(int row, int col);
void print_parking();
char* get_time_passed(time_t time_stamp);


// Punto destacado de la matriz
typedef struct {
    int x;
    int y;
} Point;

Point highlighted_point;
void set_highlighted_point(int x, int y);
void reset_highlighted_point();


#endif // PARKING_H
