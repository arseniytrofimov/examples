#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("test4.txt");
    if (my_graph == NULL) return -1;
    printf("Testing how delete_vertex works:");
    print_out_graph(my_graph);
    printf("------------------\n");
    delete_vertex(my_graph, 0);
    delete_vertex(my_graph, 2);
    print_out_graph(my_graph);
    clean_memory(my_graph);
    return 0;
}