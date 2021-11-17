#include "akinator.h"

bool find_object(type_value_node value, Stack *stack);

void add_charactist(tree *my_tree, node **current_node, type_value_node characterist, type_value_node object);

void destructer_node(node *selected_note);

void wrong_answer(tree *my_tree, node **current_node);

void get_way(tree *my_tree, type_value_node value);


void constuct_tree(tree *tree)
{
    assert(tree != nullptr);

    type_value_node value = "default";
    
    construct_node(&tree->root_node, value);

    tree->count_nodes = 1;
}


bool construct_node(node **new_node, type_value_node value)
{
    *new_node = (node *)calloc(1, sizeof(node));
    memcpy((*new_node)->value, value, MAX_SIZE_CHARACTER); 

    (*new_node)->left_node      = nullptr;
    (*new_node)->right_node     = nullptr;

    return (bool)*new_node;
}


void add_charactist(tree *my_tree, node **current_node, type_value_node characterist, type_value_node object)
{
    assert(my_tree != nullptr);

    node *old_node = nullptr;

    construct_node(&old_node, (*current_node)->value);    

    old_node->left_node  = (*current_node)->left_node;
    old_node->right_node = (*current_node)->right_node;

    (*current_node)->right_node = old_node;

    memcpy((*current_node)->value, characterist, MAX_SIZE_CHARACTER);

    node *new_node = nullptr;

    construct_node(&new_node, object);

    (*current_node)->left_node = new_node;
}


bool play_mode(const char* save_file_name, tree *my_tree)
{
    assert(my_tree != nullptr);

    node *current_node = my_tree->root_node;

    bool guessed = false;

    while (current_node->left_node != nullptr && current_node->right_node != nullptr)
    {
        char answer[] = "yes";
        
        printf("%s\n", current_node->value);
        printf("write yes/no\n");

        scanf("%s", answer);

        if (strcmp(answer, "yes") == 0)
        {
            current_node = current_node->left_node;
        }

        else if (strcmp(answer, "no") == 0)
        {
            current_node = current_node->right_node;
        }
    }

    printf("Your object is \n %s\n", current_node->value);
    printf("write yes/no \n");

    char answer[MAX_SIZE_CHARACTER + 1] = {};
    
    scanf("%s", answer);
    
    if (strcmp(answer, "yes") == 0)
    {
        guessed = true;
    } 

    else
    {
        guessed = false;
        
        wrong_answer(my_tree, &current_node);
        
        write_tree(save_file_name, my_tree);
        write_tree_graphviz("graph.dot", my_tree);
    }

    return guessed;
}


void wrong_answer(tree *my_tree, node **current_node)
{
    printf("What it was? \n");

    type_value_node object = "";

    scanf(" %[^\n]s ", object);

    printf("What is the different? \n");
    
    type_value_node characterist = {};

    scanf(" %[^\n]s ", characterist);

    add_charactist(my_tree, current_node, characterist, object);
}


void destructer_node(node *selected_node)
{ 
    assert(selected_node != nullptr);

    free(selected_node);
}