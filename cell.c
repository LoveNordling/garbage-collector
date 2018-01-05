#include "cell.h"
#include <stdio.h>

void cell_initialize(cell_t* c)
{
	cell_deactivate(c);
	cell_set_front_offset(c, 0);
}

void* cell_front_ptr(cell_t* c, void* start)
{
	return (void*) (((char*)start) + c->front_offset);
}


bool cell_is_active(cell_t* c)
{
	return c->is_active;
}

unsigned short cell_front_offset(cell_t* c)
{
	return c->front_offset;
}


void cell_activate(cell_t* c)
{
	c->is_active = true;
}

void cell_deactivate(cell_t* c)
{
	c->is_active = false;
        c->front_offset = 0;
}

void cell_set_front_offset(cell_t* c, unsigned short fo)
{
	c->front_offset = fo;

	if (c->front_offset >= CELL_SIZE)
	{
		c->front_offset = CELL_SIZE - 1;
	}
}
