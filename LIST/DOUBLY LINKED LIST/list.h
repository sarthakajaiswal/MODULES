#ifndef _DLL_H 
#define _DLL_H 

// header files 
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>  

#define TRUE    1 
#define FALSE   0 
#define SUCCESS     1 
#define LIST_DATA_NOT_FOUND 3 
#define LIST_EMPTY  2

// typedefs 
typedef int data_t; 
typedef size_t len_t; 
typedef len_t index_t; 
typedef struct Node node_t; 
typedef node_t list_t; 
typedef int status_t; 

// structure declarations 
struct Node 
{
    data_t data; 
    struct Node* prev; 
    struct Node* next; 
}; 

// function declarations 
list_t* create_list(void); 

status_t insert_start(list_t* p_list, data_t new_data); 
status_t insert_end(list_t* p_list, data_t new_data); 
status_t insert_before(list_t* p_list, data_t e_data, data_t new_data); 
status_t insert_after(list_t* p_list, data_t e_data, data_t new_data); 

status_t get_start(list_t* p_list, data_t* p_start_data); 
status_t get_end(list_t* p_list, data_t* p_end_data); 

status_t remove_start(list_t* p_list); 
status_t remove_end(list_t* p_list); 
status_t remove_data(list_t* p_list, data_t r_data); 

status_t pop_start(list_t* p_list, data_t* p_popped_data); 
status_t pop_end(list_t* p_list, data_t* p_popped_data); 

status_t is_list_empty(list_t* p_list); 
len_t get_list_length(list_t* p_list); 
status_t find(list_t* p_list, data_t f_data); 

status_t clear_list(list_t* p_list); 
void show_list(list_t* p_list, const char* msg); 
status_t destroy_list(list_t** pp_list); 

// interlist routines 
list_t* get_reversed_list(list_t* p_list); 
list_t* get_concatenated_list(list_t* p_list_1, list_t* p_list_2); 
list_t* merge_lists(list_t* p_list_1, list_t* p_list_2); 
list_t* to_list(data_t* p_array, len_t N); 

data_t* to_array(list_t* p_list, len_t* pN); 

status_t concat_lists(list_t* p_list_1, list_t* p_list_2); 
status_t reverse_list(list_t* p_list); 

// generic routines 
static status_t generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end); 
static status_t generic_delete(node_t* p_delete_node); 

// helper routines 
static node_t* get_node(data_t new_data); 
static void* xmalloc(size_t nr_elements);

#endif /* _DLL_H */

