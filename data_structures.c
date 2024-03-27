#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h> 

typedef struct {
    int *data;
    size_t _size;
    size_t _capacity;
} vector;

EMSCRIPTEN_KEEPALIVE
vector*  vector_initialize(void) {
    vector* vec = (vector*)malloc(sizeof(vector));
    vec->_capacity = 4;
    vec->_size = 0;
    vec->data = malloc(vec->_capacity);
    return vec;
}

// Function to get the size of the vector
EMSCRIPTEN_KEEPALIVE
size_t vector_get_size(vector* vec) {
    return vec->_size;
}

// Function to get the capacity of the vector
EMSCRIPTEN_KEEPALIVE
size_t vector_get_capacity(vector* vec) {
    return vec->_capacity;
}
EMSCRIPTEN_KEEPALIVE

void vector_destroy(vector* vec) {
    free(vec->data);
    free(vec);
}

static void _more_capacity(vector* vec) {
    size_t new_capacity = vec->_capacity * 2;
    vec->data = realloc(vec->data, new_capacity * sizeof(int));
    vec->_capacity = new_capacity;
}

EMSCRIPTEN_KEEPALIVE
void vector_push(vector* vec, int value) {
    if (vec->_size >= vec->_capacity) _more_capacity(vec);
    vec->data[vec->_size++] = value;
}

EMSCRIPTEN_KEEPALIVE
void vector_display(const vector* vec) {
    for (size_t i = 0; i < vec->_size; i++) printf("%d ", vec->data[i]);
    printf("\n");
}

EMSCRIPTEN_KEEPALIVE
int vector_pop(vector* vec) {
    // Add check for empty vector if necessary
    return vec->data[--vec->_size];
}

EMSCRIPTEN_KEEPALIVE
int vector_get(const vector* vec, size_t index) {
    // Add bounds checking if necessary
    return vec->data[index];    
}

EMSCRIPTEN_KEEPALIVE
void vector_set(vector* vec, size_t index, int value) {
    // Add bounds checking if necessary
    vec->data[index] = value;
}

EMSCRIPTEN_KEEPALIVE
int vector_max(const vector* vec) {
    int max = vec->data[0];
    for (size_t i = 1; i < vec->_size; i++) {
        if (max < vec->data[i]) {
            max = vec->data[i];
        }
    }
    return max;
}

EMSCRIPTEN_KEEPALIVE
int vector_min(const vector* vec) {
    int min = vec->data[0];
    for (size_t i = 1; i < vec->_size; i++) {
        if (min > vec->data[i]) {
            min = vec->data[i];
        }
    }
    return min;
}

EMSCRIPTEN_KEEPALIVE
int vector_sum(const vector* vec) {
    int sum = 0;
    for (size_t i = 0; i < vec->_size; i++) {
        sum += vec->data[i];
    }
    return sum;
}
EMSCRIPTEN_KEEPALIVE
float vector_avg(const vector* vec) {
    int sum = vector_sum(vec);
    if (vec->_size == 0) return 0; // Prevent division by zero
    return (float)sum / vec->_size;
}
EMSCRIPTEN_KEEPALIVE
void vector_insert(vector* vec, size_t index, int value) {
    if (index > vec->_size) {
        // Handle error or extend the vector to accommodate
        return;
    }
    if (vec->_size >= vec->_capacity) _more_capacity(vec);

    // Shift elements to the right
    for (size_t i = vec->_size; i > index; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[index] = value;
    vec->_size++;
}
EMSCRIPTEN_KEEPALIVE
void vector_delete(vector* vec, size_t index) {
    if (index >= vec->_size) {
        // Handle error or ignore
        return;
    }

    // Shift elements to the left
    for (size_t i = index; i < vec->_size - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->_size--;
}
EMSCRIPTEN_KEEPALIVE
void vector_reverse(vector* vec) {
    for (size_t i = 0, j = vec->_size - 1; i < j; i++, j--) {
        int temp = vec->data[i];
        vec->data[i] = vec->data[j];
        vec->data[j] = temp;
    }
}
EMSCRIPTEN_KEEPALIVE
void vector_left_shift(vector* vec) {
    if (vec->_size == 0) return; // No elements to shift
    int first = vec->data[0];
    for (size_t i = 1; i < vec->_size; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->data[vec->_size - 1] = first;
}
EMSCRIPTEN_KEEPALIVE
void vector_concat(vector* vec, const vector* vec_concat) {
    for (size_t i = 0; i < vec_concat->_size; i++) {
        vector_push(vec, vec_concat->data[i]);
    }
}
EMSCRIPTEN_KEEPALIVE
int vector_compare(const vector* vec1, const vector* vec2) {
    if (vec1->_size != vec2->_size) return 0;
    for (size_t i = 0; i < vec1->_size; i++) {
        if (vec1->data[i] != vec2->data[i]) return 0;
    }
    return 1;
}
EMSCRIPTEN_KEEPALIVE
void vector_copy(vector* dest, const vector* src) {
    if (dest->_capacity < src->_size) {
        dest->data = realloc(dest->data, src->_size * sizeof(int));
        dest->_capacity = src->_size;
    }
    for (size_t i = 0; i < src->_size; i++) {
        dest->data[i] = src->data[i];
    }
    dest->_size = src->_size;
}
EMSCRIPTEN_KEEPALIVE
int vector_is_sorted(const vector* vec) {
    for (size_t i = 0; i < vec->_size - 1; i++) {
        if (vec->data[i] > vec->data[i + 1]) return 0;
    }
    return 1;
}
EMSCRIPTEN_KEEPALIVE
int vector_binary_search(const vector* vec, int value) {
    int low = 0, high = vec->_size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (vec->data[mid] == value)
            return mid;
        else if (vec->data[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; 
}

int main(int argc, char**argv) {
    return 0;
}
