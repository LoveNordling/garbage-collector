#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

#define CELL_SIZE 2048

typedef struct cell
{
	bool is_active;
	unsigned short front_offset;
} cell_t;

void cell_initialize(cell_t* c);
void* cell_front_ptr(cell_t* c, void* start);

bool cell_is_active(cell_t* c);
unsigned short cell_front_offset(cell_t* c);

void cell_activate(cell_t* c);
void cell_deactivate(cell_t* c);
void cell_set_front_offset(cell_t* c, unsigned short fo);

#endif /* CELL_H */