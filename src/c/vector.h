#ifndef vector_H
#define vector_H

#include <stdio.h>
#include <stdlib.h>


#include "../utils/utils.h"
#include "../macros/error_macros.h"


typedef struct vector vector;

/**
 * Creates and initializes a new vector.
 *
 * Allocates memory for a vector ure and its underlying data array. The vector is initialized
 * with a default capacity and size of zero. Memory allocation failures for either the vector ure
 * or its data array result in a NULL return value.
 *
 * @return A pointer to the newly created vector, or NULL if memory allocation fails. The returned
 *         vector should be passed to vector_free to release its resources when it is no longer needed.
 */
vector* vector_initialize(void);
/**
 * Frees the resources associated with a vector.
 *
 * Releases the memory allocated for the vector's data array and resets the vector's fields. After
 * calling this function, the vector should not be used again.
 *
 * @param vec A pointer to the vector to be freed. If vec is NULL, the function does nothing.
 */

void vector_destroy(vector* vec);

void vector_display(const vector* vec);
void vector_push(vector* vec, int value);
int vector_pop(vector* vec);
int vector_get(const vector* vec, size_t index);
void vector_set(const vector* vec, size_t index, int value);
int vector_max(const vector* vec);
int vector_min(const vector* vec);
int vector_sum(const vector* vec);
float vector_avg(const vector* vec);
void vector_insert(vector* vec, size_t index, int value);
void vector_delete(vector* vec, size_t index);
void vector_reverse(vector* vec);
void vector_left_shift(vector* vec);
int vector_is_sorted(const vector* vec);
int vector_binary_search(const vector* vec, int value);
void vector_concat(vector* vec, const vector* vec_concat);
int vector_compare(const vector* vec, const vector* vec_compare);
void vector_copy(vector* vec, const vector* vec_copy);

#endif  // vector_H
