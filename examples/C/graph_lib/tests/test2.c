#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("test2.txt");
    if (my_graph == NULL) return -1;
    printf("Testing how add_link works:");
    print_out_graph(my_graph);
    printf("------------------\n");
    add_link(my_graph, 1, 2);
    add_link(my_graph, 2, 3);
    add_link(my_graph, 3, 4);
    add_link(my_graph, 4, 2);
    add_link(my_graph, 3, 0);
    print_out_graph(my_graph);
    clean_memory(my_graph);
    return 0;
}