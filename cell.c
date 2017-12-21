#include "cell.h"

enum state {PASSIVE, ACTIVE};

typedef struct cell
{
  int state;
  void* bump_pointer;
} cell_t;

void cell_new(void* start)
{
  cell_t cell = {.state = PASSIVE, .bump_pointer = start + sizeof(cell_t)};
  *(cell_t*)start = cell;
}

void cell_activate(cell_t *c)
{
  c->state = ACTIVE;
}

void cell_deactivate(cell_t *c)
{
  c->state = PASSIVE;
}

bool cell_is_active(cell_t *c){
  return c->state == ACTIVE;
}



