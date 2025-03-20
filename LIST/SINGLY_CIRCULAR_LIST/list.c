#include "list.h" 

list_t* create_list(void) 
{
    list_t* new_node = NULL; 

    new_node = get_node(0); 
    new_node->next = new_node; 
    return (new_node); 
}

status_t insert_start(list_t* p_list, data_t new_data) 
{
    node_t* run = NULL; 
    node_t* new_node = NULL; 

    new_node = get_node(new_data); 
    new_node->next = p_list->next; 
    p_list->next = new_node; 

    return (SUCCESS); 
}

status_t insert_end(list_t* p_list, data_t new_data) 
{
    node_t* run = NULL; 
    node_t* new_node = NULL; 

    run = p_list; 
    while(run->next != p_list) 
        run = run->next; 

    new_node = get_node(new_data); 
    new_node->next = p_list; 
    run->next = new_node; 

    return (SUCCESS); 
} 

status_t insert_after(list_t* p_list, data_t e_data, data_t new_data) 
{
    node_t* new_node = NULL; 
    node_t* run = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    while(run != p_list) 
    {
        if(run->data == e_data) 
        {
            new_node = get_node(new_data); 

            new_node->next = run->next; 
            run->next = new_node; 

            return (SUCCESS); 
        }

        run = run->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t insert_before(list_t* p_list, data_t e_data, data_t new_data) 
{
    node_t* run = NULL; 
    node_t* run_prev = NULL; 
    node_t* new_node = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    run_prev = p_list; 
    while(run != p_list) 
    {
        if(run->data == e_data) 
        {
            new_node = get_node(new_data); 
            new_node->next = run; 
            run_prev->next = new_node; 

            return (SUCCESS); 
        }
        run_prev = run; 
        run = run->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
} 

status_t get_start(list_t* p_list, data_t* p_start_data) 
{
    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
} 

status_t get_end(list_t* p_list, data_t* p_end_data) 
{
    node_t* run = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    while(run->next != p_list) 
        run = run->next; 

    *p_end_data = run->data; 
    return (SUCCESS); 
} 

status_t pop_start(list_t* p_list, data_t* p_popped_data) 
{
    node_t* p_start_node = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    p_start_node = p_list->next; 

    p_list->next = p_start_node->next; 
    
    *p_popped_data = p_start_node->data; 
    free(p_start_node); 
    p_start_node = NULL; 

    return (SUCCESS);
} 

status_t pop_end(list_t* p_list, data_t* p_popped_data) 
{
    node_t* p_end_node = NULL; 
    node_t* end_prev = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    p_end_node = p_list->next; 
    end_prev = p_list; 
    while(p_end_node->next != p_list) 
    {
        end_prev = p_end_node; 
        p_end_node = p_end_node->next; 
    }

    end_prev->next = p_list; 
    *p_popped_data = p_end_node->data; 

    free(p_end_node); 
    p_end_node = NULL; 

    return (SUCCESS); 
} 

status_t remove_start(list_t* p_list) 
{
    node_t* p_start_node = NULL; 
    node_t* run = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    p_start_node = p_list->next; 

    p_list->next = p_start_node->next; 
    free(p_start_node); 
    p_start_node = NULL; 

    return (SUCCESS); 
} 

status_t remove_end(list_t* p_list) 
{
    node_t* run = NULL; 
    node_t* run_prev = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    run_prev = p_list; 
    while(run->next != p_list) 
    {   
        run_prev = run; 
        run = run->next; 
    } 

    run_prev->next = p_list; 

    free(run); 
    run = NULL; 

    return (SUCCESS); 
} 

status_t remove_data(list_t* p_list, data_t r_data) 
{
    node_t* run = NULL; 
    node_t* run_prev = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    run_prev = p_list; 
    while(run != p_list) 
    {
        if(run->data == r_data) 
        {   
            run_prev->next = run->next; 
            
            free(run); 
            run = NULL; 

            return (SUCCESS); 
        }

        run_prev = run; 
        run = run->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
} 

size_t get_list_length(list_t* p_list) 
{
    node_t* run = NULL; 
    size_t length = 0; 

    run = p_list->next; 
    while(run != p_list) 
    {
        length = length + 1; 
        run = run->next; 
    }

    return (length); 
} 

data_t* to_array(list_t* p_list, size_t* pN) 
{
    data_t* p_array = NULL; 
    size_t N = 0; 
    size_t i = 0; 
    node_t* run = NULL; 

    N = get_list_length(p_list); 
    if(N <= 0) 
        return (NULL); 

    p_array = (data_t*)xmalloc(N * sizeof(data_t)); 

    run = p_list->next; 
    i = 0; 
    while(run != p_list) 
    {
        p_array[i] = run->data; 
        i = i + 1; 
        run = run->next; 
    }

    *pN = N; 
    return (p_array); 
} 

list_t* to_list(data_t* p_array, size_t N) 
{
    list_t* new_list = NULL; 
    size_t i = 0; 

    new_list = create_list(); 

    for(i = 0; i < N; i++) 
        insert_end(new_list, p_array[i]); 

    return (new_list); 
} 

status_t is_list_empty(list_t* p_list) 
{
    if(p_list->next == p_list) 
        return (TRUE); 
    return (FALSE);  
} 

status_t find(list_t* p_list, data_t f_data) 
{
    node_t* run = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    while(run != p_list) 
    {
        if(run->data == f_data) 
            return (SUCCESS); 

        run = run->next; 
    } 

    return (LIST_DATA_NOT_FOUND); 
} 

void show_list(list_t* p_list, const char* msg) 
{
    node_t* run = NULL; 

    if(msg) 
        puts(msg); 

    printf("\\-> [START] -> "); 

    run = p_list->next; 
    while(run != p_list) 
    {
        printf(" [%d] -> ", run->data); 
        run = run->next; 
    }

    printf("[END] ->/\n"); 
} 

status_t clear_list(list_t* p_list) 
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    run = p_list->next; 
    while(run != p_list) 
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }

    p_list->next = p_list; 
    return (SUCCESS); 
} 

status_t destroy_list(list_t** pp_list) 
{
    list_t* p_list = *pp_list; 
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    run = p_list->next; 
    while(run != p_list) 
    {
        run_next = run->next; 

        free(run); 
        run = run_next; 
    }

    free(p_list); 
    p_list = NULL; 
    *pp_list = NULL; 

    return (SUCCESS); 
} 

// interlist routines 
list_t* get_reversed_list(list_t* p_list) 
{
    list_t* reversed_list = NULL; 
    node_t* run = NULL; 

    reversed_list = create_list(); 

    run = p_list->next; 
    while(run != p_list) 
    {
        insert_start(reversed_list, run->data); 
        run = run->next; 
    }

    return (reversed_list); 
} 

status_t reverse_list(list_t* p_list) 
{
    node_t* current_start = NULL; 
    node_t* original_start = NULL; 
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    if(p_list->next == NULL || p_list->next->next == NULL) 
        return (SUCCESS); 

    current_start = p_list->next; 
    original_start = p_list->next; 
    run = p_list->next->next; 
    while(run != p_list) 
    {
        run_next = run->next; 

        run->next = current_start; 
        p_list->next = run; 

        current_start = run; 
        run = run_next; 
    } 

    original_start->next = p_list; 

    return (SUCCESS); 
} 

list_t* merge_lists(list_t* p_list_1, list_t* p_list_2) 
{
    node_t* run1 = NULL; 
    node_t* run2 = NULL; 
    list_t* p_merged_list = NULL; 

    p_merged_list = create_list(); 

    run1 = p_list_1->next; 
    run2 = p_list_2->next; 

    while(TRUE) 
    {
        if(run1 == p_list_1) 
        {
            while(run2 != p_list_2) 
            {
                insert_end(p_merged_list, run2->data); 
                run2 = run2->next; 
            }
            break; 
        }
        else if(run2 == p_list_2) 
        {
            while(run1 != p_list_1) 
            {
                insert_end(p_merged_list, run1->data); 
                run1 = run1->next; 
            }
            break; 
        }

        if(run1->data < run2->data) 
        {
            insert_end(p_merged_list, run1->data); 
            run1 = run1->next; 
        }
        else 
        {
            insert_end(p_merged_list, run2->data); 
            run2 = run2->next; 
        }
    }

    return (p_merged_list); 
} 

list_t* get_concatenated_list(list_t* p_list_1, list_t* p_list_2) 
{
    list_t* concatenated_list = NULL; 
    node_t* run = NULL; 

    concatenated_list = create_list(); 

    run = p_list_1->next; 
    while(run != p_list_1) 
    {
        insert_end(concatenated_list, run->data); 
        run = run->next; 
    }

    run = p_list_2->next; 
    while(run != p_list_2) 
    {
        insert_end(concatenated_list, run->data); 
        run = run->next; 
    }

    return (concatenated_list); 
} 

status_t concat_lists(list_t* p_list_1, list_t* p_list_2) 
{
    node_t* run = NULL; 

    if(is_list_empty(p_list_2) == TRUE) 
    {
        free(p_list_2); 
        p_list_2 = NULL; 
        return (SUCCESS);
    } 

    run = p_list_1; 
    while(run->next != p_list_1) 
        run = run->next; 

    run->next = p_list_2->next; 

    run = p_list_2->next; 
    while(run->next != p_list_2) 
        run = run->next; 

    run->next = p_list_1; 

    p_list_2->next = p_list_2;  

    return (SUCCESS); 
} 

// helper routines 
static node_t* get_node(data_t new_data) 
{
    node_t* new_node = NULL; 

    new_node = (node_t*)xmalloc(sizeof(node_t)); 
    new_node->data = new_data; 
    new_node->next = NULL; 

    return (new_node); 
} 

static void* xmalloc(size_t nr_bytes) 
{
    void* p = NULL; 

    p = malloc(nr_bytes); 
    if(p == NULL)
    {
        fprintf(stderr, "error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
} 