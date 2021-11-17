#include <stdio.h>

const int MAX_SIZE_CHARACTER = 20;
typedef char type_value_node[MAX_SIZE_CHARACTER];

struct node
{
    type_value_node value;

    node *parent_node; 
    node *left_node;
    node *right_node;
};

struct tree
{
    size_t count_nodes;
    node *root_node;
};