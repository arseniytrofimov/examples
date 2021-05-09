#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("test7.txt");
    printf("Testing how empty works:");
    if (my_graph == NULL){
        printf("Graph is empty");
        return -1;
    }
    print_out_graph(my_graph);
    clean_memory(my_graph);
    return 0;
}