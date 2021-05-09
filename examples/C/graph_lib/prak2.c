#include "graphlib.h"
#include <stdio.h>

int main(void){
    struct vertex * my_graph;
    my_graph = create_graph("my.txt");
    if (my_graph == NULL) return -1;
    printf("It's an example of using graph library:\n");
    print_out_graph(my_graph);
    int arr[3] = {2, 1, 0};
    int len, comp, cycle;
    len = sizeof(arr) / sizeof(arr[0]);
    printf("------------------\n");
    add_new_vertex(my_graph, len, arr);
    print_out_graph(my_graph);
    add_link(my_graph, 0, 1);
    add_link(my_graph, 1, 2);
    add_link(my_graph, 3, 4);
    printf("------------------\n");
    print_out_graph(my_graph);
    delete_vertex(my_graph, 5);
    delete_link(my_graph, 1, 2);
    printf("------------------\n");
    print_out_graph(my_graph);
    comp = find_all_components(my_graph, 1);
    printf("There is(are) %d component(s)\n", comp);
    cycle = cycle_exists(my_graph);
    if (cycle == 1) printf("There is at least one cycle");
    else printf("There are no cycles");
    clean_memory(my_graph);
    return 0;
}