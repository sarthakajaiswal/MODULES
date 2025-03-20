#include <stdio.h> 
#include <stdlib.h> 

#include "vector.h" 

vector_t* create_vector(void) 
{
    // variable declarations 
    vector_t* p_vec = NULL; 

    // code 
    p_vec = (vector_t*)xmalloc(sizeof(vector_t)); 
    p_vec->arr = NULL; 
    p_vec->N = 0; 

    return (p_vec); 
} 

status_t insert_start(vector_t* p_vec, data_t new_data) 
{
    //  variable declarations 
    index_t i = 0; 

    // code 
    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N + 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N + 1; 

    for(i = p_vec->N-1; i > 0; i--) 
        p_vec->arr[i] = p_vec->arr[i-1]; 
    p_vec->arr[0] = new_data; 

    return (SUCCESS); 
} 

status_t push_back(vector_t* p_vec, data_t new_data) 
{
    // code 
    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N + 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N + 1; 

    p_vec->arr[p_vec->N - 1] = new_data; 

    return (SUCCESS); 
} 

status_t insert_at(vector_t* p_vec, index_t index, data_t new_data) 
{
    // variable declarations 
    index_t i = 0; 

    // code 
    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N + 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N + 1; 

    for(i = p_vec->N-1; i > index; i--) 
        p_vec->arr[i] = p_vec->arr[i-1]; 

    p_vec->arr[index] = new_data; 
    return (SUCCESS); 
} 

status_t remove_start(vector_t* p_vec) 
{
    // variable declarations 
    index_t i = 0; 

    // code 
    if(p_vec->N == 0) 
        return (VECTOR_EMPTY); 

    for(i = 0; i < p_vec->N-1; i++) 
        p_vec->arr[i] = p_vec->arr[i+1]; 

    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N - 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N - 1; 

    return (SUCCESS); 
} 

status_t remove_end(vector_t* p_vec) 
{
    // code 
    if(p_vec->N == 0) 
        return (VECTOR_EMPTY); 

    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N - 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N - 1; 
    return (SUCCESS); 
} 

status_t pop_start(vector_t* p_vec, data_t* p_popped_data) 
{
    // variable declarations 
    index_t i = 0; 
    data_t start_data; 

    // code 
    if(p_vec->N == 0) 
        return (VECTOR_EMPTY); 

    start_data = p_vec->arr[0]; 

    for(i = 0; i < p_vec->N-1; i++) 
        p_vec->arr[i] = p_vec->arr[i+1]; 

    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N - 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N - 1; 

    return (SUCCESS); 
} 

status_t pop_back(vector_t* p_vec, data_t* p_popped_data) 
{
    // variable declarations 
    data_t end_data; 

    // code 
    if(p_vec->N == 0) 
        return (VECTOR_EMPTY); 

    end_data = p_vec->arr[p_vec->N - 1]; 
    
    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N - 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N - 1; 

    *p_popped_data = end_data; 
    return (SUCCESS); 
} 

status_t remove_index(vector_t* p_vec, index_t index) 
{
    // variable declarations 
    index_t i = 0; 

    // code 
    if(index < 0 || index >= p_vec->N) 
        return (INVALID_INDEX); 

    for(i = index; i < p_vec->N-1; i++) 
        p_vec->arr[i] = p_vec->arr[i+1]; 

    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N - 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N - 1; 

    return (SUCCESS); 
} 

status_t remove_data(vector_t* p_vec, data_t r_data) 
{
    // variable declarations 
    index_t i = 0; 
    index_t r_index = 0; 

    // code 
    if(p_vec->N == 0) 
        return (VECTOR_EMPTY); 

    for(r_index = 0; r_index < p_vec->N; r_index++) 
        if(p_vec->arr[r_index] == r_data) 
            break; 

    if(r_index == p_vec->N) 
        return (VECTOR_DATA_NOT_FOUND); 

    for(i = r_index; i < p_vec->N-1; i++) 
        p_vec->arr[i] = p_vec->arr[i+1]; 

    p_vec->arr = (data_t*)realloc(p_vec->arr, (p_vec->N - 1) * sizeof(data_t)); 
    p_vec->N = p_vec->N - 1; 

    return (SUCCESS); 
} 

status_t get_start(vector_t* p_vec, data_t* p_start_data) 
{
    // code 
    if(p_vec->N == 0) 
        return (VECTOR_EMPTY); 

    *p_start_data = p_vec->arr[0]; 
    return (SUCCESS); 
} 

status_t get_end(vector_t* p_vec, data_t* p_end_data) 
{
    // code 
    if(p_vec->N == 0) 
        return (VECTOR_EMPTY); 

    *p_end_data = p_vec->arr[p_vec->N - 1]; 
    return (SUCCESS); 
} 

status_t get_index(vector_t* p_vec, index_t index, data_t* p_data) 
{
    // code 
    if(index < 0 || index >= p_vec->N) 
        return (INVALID_INDEX); 

    *p_data = p_vec->arr[index]; 
    return (SUCCESS); 
} 

size_t get_size(vector_t* p_vec) 
{
    return (p_vec->N); 
} 

status_t set_index(vector_t* p_vec, index_t index, data_t new_data) 
{
    // code 
    if(index < 0 || index >= p_vec->N) 
        return (INVALID_INDEX); 
    
    p_vec->arr[index] = new_data; 
    return (SUCCESS); 
} 

status_t set_start(vector_t* p_vec, data_t new_data) 
{
    // code 
    p_vec->arr[0] = new_data; 
    return (SUCCESS); 
} 

status_t set_end(vector_t* p_vec, data_t new_data) 
{
    // code 
    p_vec->arr[p_vec->N - 1] = new_data; 
    return (SUCCESS); 
} 

index_t find(vector_t* p_vec, data_t f_data) 
{
    // variable declarations 
    index_t i = 0; 

    // code 
    for(i = 0; i < p_vec->N; i++) 
        if(p_vec->arr[i] == f_data) 
            return (i); 
    
    return (INVALID_INDEX); 
} 

status_t is_vector_empty(vector_t* p_vec) 
{
    // code 
    if(p_vec->N == 0) 
        return (TRUE); 
    return (FALSE); 
} 

void show_vector(vector_t* p_vec, const char* msg) 
{
    // variable declarations 
    index_t i = 0; 

    // code 
    if(msg) 
        puts(msg); 

    for(i = 0; i < p_vec->N; i++) 
        printf("%d ", p_vec->arr[i]); 
    printf("\n"); 
} 

status_t sort(vector_t* p_vec) 
{return(SUCCESS);} 

status_t clear_vector(vector_t* p_vec) 
{
    // code 
    free(p_vec->arr); 
    p_vec->arr = NULL; 
    p_vec->N = 0; 

    return (SUCCESS); 
} 

status_t destroy_vector(vector_t** pp_vec) 
{
    // variable declarations 
    vector_t* p_vec = *pp_vec; 

    // code 
    free(p_vec->arr);
    free(p_vec); 
    p_vec = NULL; 

    *pp_vec = NULL; 
    return (SUCCESS); 
} 

static void* xmalloc(size_t nr_bytes) 
{
    // variable declarations 
    void* p = NULL; 

    // code 
    p = malloc(nr_bytes); 
    if(p == NULL) 
    {
        fprintf(stderr, "error in llocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
} 

