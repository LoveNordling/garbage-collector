#ifndef OBJECT_H
#define OBJECT_H

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <malloc.h>
#include <math.h>

/// Create a new heap with bytes total size (including both spaces
/// and metadata), meaning strictly less than bytes will be
/// available for allocation.
///
/// \param bytes the total size of the heap in bytes
/// \param unsafe_stack true if pointers on the stack are to be considered unsafe pointers
/// \param gc_threshold the memory pressure at which gc should be triggered (1.0 = full memory)
/// \return the size of the formatstring
size_t format_string_parser(char* layout);

#endif /* OBJECT_H */
