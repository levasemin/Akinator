#include "akinator.h"

const char *file_name       = "tree.database";
const char *graph_file_name = "graph.dot";
const char *png_file_name   = "graph.png";
const char *save_file_name = "save.dot";

int main()
{
    tree my_tree = {};

    constuct_tree(&my_tree);

    char *string = nullptr;

    read_file(file_name, &string);
    
    //write_tree(graph_file_name, &my_tree);
    get_tree(&my_tree, &string);

    //write_tree(save_file_name, &my_tree);
    //write_tree_graphviz(graph_file_name, &my_tree);
    //play_mode(save_file_name, &my_tree);

    tree object_tree = {};
    
    type_value_node value_object = "Bogdanow";

    //get_characteristic(&my_tree, value_object, &my_tree);

    write_tree_graphviz(graph_file_name, &object_tree);

    create_png(graph_file_name, png_file_name);
}
