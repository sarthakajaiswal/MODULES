#include "list.h" 

list_t* create_list(void) 
{
    list_t* p_list = NULL; 

    p_list = xmalloc(sizeof(node_t)); 
    p_list->data = 0; 
    p_list->next = NULL; 
    
    return (p_list); 
} 

status_t insert_start(list_t* p_list, data_t new_data) 
{
    node_t* new_node = get_node(new_data); 

    new_node->next = p_list->next; 
    p_list->next = new_node; 

    return (SUCCESS); 
} 

status_t insert_end(list_t* p_list, data_t new_data) 
{
    node_t* new_node = get_node(new_data); 
    node_t* run = NULL; 

    run = p_list; 
    while(run->next != NULL) 
        run = run->next; 

    run->next = new_node; 

    return (SUCCESS); 
}

status_t insert_after(list_t* p_list, data_t e_data, data_t new_data) 
{
    node_t* run = NULL; 
    node_t* new_node = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    run = p_list->next; 
    while(run != NULL) 
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
    node_t* run = NULL, *run_prev = NULL; 
    node_t* new_node = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    run = p_list->next; 
    run_prev = p_list; 
    while(run != NULL)
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
    if(p_list->next == NULL) 
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

status_t get_end(list_t* p_list, data_t* p_end_data) 
{
    node_t* run = NULL; 

    if(p_list->next == NULL) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    while(run->next != NULL) 
        run = run->next; 

    *p_end_data = run->data; 
    return (SUCCESS); 
}

status_t pop_start(list_t* p_list, data_t* p_popped_data) 
{
    node_t* r_node = NULL;

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    r_node = p_list->next; 
    p_list->next = p_list->next->next; 

    *p_popped_data = r_node->data; 

    free(r_node); 
    r_node = NULL; 

    return (SUCCESS); 
}

status_t pop_end(list_t* p_list, data_t* p_popped_data) 
{
    node_t* remove_node = NULL; 
    node_t* run = NULL; 
    node_t* run_prev = NULL; 

    if(p_list->next == NULL) 
        return (LIST_EMPTY); 

    run = p_list->next; 
    run_prev = p_list; 
    while(run->next != NULL)
    {
        run_prev = run; 
        run = run->next; 
    } 

    *p_popped_data = run->data; 

    run_prev->next = NULL; 
    free(run); 
    run = NULL; 

    return (SUCCESS); 
}

status_t remove_start(list_t* p_list)
{
    node_t* start_node = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    start_node = p_list->next; 
    p_list->next = start_node->next; 

    free(start_node); 
    start_node = NULL; 

    return (SUCCESS); 
}

status_t remove_end(list_t* p_list) 
{
    node_t* run = NULL; 
    node_t* run_prev = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    run = p_list->next; 
    run_prev = p_list; 
    while(run->next != NULL)
    {
        run_prev = run; 
        run = run->next; 
    }

    run_prev->next = NULL; 
    free(run); 
    run = NULL; 

    return (SUCCESS); 
}

status_t remove_data(list_t* p_list, data_t r_data) 
{
    list_t* run = NULL; 
    node_t* run_prev = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    run = p_list->next; 
    run_prev = p_list; 
    while(run != NULL)
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

len_t get_list_length(list_t* p_list) 
{
    node_t* run = NULL; 
    len_t length = 0; 

    run = p_list->next; 
    while(run != NULL) 
    {
        length = length + 1; 
        run = run->next; 
    }

    return (length); 
}

void show_list(list_t* p_list, const char* msg) 
{
    node_t* run = NULL; 

    if(msg) 
        puts(msg); 

    printf("[START] -> "); 
    
    run = p_list->next; 
    while(run != NULL) 
    {
        printf("[%d] -> ", run->data); 
        run = run->next; 
    }

    printf("[END]\n"); 
}

status_t is_list_empty(list_t* p_list) 
{
    if(p_list->next == NULL) 
        return (TRUE); 
    return (FALSE); 
}

status_t find(list_t* p_list, data_t f_data) 
{
    node_t* run = NULL; 

    run = p_list->next; 
    while(run != NULL) 
    {
        if(run->data == f_data) 
            return (TRUE);     
        run = run->next; 
    }

    return (FALSE); 
}

status_t clear_list(list_t* p_list) 
{
    node_t* run_next = NULL; 
    node_t* run = NULL; 

    if(p_list->next == NULL)
        return (SUCCESS); 

    run = p_list->next; 
    run_next = p_list->next->next; 
    while(run_next != NULL) 
    {
        free(run); 
        run = run_next; 
        run_next = run_next->next; 
    }

    free(run); 
    run = NULL;

    p_list->next = NULL;  

    return (SUCCESS); 
}

status_t destroy_list(list_t** pp_list) 
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 
    list_t* p_list = *pp_list; 

    if(p_list->next == NULL) 
    {
        free(*pp_list); 
        *pp_list = NULL; 

        return (SUCCESS); 
    }

    run = p_list->next; 
    run_next = p_list->next->next;   
    while(run_next != NULL) 
    {
        free(run); 
        run = run_next; 
        run_next = run_next->next; 
    }

    free(run); 
    run = NULL; 

    free(p_list); 
    p_list = NULL; 

    *pp_list = NULL; 

    return (SUCCESS); 
}

list_t* merge_lists(list_t* p_list_1, list_t* p_list_2) 
{
    list_t* p_merged_list = NULL; 
    node_t* run1 = NULL; 
    node_t* run2 = NULL; 

    p_merged_list = create_list(); 

    run1 = p_list_1->next; 
    run2 = p_list_2->next; 
    while(TRUE) 
    {
        if(run1 == NULL) 
        {
            while(run2 != NULL) 
            {
                insert_end(p_merged_list, run2->data); 
                run2 = run2 ->next; 
            }
            break; 
        }
        else if(run2 == NULL) 
        {
            while(run1 != NULL) 
            {
                insert_end(p_merged_list, run1->data); 
                run1 = run1->next; 
            }
            break; 
        }

        else if(run1->data < run2->data) 
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
    list_t* p_concatenated_list = NULL; 
    node_t* run = NULL; 

    p_concatenated_list = create_list(); 

    run = p_list_1->next; 
    while(run != NULL) 
    {
        insert_end(p_concatenated_list, run->data); 
        run = run->next; 
    }
    run = p_list_2->next; 
    while(run != NULL) 
    {
        insert_end(p_concatenated_list, run->data); 
        run = run->next; 
    }

    return (p_concatenated_list); 
}

status_t concat_lists(list_t* p_list_1, list_t** pp_list_2) 
{
    node_t* run = NULL; 

    run = p_list_1; 
    while(run->next != NULL)
        run = run->next; 

    run->next = (*pp_list_2)->next; 

    free(*pp_list_2); 
    *pp_list_2 = NULL; 

    return (SUCCESS); 
}

list_t* get_reversed_list(list_t* p_list) 
{
    list_t* reversed_list = NULL; 
    node_t* run = NULL; 

    reversed_list = create_list(); 

    run = p_list->next; 
    while(run != NULL) 
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

    run = p_list->next->next; 
    current_start = p_list->next; 
    original_start = p_list->next; 
    while(run != NULL) 
    {
        run_next = run->next; 

        run->next = current_start; 
        p_list->next = run; 
        current_start = run; 

        run = run_next; 
    }

    original_start->next = NULL; 
    return (SUCCESS); 
}

data_t* to_array(list_t* p_list, size_t* pN) 
{
    data_t* p_array = NULL; 
    node_t* run = NULL; 
    len_t length = 0; 
    len_t i = 0; 

    length = get_list_length(p_list); 
    if(length <= 0) 
        return (NULL); 

    p_array = (data_t*)xmalloc(length * sizeof(data_t)); 
    
    run = p_list->next; 
    i = 0; 
    while(run != NULL) 
    {
        p_array[i] = run->data; 

        run = run->next; 
        i = i + 1; 
    }  
    
    *pN = length; 
    return (p_array); 
}

list_t* to_list(data_t* p_array, size_t N) 
{
    list_t* new_list = NULL; 

    new_list = create_list(); 

    for(size_t i = 0; i < N; i++) 
        insert_end(new_list, p_array[i]); 

    return (new_list); 
}

static status_t generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end) 
{
    p_mid->next = p_end; 
    p_beg->next = p_mid; 
}

static status_t generic_delete(node_t* p_delete_prev, node_t* p_delete_node) 
{
    p_delete_prev->next = p_delete_node->next; 
    free(p_delete_node); 
    p_delete_node = NULL; 
}

static node_t* get_node(data_t new_data) 
{
    node_t* new_node = NULL; 

    new_node = (node_t*)xmalloc(sizeof(node_t)); 
    new_node->next = NULL; 
    new_node->data = new_data; 

    return (new_node); 
}

static node_t* search_node(list_t* p_list, data_t s_data) 
{
    node_t* run = NULL; 

    if(p_list->next == NULL) 
        return (NULL); 

    run = p_list->next; 
    while(run != NULL) 
    {
        if(run->data == s_data) 
            return (run); 
        run = run->next; 
    }

    return (NULL); 
}

static void* xmalloc(size_t nr_bytes) 
{
    void* p = NULL; 

    p = malloc(nr_bytes); 
    if(p == NULL)
    {
        fprintf(stderr, "fatal: out of memory"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}

