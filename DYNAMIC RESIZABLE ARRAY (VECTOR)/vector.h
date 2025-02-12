#ifndef _VECTOR_H 
#define _VECTOR_H 

#include <stdio.h> 
#include <stdlib.h> 

#define TRUE    1 
#define FALSE   0 
#define SUCCESS 1 
#define INDEX_OUT_OF_RANGE  2 
#define INVALID_INDEX       -1 
#define VECTOR_EMPTY        3 
#define VECTOR_DATA_NOT_FOUND   4 

typedef int data_t; 
typedef struct vector vector_t; 
typedef size_t index_t; 
typedef int status_t; 

struct vector 
{
    data_t* arr; 
    size_t N; 
}; 

vector_t* create_vector(void); 

status_t insert_start(vector_t* p_vec, data_t new_data); 
status_t push_back(vector_t* p_vec, data_t new_data); 
status_t insert_at(vector_t* p_vec, index_t index, data_t new_data); 

status_t remove_start(vector_t* p_vec); 
status_t remove_end(vector_t* p_vec); 
status_t pop_start(vector_t* p_vec, data_t* p_popped_data); 
status_t pop_back(vector_t* p_vec, data_t* p_popped_data); 

status_t remove_index(vector_t* p_vec, index_t index); 
status_t remove_data(vector_t* p_vec, data_t r_data); 

status_t get_start(vector_t* p_vec, data_t* p_start_data); 
status_t get_end(vector_t* p_vec, data_t* p_end_data); 
status_t get_index(vector_t* p_vec, index_t index, data_t* p_data); 
size_t get_size(vector_t* p_vec); 

status_t set_index(vector_t* p_vec, index_t index, data_t new_data); 
status_t set_start(vector_t* p_vec, data_t new_data); 
status_t set_end(vector_t* p_vec, data_t new_data); 

index_t find(vector_t* p_vec, data_t f_data); 
status_t is_vector_empty(vector_t* p_vec); 
size_t get_size(vector_t* p_vec); 
void show_vector(vector_t* p_vec, const char* msg); 

status_t sort(vector_t* p_vec); 

status_t clear_vector(vector_t* p_vec); 
status_t destroy_vector(vector_t** pp_vec); 

static void* xmalloc(size_t nr_elements); 

#endif /* _VECTOR_H */

