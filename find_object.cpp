#include "akinator.h"

const char *default_database_file_name   = "tree.database";
const char *default_graph_file_name      = "graph.dot";
const char *default_png_file_name        = "graph.png";

void find_object(char *object,  const char *database_file_name, const char* graph_file_name, const char *png_file_name);


void find_object(char *object,  const char *database_file_name, const char* graph_file_name, const char *png_file_name)
{
    bool found = false;

    Stack object_characteristics = {};

    stack_constructor(&object_characteristics);

    tree graph = {};

    construct_tree(&graph);
    
    found = try_get_characteristics(database_file_name, &graph, &object_characteristics, object);

    print_found(found, object);
    
    char color[] = "yellow";

    fill_characterist_create_png(graph_file_name, png_file_name, &object_characteristics, color);

    destruct_tree(&graph);
    
}


int main(int argc, char *argv[])
{
    type_value_node object = "";

    const char *database_file_name = default_database_file_name;
    const char *graph_file_name    = default_graph_file_name;
    const char *png_file_name      = default_png_file_name;
    
    if (argc >= 2)
    {
        memcpy(object, argv[1], MAX_SIZE_CHARACTER);
    }
    
    if (argc >= 3)
    {
        database_file_name = argv[2];
    }

    if (argc >= 4)
    {
        graph_file_name = argv[3];
    }

    if (argc >= 5)
    {
        png_file_name = argv[4];
    }

    find_object(object, database_file_name, graph_file_name, png_file_name);
}