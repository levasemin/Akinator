#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

#define DEBUG_GRAPHVIZ(graph_file, tree)                        \
    getchar();                                                  \
    write_tree_graphviz(graph_file, tree);                      \
    system("dot -T png graph.dot > graph.png");                 \
    system("start graph.png");                                  \

extern type_value_node DEFAULT_VALUE;

void construct_tree(tree *tree);

bool construct_node(node **new_node, char *value);

void destruct_tree(tree *graph);

bool destruct_node(node **new_node);

bool play_mode(tree *graph);


bool try_get_characteristics(const char *database_file_name, tree *graph, Stack *characteristics_object, char *object);

bool get_characteristic(tree *graph, char *value, Stack *stack);


FILE *open_file(const char *file_name, const char *key);

size_t get_file_size(FILE *file);


size_t read_file(const char *file_name, char **string);

size_t read_file(FILE *file, char **string);


void dump_tree(const char* file_name, tree *graph);

void dump_tree(FILE *file, tree *graph);

void write_tree(FILE *file, node *current_node);

void write_node(FILE *file, node *current_node);


void dump_tree_graphviz(const char* graph_file_name, tree *graph, Stack* characteristics_object = nullptr, char *color = nullptr);

void dump_tree_graphviz(FILE* graphviz_file, tree *graph, Stack* characteristics_object = nullptr, char *color = nullptr);

void write_node_graphviz(FILE *file, node *current_node);


void fill_object_graphviz(const char *graphviz_file_name, Stack *stack, char *color);

void fill_object_graphviz(FILE *file, Stack *stack, char *color);


void get_tree(const char* database_file_name, tree *graph);

void print_nodes(node *my_node);


void create_png(const char *graph_file_name, const char* png_file_name);

void create_png(FILE *graph_file, FILE *png_file);


void print_found(bool found, char *object);