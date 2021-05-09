#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("test5.txt");
    if (my_graph == NULL) return -1;
    printf("Testing how find_all_components works:");
    print_out_graph(my_graph);
    printf("------------------\n");
    int comp;
    comp = find_all_components(my_graph, 1);
    printf("There are %d components", comp);
    print_out_graph(my_graph);
    clean_memory(my_graph);
    return 0;
}