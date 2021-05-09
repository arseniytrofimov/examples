#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("test1.txt");
    if (my_graph == NULL) return -1;
    printf("Testing how add_new_vertex works:");
    print_out_graph(my_graph);
    int arr[3] = {2, 1, 4, 0};
    int len;
    len = sizeof(arr) / sizeof(arr[0]);
    printf("------------------\n");
    add_new_vertex(my_graph, len, arr);
    print_out_graph(my_graph);
    clean_memory(my_graph);
    return 0;
}