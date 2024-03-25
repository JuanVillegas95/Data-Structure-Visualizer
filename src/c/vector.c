#include "vector.h"

struct properties{
    size_t _size;
    size_t _capacity;
}
vector* vector_initialize(size_t size_of_type) {
    vector* vec = (vector*)malloc(vector);
    NULL_STRUCT(vec);
    vec->_capacity = 4;
    vec->_size = 0;
    vec->_data = malloc(vec->_capacity * size_of_type);
    NULL_STRUCT(vec->_data);
    return vec;
}

void vector_destroy(vector* vec){
    vec->_capacity = 0;
    vec->_size = 0;
    free(vec->_data);
    free(vec);
}

static void _more_capacity(vector* vec) {
    int new_capacity = vec->_capacity * 2;
    int* new_data = realloc(vec->_data, new_capacity * sizeof(int));
    NULL_VOID(new_data);
    vec->_capacity = new_capacity;
    vec->_data = new_data;
}

void vector_push(vector* vec, int value){
    NULL_VOID(vec);
    if(vec->_size >= vec->_capacity) _more_capacity(vec);
    vec->_data[vec->_size++] = value;
}

void vector_display(const vector* vec){
    NULL_VOID(vec);
    VEC_EMPTY_VOID(vec);
    for(size_t i = 0; i<vec->_size; i++) printf("%d ",vec->_data[i]);
    printf("\n");
}

int vector_pop(vector* vec){
    NULL_INT(vec);
    VEC_EMPTY_INT(vec)
    return vec->_data[--vec->_size];
}

int vector_get(const vector* vec, size_t index){
    NULL_INT(vec);
    VEC_EMPTY_INT(vec)
    return vec->_data[index];    
}

void vector_set(const vector* vec, size_t index, int key){
    NULL_VOID(vec);
    INDEX_BOUNDS_VOID(vec, index);
    vec->_data[index] = key;
}

int vector_max(const vector* vec){
    NULL_INT(vec);
    VEC_EMPTY_INT(vec)
    int max = vec->_data[0];
    for(size_t i = 1; i < vec->_size; i++){
        if(max < vec->_data[i]){
            max = vec->_data[i];
        }
    }
    return max;
}

int vector_min(const vector* vec){
    NULL_INT(vec);
    VEC_EMPTY_INT(vec)
    int min = vec->_data[0];
    for(size_t i = 1; i < vec->_size; i++){
        if(min > vec->_data[i]){
            min = vec->_data[i];
        }
    }
    return min;
}

int vector_sum(const vector* vec){
    NULL_INT(vec);
    VEC_EMPTY_INT(vec)
    int sum = 0;
    for(size_t i = 0; i < vec->_size; i++){
        sum += vec->_data[i];
    }
    return sum;
}

float vector_avg(const vector* vec){
    NULL_FLOAT(vec);
    VEC_EMPTY_INT(vec);
    float sum = vector_sum(vec);
    return (float)(sum / vec->_size);
}

void vector_insert(vector* vec, size_t index, int value){
    NULL_VOID(vec);
    INDEX_BOUNDS_VOID(vec, index);
    if(vec->_size >= vec->_capacity) _more_capacity(vec);
    for(size_t i = vec->_size; i > index; i--){
        vec->_data[i] = vec->_data[i - 1];
    }
    vec->_data[index] = value;
    vec->_size++;
}

void vector_delete(vector* vec, size_t index){
    NULL_VOID(vec);
    INDEX_BOUNDS_VOID(vec, index);
    for(size_t i = index; i < vec->_size - 1; i++){
        vec->_data[i] = vec->_data[i + 1];
    }
    vec->_size--;
}

static void swap(int* a, int* b) {
    NULL_VOID(a);
    NULL_VOID(b);
    int temp = *a;
    *a = *b;
    *b = temp;
}


void vector_reverse(vector* vec){
    NULL_VOID(vec);
    VEC_EMPTY_VOID(vec);
    for(size_t i = 0, j = vec->_size - 1; i < j; i++, j--) swap(&vec->_data[i], &vec->_data[j]);
}

void vector_left_shift(vector* vec){
    NULL_VOID(vec);
    VEC_EMPTY_VOID(vec);
    int temp = vec->_data[0];
    for(int i = 0; i < vec->_size - 1; i++){
        vec->_data[i] = vec->_data[i+1];
    }
    vec->_data[vec->_size - 1] = temp;
}

void vector_concat(vector* vec, const vector* vec_concat){
    NULL_VOID(vec); NULL_VOID(vec_concat);
    VEC_EMPTY_VOID(vec); VEC_EMPTY_VOID(vec_concat);

    int new_capacity = vec->_size + vec_concat->_size;
    int* new_data = realloc(vec->_data, new_capacity * sizeof(int));
    NULL_VOID(new_data);
    vec->_data = new_data;
    for(size_t i = 0; i<vec_concat->_size; i++) vec->_data[vec->_size + i] = vec_concat->_data[i];
    vec->_capacity = new_capacity;
    vec->_size+= vec_concat->_size;
}
int vector_compare(const vector* vec, const vector* vec_compare){
    NULL_INT(vec); NULL_INT(vec_compare);
    VEC_EMPTY_INT(vec); VEC_EMPTY_INT(vec_compare);

    if(vec->_size != vec_compare->_size) return 0;
    for(size_t i = 0; i<vec->_size; i++)if(vec->_data[i] != vec_compare->_data[i]) return 0;
    return 1;
}

void vector_copy(vector* vec, const vector* vec_copy){
    NULL_VOID(vec); NULL_VOID(vec_copy);

}

int vector_is_sorted(const vector* vec){
    NULL_INT(vec);
    VEC_EMPTY_INT(vec);
    for(size_t i = 0; i < vec->_size - 1; i++) if(vec->_data[i] > vec->_data[i+1]) return 0;
    return 1;
}

int vector_binary_search(const vector* vec, int key){
    if(!vector_is_sorted(vec)){
        printf("Vector is not sorted.\n");
        return -1;
    }
    int low = 0;
    int high = vec->_size - 1;
    while (low <= high){
        int mid = (high + low) / 2;
        if(key == vec->_data[mid]){
            return mid;
        }else if(key < vec->_data[mid]){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }
    return -1;
}





















