#include "list.h" 

list_t* create_list(void) 
{
    return (get_node(0)); 
}

status_t insert_start(list_t* p_list, data_t new_data) 
{
    node_t* new_node = NULL; 

    new_node = get_node(new_data); 

    new_node->next = p_list->next; 
    new_node->prev = p_list; 
    if(p_list->next != NULL) 
        p_list->next->prev = new_node; 
    p_list->next = new_node; 

    return (SUCCESS); 
}

status_t insert_end(list_t* p_list, data_t new_data) 
{
    node_t* new_node = NULL; 
    node_t* run = NULL;
     
    run = p_list; 
    while(run->next != NULL) 
        run = run->next; 

    new_node = get_node(new_data); 

    new_node->next = run->next; 
    new_node->prev = run; 
    run->next = new_node; 

    return (SUCCESS); 
}

status_t insert_after(list_t* p_list, data_t e_data, data_t new_data) 
{
    node_t* run = NULL; 
    node_t* new_node = NULL; 

    run = p_list->next; 
    while(run != NULL) 
    {
        if(run->data == e_data) 
        {
            new_node = get_node(new_data); 

            new_node->next = run->next; 
            new_node->prev = run; 
            if(run->next != NULL) 
                run->next->prev = new_node; 
            run->next = new_node; 

            return (SUCCESS); 
        }

        run = run->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t insert_before(list_t* p_list, data_t e_data, data_t new_data)
{
    node_t* new_node; 
    node_t* run = NULL; 

    run = p_list->next; 
    while(run != NULL) 
    {
        if(run->data == e_data) 
        {
            new_node = get_node(new_data); 

            new_node->prev = run->prev; 
            new_node->next = run; 
            run->prev->next = new_node; 
            run->prev = new_node; 

            return (SUCCESS); 
        }

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
    // variable declarations 
    node_t* run = NULL; 

    // code 
    if(p_list->next == NULL && p_list->prev == NULL)  
        return (LIST_EMPTY); 

    run = p_list; 
    while(run->next != NULL) 
        run = run->next; 

    *p_end_data = run->data; 

    return (SUCCESS); 
}

status_t remove_start(list_t* p_list) 
{
    node_t* p_remove_node = NULL; 

    if(p_list->next == NULL) 
        return (LIST_EMPTY); 

    p_remove_node = p_list->next; 

    if(p_list->next->next != NULL)
        p_list->next->next->prev = p_list; 
    p_list->next = p_list->next->next; 

    free(p_remove_node); 
    p_remove_node = NULL; 

    return (SUCCESS); 
}

status_t remove_end(list_t* p_list) 
{
    // variable declarations 
    node_t* run = NULL; 
    node_t* p_end_node = NULL; 

    // code 
    if(p_list->next == NULL) 
        return (LIST_EMPTY); 

    run = p_list; 
    while(run->next != NULL) 
        run = run->next; 

    p_end_node = run; 

    p_end_node->prev->next = NULL; 
    
    free(p_end_node); 
    p_end_node = NULL; 

    return (SUCCESS); 
}

status_t remove_data(list_t* p_list, data_t r_data) 
{
    node_t* run = NULL; 
    node_t* p_delete_node = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    p_delete_node = p_list->next; 
    while(p_delete_node != NULL) 
    {
        if(p_delete_node->data == r_data) 
        {
            p_delete_node->prev->next = p_delete_node->next; 
            if(p_delete_node->next != NULL) 
                p_delete_node->next->prev = p_delete_node->prev; 

            free(p_delete_node); 
            p_delete_node = NULL; 

            return (SUCCESS); 
        }

        p_delete_node = p_delete_node->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t pop_start(list_t* p_list, data_t* p_popped_data) 
{
    node_t* p_start_node = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    p_start_node = p_list->next; 

    if(p_start_node->next != NULL)
        p_start_node->next->prev = p_list; 
    p_list->next = p_start_node->next; 
    
    *p_popped_data = p_start_node->data; 

    free(p_start_node); 
    p_start_node = NULL; 

    return (SUCCESS); 
}

status_t pop_end(list_t* p_list, data_t* p_popped_data) 
{
    // variable declarations 
    node_t* p_end_node = NULL; 

    // code 
    if(p_list->next == NULL) 
        return (LIST_EMPTY); 

    p_end_node = p_list->next; 
    while(p_end_node->next != NULL) 
        p_end_node = p_end_node->next; 

    p_end_node->prev->next = NULL; 

    *p_popped_data = p_end_node->data; 

    free(p_end_node); 
    p_end_node = NULL; 

    return (SUCCESS); 
}

status_t is_list_empty(list_t* p_list) 
{
    if(p_list->next == NULL && p_list->prev == NULL) 
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

list_t* merge_lists(list_t* p_list_1, list_t* p_list_2) 
{
    list_t* merged_list = NULL; 
    node_t* run_1 = NULL; 
    node_t* run_2 = NULL; 

    merged_list = create_list(); 

    run_1 = p_list_1->next; 
    run_2 = p_list_2->next; 
    while(1) 
    {
        if(run_1 == NULL) 
        {
            while(run_2 != NULL) 
            {
                insert_end(merged_list, run_2->data); 
                run_2 = run_2 -> next; 
            }
            break; 
        }
        else if(run_2 == NULL) 
        {
            while(run_1 != NULL) 
            {
                insert_end(merged_list, run_1->data); 
                run_1 = run_1->next; 
            }
            break; 
        }

        if(run_1->data < run_2->data) 
        {
            insert_end(merged_list, run_1->data); 
            run_1 = run_1->next; 
        }
        else 
        {
            insert_end(merged_list, run_2->data); 
            run_2 = run_2->next; 
        }
    }

    return (merged_list); 
}

list_t* to_list(data_t* p_array, len_t N) 
{
    // variable declarations 
    len_t i; 
    list_t* new_list = NULL; 

    // code 
    new_list = create_list(); 

    for(i = 0; i < N; i++) 
        insert_end(new_list, p_array[i]); 

    return (new_list); 
}

list_t* get_reversed_list(list_t* p_list) 
{
    list_t* reversed_list = create_list(); 
    node_t* run = NULL; 

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
        run->prev = p_list; 
        current_start->prev = run; 
        p_list->next = run; 

        current_start = run; 
        run = run_next; 
    }

    original_start->next = NULL; 

    return (SUCCESS); 
}

list_t* get_concatenated_list(list_t* p_list_1, list_t* p_list_2)
{
    node_t* run = NULL; 
    list_t* new_list = NULL; 

    new_list = create_list(); 

    run = p_list_1->next; 
    while(run != NULL) 
    {
        insert_end(new_list, run->data); 
        run = run->next;  
    } 

    run = p_list_2->next; 
    while(run != NULL) 
    {
        insert_end(new_list, run->data); 
        run = run->next; 
    }  

    return (new_list); 
}

status_t concat_lists(list_t* p_list_1, list_t* p_list_2) 
{
    node_t* run = NULL; 

    if(p_list_2->next == NULL) 
        return (SUCCESS); 

    run = p_list_1; 
    while(run->next != NULL) 
        run = run->next; 

    run->next = p_list_2->next; 
    run->next->prev = run; 

    p_list_2->next = NULL; 
    return (SUCCESS); 
}

data_t* to_array(list_t* p_list, len_t* pN) 
{
    // variable declarations 
    len_t N = -1; 
    data_t* p_array = NULL; 
    node_t* run = NULL; 
    len_t i = 0; 

    // code 
    N = get_list_length(p_list); 

    if(N <= 0) 
        return (NULL); 

    p_array = (data_t*)xmalloc(N * sizeof(data_t)); 

    run = p_list->next; 
    i = 0; 
    while(run != NULL)
    {
        p_array[i] = run->data; 
        i = i + 1; 
    }

    *pN = N; 
    return (p_array); 
}

status_t clear_list(list_t* p_list) 
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    run = p_list->next; 
    while(run != NULL) 
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }

    p_list->next = NULL; 

    return (SUCCESS); 
}

status_t destroy_list(list_t** pp_list) 
{
    list_t* p_list; 
    node_t* run = NULL; 
    node_t* run_next = NULL; 
    node_t* p_delete_node = NULL; 

    p_list = *pp_list; 
    run = p_list->next; 
    while(run != NULL) 
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

len_t get_list_length(list_t* p_list) 
{
    // variable declarations 
    len_t length = 0; 
    node_t* run = NULL; 

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

    printf("[START] <-> "); 

    run = p_list->next; 
    while(run != NULL) 
    {
        printf("[%d] <-> ", run->data); 
        run = run->next; 
    }

    printf("[END]\n"); 
}

// generic routines 
static status_t generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end) 
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

static status_t generic_delete(node_t* p_delete_node) 
{
    if(p_delete_node->next != NULL)
        p_delete_node->next->prev = p_delete_node->prev; 

    p_delete_node->prev->next = p_delete_node->next; 

    free(p_delete_node); 

    return (SUCCESS); 
} 

// helper routines 
static node_t* get_node(data_t new_data) 
{
    node_t* new_node = NULL; 

    new_node = xmalloc(sizeof(node_t)); 
    new_node->next = NULL; 
    new_node->prev = NULL; 
    new_node->data = new_data; 

    return (new_node); 
}

static void* xmalloc(size_t nr_bytes) 
{
    void* p = NULL; 

    p = malloc(nr_bytes); 
    if(p == NULL) 
    {
        fprintf(stderr, "Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}

