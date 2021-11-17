#include "akinator.h"

FILE *open_file(const char *file_name, char *key)
{
    assert(file_name != nullptr);
    
    FILE *file = fopen(file_name, key);
    
    assert(file != nullptr);
    
    return file;
}

size_t get_file_size(FILE *file)
{
    assert(file != nullptr);

    size_t prev = ftell(file);

    fseek(file, 0L, SEEK_END);
    
    size_t file_size = ftell(file);
    
    fseek(file, prev, SEEK_SET);

    return file_size;
}

size_t read_file(const char *file_name, char **string)
{
    FILE *file = open_file(file_name, "rb");

    return read_file(file, string);
}
    
size_t read_file(FILE *file, char **string)
{
    assert(file != nullptr);

    size_t file_size = get_file_size(file);

    *string = (char *)calloc((file_size + 1), sizeof(char));
    assert(*string != nullptr);

    size_t count_elements = fread(*string, sizeof(char), file_size, file);

    (*string)[count_elements] = '$';

    return file_size;
}

#define DEBUG_GRAPHVIZ(graph_file, tree)            \
    getchar();                                                  \
    write_tree_graphviz(graph_file, tree);                  \
    system("dot -T png graph.dot > graph.png"); \
    system("start graph.png");            \


bool get_tree(tree *my_tree, char **string)
{
    Stack stack = {};
    
    stack_constructor(&stack);
    
    bool is_root = true;

    while ((*string = strchr(*string, '\"')) != nullptr)
    {
        type_value_node value = "";
        int count = 0;
        
        sscanf(*string, " \"%[^\"]\" ", value);

        *string = strchr(++(*string), '\"') + 1;

        node **new_node = nullptr;
                    
        if (is_root) 
        {
            new_node = &(my_tree->root_node);
                
            is_root = false;
        }

        else         
        {
            node *characterist = top_stack(&stack);

            if (characterist->left_node == nullptr && is_root == false)
            {
                new_node = &(characterist->right_node);

                construct_node(new_node, "nothing");

                new_node = &(characterist->left_node);

                construct_node(new_node, value);

            } 

            else if (characterist->left_node != nullptr && is_root == false)
            {            
                new_node = &(characterist->right_node);

                construct_node(new_node, value);
                
                pop_stack(&stack);
            }
        }

        if (strchr(*string, '{') != nullptr && strchr(*string, '{') < strchr(*string, '}'))
        {            
            construct_node(new_node, value);

            push_stack(&stack, new_node);

        }

        //DEBUG_GRAPHVIZ("graph.dot", my_tree);

    }

    write_tree_graphviz("graph.dot", my_tree);   
}