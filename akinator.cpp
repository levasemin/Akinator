#include "akinator.h"

bool find_object(char *value, Stack *stack);

void add_charactist(tree *graph, node **current_node, char *characterist, char *object);

bool construct_node(node **new_node, char *value);

void destruct_node(node *selected_note);

void wrong_answer(tree *graph, node **current_node);

void get_way(tree *graph, char *value);


void construct_tree(tree *tree)
{
    assert(tree != nullptr);
    
    construct_node(&tree->root_node, DEFAULT_VALUE);

    tree->count_nodes = 1;
}


bool construct_node(node **new_node, char *value)
{
    assert(new_node != nullptr);
    assert(value    != nullptr);

    *new_node = (node *)calloc(1, sizeof(node));
    
    assert(*new_node != nullptr);

    memcpy((*new_node)->value, value, MAX_SIZE_CHARACTER); 

    (*new_node)->left_node      = nullptr;
    (*new_node)->right_node     = nullptr;

    return (bool)*new_node;
}


void add_charactist(tree *graph, node **current_node, char *characterist, char *object)
{
    assert(graph      != nullptr);
    assert(current_node != nullptr);
    assert(characterist != nullptr);
    assert(object       != nullptr);

    node *old_node = nullptr;

    construct_node(&old_node, (*current_node)->value);    

    old_node->left_node  = (*current_node)->left_node;
    old_node->right_node = (*current_node)->right_node;

    (*current_node)->right_node = old_node;

    memcpy((*current_node)->value, characterist, MAX_SIZE_CHARACTER);

    node *new_node = nullptr;

    construct_node(&new_node, object);

    (*current_node)->left_node = new_node;
    
    graph -> count_nodes += 1;
}


bool play_mode(tree *graph)
{
    assert(graph != nullptr);

    node *current_node = graph->root_node;

    bool guessed = false;

    while (current_node->left_node != nullptr && current_node->right_node != nullptr)
    {
        char answer[20] = "yes";
        
        printf("%s\n", current_node->value);
        printf("write yes/no\n");

        scanf("%20s", answer);

        if (strcmp(answer, "yes") == 0)
        {
            current_node = current_node->left_node;
        }

        else if (strcmp(answer, "no") == 0)
        {
            current_node = current_node->right_node;
        }
    }

    printf("Your object is \n%s\n", current_node->value);
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
        
        wrong_answer(graph, &current_node);
    }

    return guessed;
}


void wrong_answer(tree *graph, node **current_node)
{
    printf("What it was? \n");

    type_value_node object = "";

    scanf(" %[^\n]s ", object);

    printf("What is the different? \n");
    
    type_value_node characterist = {};

    scanf(" %[^\n]s ", characterist);

    add_charactist(graph, current_node, characterist, object);
}

void destruct_tree(tree *graph)
{
    assert(graph != nullptr);

    Stack stack = {};

    stack_constructor(&stack);

    push_stack(&stack, &graph->root_node);

    while (stack.size != 0)
    {
        node *current_node = pop_stack(&stack);
        
        if (current_node->right_node != nullptr)  
        {
            push_stack(&stack, &(current_node->right_node));
        }
        
        if (current_node->left_node != nullptr)
        {
            push_stack(&stack, &(current_node->left_node));
        }
        
        destruct_node(current_node);

    }

}

void destruct_node(node *selected_node)
{ 
    assert(selected_node != nullptr);

    free(selected_node);
}