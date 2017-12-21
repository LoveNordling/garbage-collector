
#include <stdbool.h>

typedef struct cell cell_t;

void cell_new(void* start);

void cell_activate(cell_t *b);

void cell_deactivate(cell_t *b);

bool cell_is_active(cell_t *c);