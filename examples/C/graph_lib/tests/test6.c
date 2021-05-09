#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("test6.txt");
    if (my_graph == NULL) return -1;
    printf("Testing how cycle_exists works:");
    print_out_graph(my_graph);
    printf("------------------\n");
    int cycle;
    cycle = cycle_exists(my_graph);
    if (cycle){
        printf("There is at least one cycle");
    }else{
        printf("There are no cycles at all");
    }
    print_out_graph(my_graph);
    clean_memory(my_graph);
    return 0;
}