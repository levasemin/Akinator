#include "akinator.h"

void write_tree_graphviz(FILE *file, tree *graph);



void dump_tree(const char* database_file_name, tree *graph)
{
    assert(graph != nullptr);
    
    FILE *database_file = open_file(database_file_name, "wb");

    dump_tree(database_file, graph);

    fclose(database_file);
}

void dump_tree(FILE *database_file, tree *graph)
{
    assert(database_file  != nullptr);
    assert(graph != nullptr);
    
    write_tree(database_file, graph->root_node);
}

void write_tree(FILE *database_file, node *current_node)
{    
    assert(database_file != nullptr);
    assert(current_node != nullptr);
    
    write_node(database_file, current_node);

    //fseek(file, -1L, SEEK_END);

    //fprintf(database_file, "{\"%s\"\n", current_node->value);

    if (current_node->left_node != nullptr)    
    {
        write_tree(database_file, current_node->left_node);
    } 

    if (current_node->right_node != nullptr)
    {
        write_tree(database_file, current_node->right_node);
    }

    fprintf(database_file, "}");

    return;
}

void write_node(FILE *database_file, node *current_node)
{
    fseek(database_file, -1L, SEEK_END);

    fprintf(database_file, "{\"%s\"\n", current_node->value);

    fprintf(database_file, "}");
}

void write_tree_graphviz(const char *graphviz_name_file, tree *graph)
{
    assert(graph != nullptr);
    
    FILE *graphviz_file = open_file(graphviz_name_file, "wb");

    write_tree_graphviz(graphviz_file, graph);

    fclose(graphviz_file);
}

void write_tree_graphviz(FILE *graphviz_file, tree *graph)
{
    assert(graphviz_file  != nullptr);
    assert(graph != nullptr);

    Stack stack = {};

    stack_constructor(&stack);

    push_stack(&stack, &graph->root_node);

    while (stack.size != 0)
    {
        node *current_node = pop_stack(&stack);
        
        write_node_graphviz(graphviz_file, current_node);

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
    fprintf(graphviz_file, "\"%s\"->\"%s\";\n", current_node->value, current_node->child_type##_node->value);


//TODO: написать функцию для printf digraph, то есть функция, которая первоначально запускается перед дозаписыванием, fseek(file, -1, SET_END), ftell
//fclose везде 

FILE *create_graphviz_file(const char *graphviz_file_name)
{
    FILE *graphviz_file = fopen(graphviz_file_name, "wb");

    fprintf(graphviz_file, "digraph G{\n}");

    return graphviz_file;
}

void write_node_graphviz(FILE *graphviz_file, node *current_node)
{    
    assert(graphviz_file         != nullptr);
    assert(current_node != nullptr);
    
    size_t file_size = 0;
            
    fseek(graphviz_file, -1L, SEEK_END);

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
        fprintf(graphviz_file, "\"%s\";\n", current_node->value);
    }

    fprintf(graphviz_file, "}");
}

void fill_object_graphviz(const char *graphviz_file_name, Stack *stack, char *color)
{
    assert(stack != nullptr);
    assert(color != nullptr);

    FILE *file = open_file(graphviz_file_name, "rb+");

    fill_object_graphviz(file, stack, color);

    fclose(file);
}

void fill_object_graphviz(FILE *graphviz_file, Stack *stack, char *color)
{
    assert(graphviz_file  != nullptr);
    assert(stack != nullptr);
    assert(color != nullptr);
    
    fseek(graphviz_file, -1L, SEEK_END);

    while (0 < stack->size)
    {
        fprintf(graphviz_file, "\"%s\"[color=\"%s\" style=filled];\n", pop_stack(stack)->value, color);
    }

    fprintf(graphviz_file, "}");
    
    fclose(graphviz_file);
}

void dump_tree_graphviz(const char* graphviz_file_name, tree *graph, Stack* characteristics_object, char *color)
{
    assert(graphviz_file_name != nullptr);
    assert(graph              != nullptr);

    FILE *graphviz_file = create_graphviz_file(graphviz_file_name);
    
    dump_tree_graphviz(graphviz_file, graph, characteristics_object, color);

    fclose(graphviz_file);
}

void dump_tree_graphviz(FILE* graphviz_file, tree *graph, Stack* characteristics_object, char *color)
{
    assert(graphviz_file != nullptr);
    assert(graph         != nullptr);

    write_tree_graphviz(graphviz_file, graph);

    if (characteristics_object != nullptr)
    {
        fill_object_graphviz(graphviz_file, characteristics_object, color);
    }
}

void create_png(const char *graph_file_name, const char* png_file_name)
{
    assert(graph_file_name != nullptr);
    assert(png_file_name   != nullptr);

    //"dot -T png graph.dot > graph.png"
    char str[100] = "dot -T png ";
    
    strcat(str, graph_file_name);
    strcat(str, ">");
    strcat(str, png_file_name);
    
    system(str);
}