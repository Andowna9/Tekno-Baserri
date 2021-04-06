#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// Array dinámico, similar a ArrayList de Java

typedef struct {

    void** data;
    int size;
    int limit;

} dyn_array;

/**
 * @brief Inicializa el array con una capacidad
 * @param self Puntero al array dinámico
 * @param init_limit Capacidad inicial
 */
void init_arr(dyn_array* self, int init_limit);

/**
 * @brief Añade un elemento al final
 * @param self Puntero al array dinámico
 * @param data Puntero a cualquier tipo de dato
 */
void add_elem(dyn_array* self, void* data);

/**
 * @brief Obtiene el puntero a un dato en un índice dado
 * @param self Puntero al array dinámico
 * @param index Índice >= 0
 */
void* get_elem(dyn_array self, int index);

/**
 * @brief Elimina un elmento
 * @param self Puntero al array dinámico
 * @param data Índice >= 0
 */
void remove_elem(dyn_array* self, int index);

/**
 * @brief Libera la memoria reservada durante la inicialización
 * @param self Puntero al array dinámico
 */
void free_mem(dyn_array* self);

#endif // DYNAMIC_ARRAY_H
