#include "akinator.h"

void write_tree(const char* file_name, tree *graph)
{
    node *current_node = graph->root_node;

    char key[] = "wb";

    FILE *file = open_file(file_name, key);

    write_tree(file, current_node);
}

void write_tree(FILE *file, tree *graph)
{
    node *current_node = graph->root_node;

    write_tree(file, current_node);
}

void write_tree(FILE *file, node *current_node)
{    
    write_node(file, current_node);

    if (current_node->left_node != nullptr)    
    {
        write_tree(file, current_node->left_node);
    } 

    if (current_node->right_node != nullptr)
    {
        write_tree(file, current_node->right_node);
        fprintf(file, "}");
    }

    return;
}

void write_node(char *file_name, node *current_node)
{
    char key[] = "rb+";

    FILE *file = open_file(file_name, key);

    write_node(file, current_node);
}

void write_node(FILE *file, node *current_node)
{
    assert(file         != nullptr);
    assert(current_node != nullptr);

    if (current_node->left_node != nullptr || current_node->right_node != nullptr)
    {
        fprintf(file, "{\"%s\"\n", current_node->value);
    }

    else
    {
        fprintf(file, "{\"%s\"}\n", current_node->value);
    }
}

void write_tree_graphviz(const char *name_file, tree *graph)
{
    assert(graph != nullptr);
    
    char key[] = "wb";

    FILE *file = open_file(name_file, key);

    write_tree_graphviz(file, graph);

    fclose(file);
}

void write_tree_graphviz(FILE *file, tree *graph)
{
    fprintf(file, "digraph G{\n}");

    Stack stack = {};

    stack_constructor(&stack);

    push_stack(&stack, &graph->root_node);

    while (stack.size != 0)
    {
        node *current_node = pop_stack(&stack);
        
        write_node_graphviz(file, current_node);

        if (current_node->right_node != nullptr)  
        {
            push_stack(&stack, &(current_node->right_node));
        }
        
        if (current_node->left_node != nullptr)
        {
            push_stack(&stack, &(current_node->left_node));
        }
    }

}

void write_node_graphviz(const char *name_file, node *current_node)
{
    assert(name_file    != nullptr);
    assert(current_node != nullptr);
    
    char key[] = "rb+";

    FILE *file = fopen(name_file, key);

    assert(file != nullptr);

    write_node(file, current_node);
     
}

#define FWRITE_CHILD(child_type)                                                              \
    fprintf(file, "\"%s\"->\"%s\";\n", current_node->value, current_node->child_type##_node->value);


void write_node_graphviz(FILE *file, node *current_node)
{    
    assert(file         != nullptr);
    assert(current_node != nullptr);
    
    size_t file_size = 0;
    
    fseek(file, 0L, SEEK_SET);
    
    fprintf(file, "digraph G{\n");

    file_size = get_file_size(file);
    
    fseek(file, (long int)(file_size) - 1, SEEK_SET);

    if (current_node->left_node != nullptr)  
    {
        FWRITE_CHILD(left)                
    }
    
    if (current_node->right_node != nullptr)
    {
        FWRITE_CHILD(right)
    }

    else
    {
        fprintf(file, "\"%s\";\n", current_node->value);
    }

    fprintf(file, "}");
}

void create_png(const char *graph_file_name, const char* png_file_name)
{
    //"dot -T png graph.dot > graph.png"
    char str[] = "dot -T png ";
    
    strcat(str, graph_file_name);
    strcat(str, ">");
    strcat(str, png_file_name);
    
    system(str);
}