#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>

typedef struct object object_t;

/// Creates a new object
/// with either a layout string
/// or just a byte-size.
///
/// \param memory_ptr pointer to available place to store object
/// \param layout pointer to layout-string (CAN BE NULL if no layout)
/// \param bytes size of object (IF LAYOUT IS NULL)
/// \return the size of the formatstring
void* new_object(void* memory_ptr, void* layout, size_t bytes);

#endif /* OBJECT_H */
