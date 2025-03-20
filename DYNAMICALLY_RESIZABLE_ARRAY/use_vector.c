#include <stdio.h> 
#include <assert.h> 
#include "vector.h" 

int main(void) 
{
    vector_t* vec = NULL; 
    int i = 0; 
    int N; 

    vec = create_vector(); 
    show_vector(vec, "After creation"); 
    printf("size=%lld\n\n", get_size(vec)); 
    
    insert_start(vec, 10); 
    show_vector(vec, "After insert_start()"); 
    printf("size=%lld\n\n", get_size(vec)); 
    
    for(i = 10; i < 100; i = i + 10) 
    push_back(vec, i); 
    show_vector(vec, "After push_back()"); 
    printf("size=%lld\n\n", get_size(vec)); 
    
    insert_at(vec, 1, 1234); 
    insert_at(vec, 2, 5678); 
    show_vector(vec, "After insert_at()"); 
    printf("size=%lld\n\n", get_size(vec)); 
    
    remove_start(vec); 
    show_vector(vec, "After remove_start()"); 
    printf("size=%lld\n\n", get_size(vec)); 
    
    remove_end(vec); 
    show_vector(vec, "After remove_end()"); 
    printf("size=%lld\n\n", get_size(vec)); 
    
    remove_index(vec, 2); 
    show_vector(vec, "After remove_index()"); 
    printf("size=%lld\n\n", get_size(vec)); 

    remove_index(vec, 2); 
    show_vector(vec, "After remove_index()"); 
    printf("size=%lld\n\n", get_size(vec)); 

    set_index(vec, 2, 888); 
    show_vector(vec, "After set_index()"); 
    printf("size=%lld\n\n", get_size(vec)); 

    set_index(vec, 3, 999); 
    show_vector(vec, "After set_index()"); 
    printf("size=%lld\n\n", get_size(vec)); 

    
    set_start(vec, 999); 
    show_vector(vec, "After set_start()"); 
    printf("size=%lld\n\n", get_size(vec)); 

    printf("index=%lld\n\n", find(vec, 999)); 

    assert(find(vec, 6789) == INVALID_INDEX); 

    clear_vector(vec); 
    assert(vec->arr == NULL); 

    assert(get_start(vec, &N) == VECTOR_EMPTY); 
    assert(get_end(vec, &N) == VECTOR_EMPTY); 


    printf("size=%lld\n\n", get_size(vec)); 

    destroy_vector(&vec); 
    assert(vec == NULL); 

    return (0); 
}

