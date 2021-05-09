#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("test3.txt");
    if (my_graph == NULL) return -1;
    printf("Testing how delete_link works:");
    print_out_graph(my_graph);
    printf("------------------\n");
    delete_link(my_graph, 0, 1);
    delete_link(my_graph, 0, 2);
    delete_link(my_graph, 3, 4);
    delete_link(my_graph, 1, 2);
    print_out_graph(my_graph);
    clean_memory(my_graph);
    return 0;
}