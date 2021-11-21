#include "akinator.h"

const char *default_database_file_name   = "database_files/tree.database";
const char *default_graph_file_name      = "database_files/graph.dot";
const char *default_png_file_name        = "database_files/graph.png";

bool compare_characteristcs(Stack *charactistics_object1, Stack *charactistics_object2);

void compare_objects(char *object1, char *object2, const char *database_file_name, const char* graph_file_name, const char *png_file_name);

bool compare_characteristcs(Stack *charactistics_object1, Stack *charactistics_object2, Stack *union_characteristic);

#define GET_STACK_CHARACTERISTICS(num)                                                                                              \
                                                                                                                                    \
    Stack characteristics_object##num = {};                                                                                         \
                                                                                                                                    \
    stack_constructor(&characteristics_object##num);                                                                                \
                                                                                                                                    \
    bool object_found##num = false;                                                                                                 \
                                                                                                                                    \
    object_found##num = try_get_characteristics(database_file_name, &graph, &characteristics_object##num, object##num);             \
                                                                                                                                    \

void compare_objects(char *object1, char *object2, const char *database_file_name, const char* graph_file_name, const char *png_file_name)
{
    assert(object1            != nullptr);
    assert(object2            != nullptr);
    assert(database_file_name != nullptr);
    assert(graph_file_name    != nullptr);
    assert(png_file_name      != nullptr);

    tree graph = {};                                                                                                               
                                                                                                                                    
    construct_tree(&graph);  

    GET_STACK_CHARACTERISTICS(1)
    
    print_found(object_found1, object1);                                                                                            

    GET_STACK_CHARACTERISTICS(2)

    print_found(object_found2, object2);                                                                                            

    bool compared = false;
     
    Stack characteristics_union = {};
    
    stack_constructor(&characteristics_union);

    compared = compare_characteristcs(&characteristics_object1, &characteristics_object2, &characteristics_union);
    
    if (compared)
    {
        printf("Characteristics were comepred");
    }   

    else
    {
        printf("Characteristics1 were not comepred");
    }

    dump_tree_graphviz(graph_file_name, &graph);

    char color_object1[] = "yellow";
    
    dump_tree_graphviz(graph_file_name, &graph, &characteristics_object1, color_object1);
    
    char color_object2[] = "red";

    fill_object_graphviz(graph_file_name, &characteristics_object2, color_object2);

    char color_union[] = "green";

    fill_object_graphviz(graph_file_name, &characteristics_union, color_union);

    create_png(graph_file_name, png_file_name);

    destruct_tree(&graph);

}

bool compare_characteristcs(Stack *charactistics_object1, Stack *charactistics_object2, Stack *union_characteristics)
{
    assert(charactistics_object1 != nullptr);
    assert(charactistics_object2 != nullptr);
    assert(union_characteristics != nullptr);

    if (charactistics_object1->size == 0 || charactistics_object2->size == 0)
    {
        return false;
    }

    for (size_t i = 0; i < charactistics_object1->size; ++i)
    {
        node *union_characteristic = *(stack_type *)(charactistics_object1->data + sizeof(charactistics_object1->stack_canary) + sizeof(stack_type) * (charactistics_object1->size - i - 1));
        
        char *charactist_object1 = union_characteristic->value;
        
        for (size_t j = 0; j < charactistics_object2->size; ++j)
        {
            char *charactist_object2 = ((*(stack_type *)(charactistics_object2->data + sizeof(charactistics_object2->stack_canary) + sizeof(stack_type) * (charactistics_object2->size - j - 1)))->value);

            if (strcmp(charactist_object1, charactist_object2) == 0)
            {
                push_stack(union_characteristics, &union_characteristic);
                
                break;
            }
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    type_value_node object1 = "";
    type_value_node object2 = "";


    const char *database_file_name = default_database_file_name;
    const char *graph_file_name    = default_graph_file_name;
    const char *png_file_name      = default_png_file_name;
    
    if (argc >= 2)
    {
        memcpy(object1, argv[1], MAX_SIZE_CHARACTER);
    }

    if (argc >= 3)
    {
        memcpy(object2, argv[2], MAX_SIZE_CHARACTER);
    }

    if (argc >= 4)
    {
        database_file_name = argv[3];
    }

    if (argc >= 5)
    {
        graph_file_name = argv[4];
    }

    if (argc >= 6)
    {
        png_file_name = argv[5];
    }

    compare_objects(object1, object2, database_file_name, graph_file_name, png_file_name);
}
