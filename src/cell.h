/**
 * @file cell.h
 * @author Love Nordling
 * @author Manuel Alexan
 * @date 10 January 2018
 * @brief Cell header module
 *
 * This module contains the cell metadata structure and its related functions.
 * A cell structure simply stores information about a cell in memory. It does not
 * know the absolute position of the cell in the heap, only the relative position
 * of its free memory. This is to save space.
 * An array of these structures will be stored consecutively in the beginning of
 * the heap.
 */

#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

#define CELL_SIZE 2048

//Should this really be in .h file?
//Yes. If we want to make arrays of the datastructure.

/**
 * @brief The metadata of a single cell in the heap
 *
 * This struct contains information about a cell region in the heap.
 * An array of these structures will be stored in the heap's header region.
 */
typedef struct cell
{
    bool is_active;
    unsigned short front_offset;
} cell_t;

/**
 * @brief Initializes the cell to default values
 *
 * @param c the cell
 * @return void
 */
void cell_initialize(cell_t* c);

/**
 * @brief Returns the cell's front pointer
 *
 * A cell header does not contain a pointer to its start position in
 * the heap.
 * This is calculated on the fly with array arithmetic, to save memory.
 *
 * @param c the cell
 * @param start a pointer to the cell's position in the heap
 * @return the cell's front pointer
 */
void* cell_front_ptr(cell_t* c, void* start);

/**
 * @brief Returns true if cell is currently active, otherwise returns false
 *
 * @param c the cell
 * @return true if cell is active, otherwise false
 */
bool cell_is_active(cell_t* c);

/**
 * @brief Returns the cell's current front offset
 *
 * @param c the cell
 * @return the cell's front offset
 */
unsigned short cell_front_offset(cell_t* c);

/**
 * @brief Activates the cell
 *
 * @param c the cell
 * @return void
 */
void cell_activate(cell_t* c);

/**
 * @brief Deactivates the cell
 *
 * @param c the cell
 * @return void
 */
void cell_deactivate(cell_t* c);

/**
 * @brief Sets the front offset of the cell to
 * a new value
 *
 * @param c the cell
 * @param fo a new front offset
 * @return void
 */
void cell_set_front_offset(cell_t* c, unsigned short fo);

#endif /* CELL_H */
