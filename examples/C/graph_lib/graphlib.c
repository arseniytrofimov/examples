#include <stdio.h>
#include <stdlib.h>
#include "graphlib.h"

struct neighbours{
    int n;
    struct neighbours * next;
};

struct vertex{
    int flag;
    int n;
    struct vertex * next;
    struct neighbours * links;
};

struct vertex * create_graph(const char str[]){
    /**

     function of creating a graph
     using the name of file with
     a number "N" of vertexes in the first line
     and N lines with N times "1"/"0" that mean if
     there is a link between numbers of vertexes
     in line and column or not

     vertexes are enumerated from 0 to N-1

     matrix in the file must be symmetrical

    **/
    FILE * file;
    struct vertex *p, *first, *last;
    struct neighbours *q, *last_v;
    int n;
    char str_num[10];
    char c;

    if ((file = fopen(str, "r"))==NULL) return NULL;

    fgets(str_num, 10, file);
    n = atoi(str_num);

    for (int i = 0; i < n; i++){

        p = malloc(sizeof(struct vertex));
        p->flag = 0;
        p->n = i;
        p->links = NULL;
        p->next = NULL;

        if (i == 0) first = p;
        if (i != 0) last->next = p;
        last = p;
        last_v = NULL;

        for (int j = 0; j <= n; j++){
            c = (char)fgetc(file);

            if (c == '1'){
                q = malloc(sizeof(struct neighbours));
                q->n = j;
                q->next = NULL;
                if (p->links == NULL){
                    p->links = q;
                }else{
                    last_v->next = q;
                }
                last_v = q;
            }
        }

    }
    fclose(file);

    return first;
}

struct vertex * find_vertex(int num, struct vertex * graph){
    /**
     this function returns the pointer to
     the vertex with number "num"
     if there is no such vertex, returns NULL
     it's a supportive function
    **/
    struct vertex * p;
    p = graph;
    while (p != NULL){
        if (p->n == num) return p;
        p = p->next;
    }
    return NULL;
}

int link_exists(struct vertex * graph, int from, int to){
    /**
     1 if successfully, or 0
    **/
    struct vertex *p;
    struct neighbours *q;
    p = find_vertex(to, graph);
    if (p == NULL) return 0;
    p = find_vertex(from, graph);
    if (p == NULL) return 0;
    if (from == to) return 0;
    q = p->links;
    while (q != NULL){
        if (q->n == to) return 1;
        q = q->next;
    }
    return 0;
}

void sort_neighbours(struct vertex * vert){
    /**
     it's supporting function for creating new edge
    **/
    struct neighbours *tmp, *tmp1, *tmp2;
    tmp = vert->links;
    if (tmp->next == NULL) return;
    tmp1 = tmp->next;
    if (tmp->n > tmp1->n){
        vert->links = tmp1;
        tmp1 = tmp1->next;
        vert->links->next = tmp;
        tmp->next = tmp1;
    }
    tmp = vert->links;
    tmp1 = tmp->next;
    tmp2 = tmp1->next;
    while ((tmp2 != NULL) && (tmp2->n < tmp1->n)){
        tmp->next = tmp2;
        tmp1->next = tmp2->next;
        tmp2->next= tmp1;
        tmp = tmp->next;
        tmp1 = tmp->next;
        tmp2 = tmp1->next;
    }
}

void add_link(struct vertex * graph, int from, int to){
    /**
     this function creates an edge between two vertexes
     with numbers "from" and "to"
    **/
    struct vertex *p, *p1;
    struct neighbours *q, *q1, *q2;
    if (link_exists(graph, from, to)) return;
    p = find_vertex(from, graph);
    p1 = find_vertex(to, graph);
    q = malloc(sizeof(struct neighbours));
    q1 = p->links;
    if (q1 == NULL){
        q->n = to;
        q->next = NULL;
        p->links = q;
    }else{
        q->n = to;
        q->next = p->links;
        p->links = q;
    }
    q2 = malloc(sizeof(struct neighbours));
    q1 = p1->links;
    if (q1 == NULL){
        q2->n = from;
        q2->next = NULL;
        p1->links = q2;
    }else{
        q2->n = from;
        q2->next = p1->links;
        p1->links = q2;
    }
    sort_neighbours(p);
    sort_neighbours(p1);
}

void add_new_vertex(struct vertex * graph, int grade, int array[]){
    /**
        this function adds a new vertex to the graph

        parameter "array" is an array of integer numbers
        of neighbours of the new vertex

        parameter "grade" is the quantity of numbers in "array"
    **/

    struct vertex *tmp, *p;
    tmp = graph;
    if (tmp != NULL)
        while (tmp->next != NULL)
            tmp = tmp->next;
    p = malloc(sizeof(struct vertex));
    p->next = NULL;
    p->links = NULL;
    if (tmp == NULL) p->n = 0;
    else p->n = tmp->n + 1;

    if (tmp == NULL) graph = p;
    else tmp->next = p;



    for (int i = 0; i < grade; i++){
        add_link(graph, array[i], p->n);
    }
}

void delete_link(struct vertex * graph, int from, int to){
    /**
     this function deletes edge between two vertexes,
     number "from" and "to"
    **/
    struct vertex *p;
    struct neighbours *q, *q1;
    p = find_vertex(from, graph);
    if (!(link_exists(graph, from, to))) return;
    q = p->links;
    if (q->n == to){
        p->links = q->next;
        free(q);
    }else{
        while (q->next->n != to) q = q->next;
        q1 = q->next;
        q->next = q1->next;
        free(q1);
    }
    p = find_vertex(to, graph);
    if (!(link_exists(graph, to, from))) return;
    q = p->links;
    if (q->n == from){
        p->links = q->next;
        free(q);
    }else{
        while (q->next->n != from) q = q->next;
        q1 = q->next;
        q->next = q1->next;
        free(q1);
    }
}

struct vertex * delete_vertex(struct vertex * graph, int num){
    /**
     this funcion deletes vertex number "num" and all it's edges
    **/
    struct vertex *p, *p1;
    if (num == 0){
        p = graph;
        while (p->links != NULL) delete_link(graph, 0, p->links->n);
        p1 = graph->next;
        free(p);
        return p1;
    }else{
        p = find_vertex(num, graph);
        if (p == NULL) return graph;
        p1 = find_vertex(num - 1, graph);
        while (p->links != NULL) delete_link(graph, num, p->links->n);
        p1->next = p->next;
        free(p);
        return graph;
    }
}

int every_is_in_any_component(struct vertex * graph){
    /**
     it's supporting function for finding components
    **/
    struct vertex *p;
    p = graph;
    while (p != NULL){
        if (p->flag == 0) return 0;
        p = p->next;
    }
    return 1;
}

void make_component(struct vertex * graph, int num, int counter){
    /**
     it's supporting function for finding components
    **/
    struct vertex * p;
    struct neighbours * q;
    p = find_vertex(num, graph);
    if (p->flag == counter) return;
    if (p->flag == 0) p->flag = counter;
    q = p->links;
    while (q != NULL){
        make_component(graph, q->n, counter);
        q = q->next;
    }
}

int find_all_components(struct vertex * graph, int parameter){
    /**
     this function counts components and returns
     number of them
     if you want to print out components, set "parameter" = "1"
     else set "0"
    **/
    int counter = 1;
    struct vertex *p;
    if (graph == NULL) return 0;
    while (!(every_is_in_any_component(graph))){
        p = graph;
        while (p->flag != 0) p = p->next;
        make_component(graph, p->n, counter);
        ++counter;
    }
    if (parameter == 1){
        printf("Components:\n");
        for (int i = 1; i < counter; i++) {
            p = graph;
            printf("%d:{ ", i);
            while (p != NULL) {
                if (p->flag == i) printf("%d ", p->n);
                p = p->next;
            }
            printf("}\n");
        }
    }
    p = graph;
    while (p != NULL){
        p->flag = 0;
        p = p->next;
    }
    return counter - 1 ;
}

int cycle_exists(struct vertex * graph){
    /**
     this function returns 1 if there is at least
     one cycle in graph, instead, returns 0
    **/
    int components, vertexes, edges;
    struct vertex *p;
    struct neighbours *q;
    components = find_all_components(graph, 0);
    edges = 0;
    vertexes = 0;
    p = graph;
    while (p != NULL){
        vertexes++;
        q = p->links;
        while (q != NULL){
            edges++;
            q = q->next;
        }
        p = p->next;
    }
    edges /= 2;
    if (vertexes - edges == components) return 0;
    return 1;
}

void print_out_graph(struct vertex * graph){
    /**
     this function can print your graph in
     format of
     0 : 1 2 3
     ...
     where "0" is the number of vertex
     and "1", "2", "3" are the numbers of
     it's neighbours
    **/
    struct vertex * curr = graph;
    struct neighbours * curr_v;

    while (curr != NULL){
        curr_v = curr->links;
        printf("%d : ", curr->n);
        if (curr_v == NULL) printf("isolated!");
        while (curr_v != NULL){
            printf("%d ", curr_v->n);
            curr_v = curr_v->next;
        }
        printf("\n");
        curr = curr->next;
    }
}

void clean_memory(struct vertex * graph){
    /**
     this function cleans all the memory,
     allocated for keeping graph
    **/
    struct vertex * tmp;
    struct neighbours *q, *q1;
    while (graph != NULL){
        q = graph->links;
        while (q != NULL){
            q1 = q->next;
            free(q);
            q = q1;
        }
        tmp = graph->next;
        free(graph);
        graph = tmp;
    }
}