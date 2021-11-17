#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

void constuct_tree(tree *tree);

bool play_mode(const char* save_file_name, tree *my_tree);

bool construct_node(node **new_node, type_value_node value);

void get_characteristic(tree *my_tree, type_value_node value, tree *charactist_tree);

FILE *open_file(const char *file_name, char *key);

size_t get_file_size(FILE *file);


size_t read_file(const char *file_name, char **string);

size_t read_file(FILE *file, char **string);


void write_tree(const char* file_name, tree *graph);

void write_tree(FILE *file, tree *graph);

void write_tree(FILE *file, node *current_node);

void write_node(char *file_name, node *current_node);

void write_node(FILE *file, node *current_node);


void write_tree_graphviz(const char *name_file, tree *graph);

void write_tree_graphviz(FILE *file, tree *graph);

void write_node_graphviz(const char *name_file, node *current_node);

void write_node_graphviz(FILE *file, node *current_node);


bool get_tree(tree *my_tree, char **string);

void print_nodes(node *my_node);

void add_charactist(tree *my_tree, node **current_node, type_value_node characterist, type_value_node object);


void create_png(const char *graph_file_name, const char* png_file_name);

void create_png(FILE *graph_file, FILE *png_file);