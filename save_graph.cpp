#include "akinator.h"

void write_tree(const char* file_name, tree *graph)
{
    assert(graph != nullptr);
    
    FILE *file = open_file(file_name, "wb");

    write_node(file, graph->root_node);

    fclose(file);
}

void write_tree(FILE *file, tree *graph)
{
    assert(file  != nullptr);
    assert(graph != nullptr);
    
    write_node(file, graph->root_node);
}

void write_node(FILE *file, node *current_node)
{    
    assert(file != nullptr);
    assert(current_node != nullptr);
    
    fprintf(file, "{\"%s\"\n", current_node->value);

    if (current_node->left_node != nullptr)    
    {
        write_node(file, current_node->left_node);
    } 

    if (current_node->right_node != nullptr)
    {
        write_node(file, current_node->right_node);
    }

    fprintf(file, "}");

    return;
}


void write_tree_graphviz(const char *name_file, tree *graph)
{
    assert(graph != nullptr);
    
    FILE *file = open_file(name_file, "wb");

    write_tree_graphviz(file, graph);

    fclose(file);
}

void write_tree_graphviz(FILE *file, tree *graph)
{
    assert(file  != nullptr);
    assert(graph != nullptr);

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


#define FWRITE_CHILD(child_type)                                                                     \
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

void fill_object_graphviz(const char *file_name, Stack *stack, char *color)
{
    assert(stack != nullptr);
    assert(color != nullptr);

    char key[] = "rb+";

    FILE *file = open_file(file_name, key);

    fill_object_graphviz(file, stack, color);
}

void fill_object_graphviz(FILE *file, Stack *stack, char *color)
{
    assert(file  != nullptr);
    assert(stack != nullptr);
    assert(color != nullptr);

    fseek(file, 0L, SEEK_SET);

    fprintf(file, "digraph G{\n");

    size_t file_size = 0;
    
    file_size = get_file_size(file);
    
    fseek(file, (long int)(file_size) - 1, SEEK_SET);

    while (0 < stack->size)
    {
        
        fprintf(file, "\"%s\"[color=\"%s\" style=filled];\n", pop_stack(stack)->value, color);
    }

    fprintf(file, "}");
    
    fclose(file);
}

void fill_characterist_create_png(const char* graph_file_name, const char *png_file_name, Stack* characteristics_object, char *color)
{
    assert(graph_file_name        != nullptr);
    assert(png_file_name          != nullptr);
    assert(characteristics_object != nullptr);
    assert(color                  != nullptr);
    
    fill_object_graphviz(graph_file_name, characteristics_object, color);

    create_png(graph_file_name, png_file_name);
}

void create_png(const char *graph_file_name, const char* png_file_name)
{
    assert(graph_file_name != nullptr);
    assert(png_file_name   != nullptr);

    //"dot -T png graph.dot > graph.png"
    char str[] = "dot -T png ";
    
    strcat(str, graph_file_name);
    strcat(str, ">");
    strcat(str, png_file_name);
    
    system(str);
}