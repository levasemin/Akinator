#include "akinator.h"

const char *default_database_file_name   = "tree.database";
const char *default_save_file_name       = "save.database";
const char *default_graph_file_name      = "graph.dot";
const char *default_png_file_name        = "graph.png";

void play (const char *database_file_name, const char *save_file_name, const char *graph_file_name, const char *png_file_name);


void play (const char *database_file_name, const char *save_file_name, const char *graph_file_name, const char *png_file_name)
{
    tree graph = {};

    construct_tree(&graph);
    
    get_tree(database_file_name, &graph);

    play_mode(&graph);

    write_tree(save_file_name, &graph);
    
    write_tree_graphviz(graph_file_name, &graph);

    create_png(graph_file_name, png_file_name);

    destruct_tree(&graph);
}

//TODO: while scanf != end: void functions type of act
int main(int argc, char *argv[])
{
    const char *database_file_name = default_database_file_name;
    const char *save_file_name     = default_save_file_name;
    const char *graph_file_name    = default_graph_file_name;
    const char *png_file_name      = default_png_file_name;
    
    if (argc >= 2)
    {
        database_file_name = argv[1];
    }

    if (argc >= 3)
    {
        save_file_name = argv[2];
    }

    if (argc >= 4)
    {
        graph_file_name = argv[3];
    }

    if (argc >= 5)
    {
        png_file_name = argv[4];
    }
    
    play(database_file_name, save_file_name, graph_file_name, png_file_name);
}