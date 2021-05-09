struct vertex * create_graph(const char str[]);
void add_link(struct vertex * graph, int from, int to);
void add_new_vertex(struct vertex * graph, int grade, int array[]);
void delete_link(struct vertex * graph, int from, int to);
struct vertex * delete_vertex(struct vertex * graph, int num);
int find_all_components(struct vertex * graph, int parameter);
int cycle_exists(struct vertex * graph);
void print_out_graph(struct vertex * graph);
void clean_memory(struct vertex * graph);