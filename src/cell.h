/**
 * @file cell.h
 * @author Love Nordling
 * @author Manuel Alexan
 * @date 10 January 2018
 * @brief 
 *
 *  
 * 
 */

#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

#define CELL_SIZE 2048

//Should this really be in .h file?

typedef struct cell
{
    bool is_active;
    unsigned short front_offset;
} cell_t;


/**
 * @brief 
 *
 * @param c
 * @return void
 */
void cell_initialize(cell_t* c);

/**
 * @brief 
 *
 * @param c
 * @param start
 * @return pointer to
 */
void* cell_front_ptr(cell_t* c, void* start);

/**
 * @brief 
 *
 * @param c
 * @return bool
 */
bool cell_is_active(cell_t* c);

/**
 * @brief 
 *
 * @param c
 * @return void
 */
unsigned short cell_front_offset(cell_t* c);

/**
 * @brief 
 *
 * @param c
 * @return void
 */
void cell_activate(cell_t* c);

/**
 * @brief 
 *
 * @param c
 * @return void
 */
void cell_deactivate(cell_t* c);

/**
 * @brief 
 *
 * @param c
 * @param fo
 * @return void
 */
void cell_set_front_offset(cell_t* c, unsigned short fo);

#endif /* CELL_H */
