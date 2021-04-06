#include <dynamic_array.h>
#include <stdlib.h>

void init_arr(dyn_array* self, int init_limit) {

    self->limit = init_limit;
    self->size = 0;
    self->data = malloc(sizeof (void*) * self->limit);
}

int is_index_valid(dyn_array self, int index) {

    return index >= 0 && index < self.size;
}

void add_elem(dyn_array* self, void* data) {

    // Si el tamaño es igual al límite, reasignamos el área de momoria para contener el doble

    if (self->size == self->limit) {

        self->limit *= 2;

        self->data = realloc(self->data, sizeof(void*) * self->limit);
    }

    // Gurdamos el puntero al dato añadido

    self->data[self->size++] = data;

}

void remove_elem(dyn_array* self, int index) {

    if (is_index_valid(*self, index)) {

        int i;

        // Desplazamiento de punteros vacíos a partir del índice eliminado para mantener el orden

        for (i = index + 1; i < self->size; i++)  {

            self->data[i - 1] = self->data[i];
        }

        self->size--;

    }
}

void* get_elem(dyn_array self, int index) {

    if (is_index_valid(self, index)) {

        return self.data[index];
    }

    return NULL;
}

void free_mem(dyn_array* self) {

    if (self->data != NULL) {

        free(self->data);

        self->data = NULL;

    }
}
