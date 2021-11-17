#include "akinator.h"

bool find_object(type_value_node value, Stack *stack);

void get_characteristic(tree *my_tree, type_value_node value, tree *charactist_tree)
{
    Stack stack = {};

    stack_constructor(&stack);
    
    push_stack(&stack, &my_tree->root_node);

    find_object(value, &stack);
    
    constuct_tree(charactist_tree);
    
    node *current_node = charactist_tree->root_node;
    
    for (size_t i = 0; i < stack.size; ++i)
    {
        node *current_charact = *(stack_type *)(stack.data + sizeof(stack.stack_canary) + sizeof(stack_type) * i);
        
        construct_node(&current_node, current_charact->value);

        current_node = current_node->left_node;
    }
}

bool find_object(type_value_node value, Stack *stack)
{   
    node *current_node = top_stack(stack);

    if (strcmp(current_node->value, value) == 0)
    {
        push_stack(stack, &current_node);
        push_stack(stack, &(current_node->left_node));

        return true;
    }

    bool found = false;

    if (current_node->right_node != nullptr)
    {
        push_stack(stack, &(current_node->left_node));
        
        bool found = find_object(value, stack);
        
        if (found == false)
        {
            pop_stack(stack);
        }
    }

    if (current_node->left_node != nullptr)
    {
        push_stack(stack, &current_node->right_node);
        
        bool found = find_object(value, stack);

        if (found == false)
        {
            pop_stack(stack);
        }
    }

    return found;
}