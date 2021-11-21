#include "akinator.h"

bool find_object(char *value, Stack *stack);

bool try_get_characteristics(const char *database_file_name, tree *graph, Stack *object_characteristics, char *object)
{
    get_tree(database_file_name, graph);

    bool found = false;
 
    found = get_characteristic(graph, object, object_characteristics);

    return found;
}

bool get_characteristic(tree *graph, char *value, Stack *characteristic_stack)
{    
    push_stack(characteristic_stack, &graph->root_node);

    bool found = false;
    
    found = find_object(value, characteristic_stack);

    return found;
}

bool find_object(char *value, Stack *characteristic_stack)
{   
    node *current_node = top_stack(characteristic_stack);

    if (strcmp(current_node->value, value) == 0)
    {                
        return true;
    }

    bool found = false;

    if (current_node->right_node != nullptr)
    {
        push_stack(characteristic_stack, &(current_node->right_node));
        
        found = find_object(value, characteristic_stack);
        
        if (found == false)
        {
            pop_stack(characteristic_stack);
        }

        else
        {
            return true;
        }
    }

    if (current_node->left_node != nullptr)
    {
        push_stack(characteristic_stack, &current_node->left_node);
        
        found = find_object(value, characteristic_stack);

        if (found == false)
        {
            pop_stack(characteristic_stack);
        }

        else
        {
            return true;
        }
    }

    return found;
}

void print_found(bool found, char *object)
{
    if (found)
    {
        printf("Object: %s was found\n", object);
    }

    else
    {
        printf("Object: %s was not found\n", object);
    }
}