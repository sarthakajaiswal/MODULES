#include "list.h" 

list_t* create_list(void) 
{
    node_t* new_node = get_node(0); 

    new_node->next = new_node; 
    new_node->prev = new_node; 

    return (new_node); 
}

status_t insert_start(list_t* p_list, data_t new_data) 
{
    node_t* new_node = NULL; 

    new_node = get_node(new_data); 
    new_node->next = p_list->next; 
    new_node->prev = p_list; 
    p_list->next->prev = new_node; 
    p_list->next = new_node; 

    return (SUCCESS); 
}

status_t insert_end(list_t* p_list, data_t new_data) 
{
    node_t* new_node = NULL; 
    
    new_node = get_node(new_data); 
    new_node->next = p_list; 
    new_node->prev = p_list->prev; 
    p_list->prev->next = new_node; 
    p_list->prev = new_node; 

    return (SUCCESS); 
}

status_t insert_before(list_t* p_list, data_t e_data, data_t new_data) 
{
    node_t* new_node = NULL; 
    node_t* run = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    run = p_list->next; 
    while(run != p_list) 
    {
        if(run->data == e_data) 
        {
            new_node = get_node(new_data); 
            new_node->next = run->next; 
            new_node->prev = run; 
            run->next->prev = new_node; 
            run->next = new_node; 

            return (SUCCESS); 
        }

        run = run->next; 
    } 

    return (LIST_DATA_NOT_FOUND); 
}

status_t insert_after(list_t* p_list, data_t e_data, data_t new_data) 
{
    node_t* new_node = NULL; 
    node_t* run = NULL; 

    if(p_list->next == p_list)
        return (LIST_EMPTY); 

    run = p_list->next; 
    while(run != p_list) 
    {
        if(run->data == e_data) 
        {
            new_node = get_node(new_data); 

            new_node->next = run; 
            new_node->prev = run->prev; 
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
    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

status_t get_end(list_t* p_list, data_t* p_end_data) 
{
    if(is_list_empty(p_list) == TRUE)  
        return (LIST_EMPTY); 

    *p_end_data = p_list->prev->data; 
    return (SUCCESS); 
}

status_t remove_start(list_t* p_list) 
{
    node_t* p_start_node = NULL; 

    if(p_list->next == p_list) 
        return (LIST_EMPTY); 

    p_start_node = p_list->next; 

    p_start_node->next->prev = p_list; 
    p_list->next = p_start_node->next; 

    free(p_start_node); 
    p_start_node = NULL; 

    return (SUCCESS); 
} 

status_t remove_end(list_t* p_list) 
{
    node_t* p_end_node = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    p_end_node = p_list->prev; 

    p_end_node->prev->next = p_list; 
    p_list->prev = p_end_node->prev; 

    free(p_end_node); 
    return (SUCCESS); 
}

status_t remove_data(list_t* p_list, data_t r_data) 
{
    node_t* run = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY);  

    run = p_list->next; 
    while(run != p_list) 
    {
        if(run->data == r_data) 
        {
            run->prev->next = run->next; 
            run->next->prev = run->prev; 

            free(run); 
            run = NULL; 

            return (SUCCESS); 
        }

        run = run->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
} 

status_t pop_start(list_t* p_list, data_t* p_popped_data) 
{
    node_t* p_start_node = NULL; 

    if(is_list_empty(p_list) == TRUE)
        return (LIST_EMPTY); 

    p_start_node = p_list->next; 

    p_list->next = p_list->next->next; 
    p_start_node->next->prev = p_list; 

    *p_popped_data = p_start_node->data; 

    free(p_start_node); 
    return (SUCCESS); 
} 

status_t pop_end(list_t* p_list, data_t* p_popped_data) 
{
    node_t* p_end_node = NULL; 

    if(is_list_empty(p_list) == TRUE) 
        return (LIST_EMPTY); 

    p_end_node = p_list->prev; 

    p_list->prev->prev->next = p_list; 
    p_list->prev = p_list->prev->prev; 

    *p_popped_data = p_end_node->data; 

    free(p_end_node); 
    p_end_node = NULL; 

    return (SUCCESS); 
} 

status_t is_list_empty(list_t* p_list) 
{
    return ((p_list->prev==p_list) && (p_list->next == p_list)); 
}

len_t get_list_length(list_t* p_list) 
{
    len_t length = 0; 
    node_t* run = NULL; 

    run = p_list->next; 
    while(run != p_list) 
    {
        length = length + 1; 
        run = run->next; 
    }

    return (length); 
} 

status_t find(list_t* p_list, data_t f_data) 
{
    node_t* run = NULL; 

    run = p_list->next; 
    while(run != p_list) 
    {
        if(run->data == f_data) 
            return (TRUE); 

        run = run->next; 
    }

    return (FALSE); 
}

list_t* to_list(data_t* p_array, len_t N) 
{
    list_t* new_list = NULL; 
    len_t i; 

    new_list = create_list(); 

    for(i = 0; i < N; i++) 
    {
        insert_end(new_list, p_array[i]); 
    }

    return (new_list); 
} 

data_t* to_array(list_t* p_list, len_t* pN) 
{
    data_t* p_array = NULL; 
    len_t length; 
    node_t* run = NULL; 

    length = get_list_length(p_list); 
    if(length <= 0) 
        return (NULL); 

    p_array = (data_t*)xmalloc(length * sizeof(data_t)); 
    
    run = p_list->next; 
    len_t i = 0; 
    while(run != p_list) 
    {
        p_array[i] = run->data; 
        i = i + 1; 
        run = run->next; 
    }

    return (p_array); 
}

void show_list(list_t* p_list, const char* msg) 
{
    node_t* run = NULL; 

    if(msg) 
        puts(msg); 

    printf("\\->[START] <-> "); 

    run = p_list->next; 
    while(run != p_list) 
    {
        printf("[%d] <-> ", run->data); 
        run = run->next; 
    }

    printf("[END] <-/\n"); 
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
    p_list->prev = p_list; 

    return (SUCCESS); 
} 

status_t destroy_list(list_t** pp_list) 
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 
    list_t* p_list = *pp_list; 

    run = p_list->next; 
    while(run != p_list) 
    {
        run_next = run->next; 
        free(run); 
        run = run->next; 
    }
    p_list->next = p_list; 

    free(p_list); 
    p_list = NULL; 

    *pp_list=  NULL; 
    return (SUCCESS); 
}  

// interlist routines 
list_t* get_concatenated_list(list_t* p_list_1, list_t* p_list_2) 
{
    list_t* new_list = NULL; 
    node_t* run = NULL; 

    new_list = create_list(); 
    run = p_list_1->next; 
    while(run != p_list_1) 
    {
        insert_end(new_list, run->data); 
        run = run->next; 
    }

    run = p_list_2->next; 
    while(run != p_list_2) 
    {
        insert_end(new_list, run->data); 
        run = run->next; 
    }

    return (new_list); 
}

status_t concat_lists(list_t* p_list_1, list_t* p_list_2) 
{
    node_t* run = NULL; 

    if(p_list_2->next == p_list_2) 
        return (SUCCESS); 

    run = p_list_1->prev; 
    
    run->next = p_list_2->next; 
    p_list_2->next->prev = run; 
    p_list_1->prev = p_list_2->prev; 
    p_list_2->prev->next = p_list_1; 

    p_list_2->next = p_list_2; 
    p_list_2->prev = p_list_2; 

    return (SUCCESS); 
}

list_t* get_reversed_list(list_t* p_list) 
{
    list_t* new_list = NULL; 
    node_t* run = NULL; 

    new_list = create_list(); 

    run = p_list->next; 
    while(run != p_list) 
    {
        insert_start(new_list, run->data); 
        run = run->next; 
    }

    return (new_list); 
}

status_t reverse_list(list_t* p_list) 
{
    node_t* current_start = NULL; 
    node_t* original_start = NULL; 
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    if(p_list->next == p_list || p_list->next->next == p_list) 
        return (SUCCESS); 

    current_start = p_list->next; 
    original_start = p_list->next; 
    run = original_start->next;  
    while(run != p_list) 
    {
        run_next = run->next; 

        run->next = current_start; 
        run->prev = p_list; 
        p_list->next = run; 
        current_start->prev = run; 

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
    list_t* merged_list = NULL; 

    merged_list = create_list(); 
    
    run1 = p_list_1->next; 
    run2 = p_list_2->next; 
    while(1) 
    {
        if(run1 == p_list_1) 
        {
            while(run2 != p_list_2)
            {
                insert_end(merged_list, run2->data); 
                run2 = run2->next; 
            }
            break; 
        }
        else if(run2 == p_list_2) 
        {
            while(run1 != p_list_1) 
            {
                insert_end(merged_list, run1->data); 
                run1 = run1->next; 
            }
            break; 
        }

        if(run1->data < run2->data) 
        {
            insert_end(merged_list, run1->data); 
            run1 = run1->next; 
        }
        else 
        {
            insert_end(merged_list, run2->data); 
            run2 = run2->next; 
        }
    }

    return (merged_list); 
}

// helper routines 
static node_t* get_node(data_t new_data) 
{
    node_t* new_node = NULL; 

    new_node = xmalloc(sizeof(node_t)); 
    new_node->data = new_data; 
    new_node->prev = NULL; 
    new_node->next = NULL; 

    return (new_node); 
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
