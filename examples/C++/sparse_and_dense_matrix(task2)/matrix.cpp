#include "matrix.hpp"

//simple constructor, creates elem with 0,0,0
Elem::Elem(): row(0), column(0), value(0){};

//constructor that initializes all fields
Elem::Elem(size_t r, size_t c, double val): row(r), column(c), value(val){}

//operator < for comparison
//though, I didn't use it:)
bool Elem::operator < (const Elem & el) const{
    if (row == el.row) return (column < el.column);
    else return (row < el.row);
}

//operator converts to double
Elem::operator double() const{
    return value;
}

//for *iterator
double Elem::operator *() const{
    return value;
}

//constructor
Ref::Ref(Elem& val): r(val){}

//converts Ref to Elem
Ref::operator Elem &() const{
    return r;
}

//converts Ref to double
Ref::operator double & () const{
    return r.value;
}

//returns double value
double Ref::operator *() const{
    return r.value;
}

//Single argument constructor
IterableDenseMatrix::IterableDenseMatrix(size_t s): size_matrix(s),
        data(s, std::vector<Elem>(s)), columnReferences(s){
    for (size_t col = 0; col < s; col++)
        for (size_t row = 0; row < s; row++){
            //sets all values from 0,0,0 to row,col,0
            data[row][col] = Elem(row, col, 0);
            //sets references in columns for all elements
            columnReferences[col].emplace_back(Ref(data[row][col]));
        }
}

//iterator to beginning of row
Rows_Iterator IterableDenseMatrix::iterate_rows(size_t row){
    return data[row].begin();
}

//iterator to ending of row
Rows_Iterator IterableDenseMatrix::end_row(size_t row){
    return data[row].end();
}

//iterator to beginning of column
Cols_Iterator IterableDenseMatrix::iterate_columns(size_t column){
    return columnReferences[column].begin();
}

//iterator to ending of column
Cols_Iterator IterableDenseMatrix::end_column(size_t column){
    return columnReferences[column].end();
}

//for testing and simple usage
std::vector<Elem>& IterableDenseMatrix::operator [](size_t row){
    return data[row];
}

//gets value
double IterableDenseMatrix::get(size_t x, size_t y) const{
    return data[x][y].value;
}

//sets value
void IterableDenseMatrix::set(size_t x, size_t y, double value){
    data[x][y].value = value;
}

//size of matrix
size_t IterableDenseMatrix::size() const{
    return size_matrix;
}

//destructor
IterableDenseMatrix::~IterableDenseMatrix(){
    for (size_t i = 0; i < size_matrix; i++){
        data[i].clear();
        columnReferences[i].clear();
    }
    data.clear();
    columnReferences.clear();
}

//uses for method 'get' to find elem value
double IterableSparseMatrix::find_elem(size_t x, size_t y) const{
    for (auto & it : data[x]){
        if (it.column == y) return it.value;
    }
    return 0;
}

//makes new elem if 'set' didn't find existing one
void IterableSparseMatrix::add_elem(size_t x, size_t y, double val){
    for (auto it = data[x].begin(); it != data[x].end(); it++){
        //find place to emplace in
        if (it->column > y){
            data[x].emplace(it, Elem(x, y, val));
            return;
        }
    }
    //if didn't find bigger column elem
    data[x].emplace_back(Elem(x, y, val));
}

//clears references before creating new ones
void IterableSparseMatrix::clear_references(){
    for (size_t i = 0; i < size_matrix; ++i) {
        columnReferences[i].clear();
    }
}

//makes new column references
void IterableSparseMatrix::set_references(){
    clear_references();
    for (size_t i = 0; i < size_matrix; ++i) {
        for (auto it = data[i].begin(); it != data[i].end(); it++){
            columnReferences[(*it).column].emplace_back(Ref(*it));
        }
    }
}

//single argument constructor
IterableSparseMatrix::IterableSparseMatrix(int s): size_matrix(s),
    data(s, std::vector<Elem>()), columnReferences(s){}

//size of matrix
size_t IterableSparseMatrix::size() const{
    return size_matrix;
}

//iterator to beginning of row
Rows_Iterator IterableSparseMatrix::iterate_rows(size_t row){
    return data[row].begin();
}

//iterator to ending of row
Rows_Iterator IterableSparseMatrix::end_row(size_t row){
    return data[row].end();
}

//iterator to beginning of column
Cols_Iterator IterableSparseMatrix::iterate_columns(size_t column){
    set_references();
    return columnReferences[column].begin();
}

//iterator to ending of column
Cols_Iterator IterableSparseMatrix::end_column(size_t column){
    return columnReferences[column].end();
}

//gets value
double IterableSparseMatrix::get(size_t x, size_t y) const{
    return find_elem(x, y);
}

//sets value
void IterableSparseMatrix::set(size_t x, size_t y, double value){
    for (auto it = data[x].begin(); it != data[x].end(); it++){
        if (it->column == y){
            it->value = value;
            return;
        }
    }
    //if didn't find existing elem
    add_elem(x, y, value);
}

//for testing: show all elements using get
void IterableSparseMatrix::show() const{
    for (size_t i = 0; i < size_matrix; ++i) {
        for (size_t j = 0; j < size_matrix; ++j) {
            if (get(i, j) != 0) std::cout << i << ' ' << j << ' ' << get(i, j) << std::endl;
        }
    }

}

//destructor
IterableSparseMatrix::~IterableSparseMatrix(){
    for (size_t i = 0; i < size_matrix; ++i){
        data[i].clear();
        columnReferences[i].clear();
    }
    data.clear();
    columnReferences.clear();
}

//for the first task: find nodes with highest grade
void find_highest_grade_nodes(IterableSquareMatrix & graph){

    //creating of vector to put there the grades
    std::vector<int> grades(graph.size());

    //for simple usage
    size_t size = graph.size();

    //searching for neighbours
    for (size_t i = 0; i < size; ++i){

        //searching neighbours in rows
        for (auto it = graph.iterate_rows(i); it != graph.end_row(i); ++it){
            if ((*it) != 0) grades[i]++;
        }

        //searching neighbours in columns
        for (auto it = graph.iterate_columns(i); it != graph.end_column(i); ++it){
            if ((*it) != 0) grades[i]++;
        }
    }

    //writing out all grades
    std::cout << "Grades: " << std::endl;
    for (size_t i = 0; i < size; ++i){
        std::cout << i << " | " << grades[i] << std::endl;
    }

    int highest_value = 0;
    //find highest in vector
    for (size_t i = 0; i < size; ++i) {
        if (grades[i] > highest_value) highest_value = grades[i];
    }

    //writing out highest ones
    std::cout << "Highest grade is/are:";
    for (size_t i = 0; i < size; ++i) {
        if (grades[i] == highest_value)
            std::cout << ' ' << i;
    }
    std::cout << std::endl;
}

//supporting function for find_components
//takes number of node
//and calls same function for its all neighbours
void find_neighbours(IterableSquareMatrix & graph, std::vector<bool> & arr, size_t num){

    //if this node is already checked
    if (arr[num]) return;

    //set node as checked
    arr[num] = true;

    //call this function for all its neighbours (not 0 edges)
    for (auto it = graph.iterate_rows(num); it != graph.end_row(num); ++it){
        if (it->value != 0)
            find_neighbours(graph, arr, it->column);
    }
}

//function for task 3: find number of components
//considers that graph is not oriented
int find_components(IterableSquareMatrix & graph){

    //for simple usage
    size_t size = graph.size();

    //vector of bool to set nodes as checked
    std::vector<bool> tf(size);

    //set all to false
    for (int i = 0; i < size; ++i) {
        tf[i] = false;
    }
    int i = 0;
    int number_of_components = 0;

    //starts with 0 node, calls find_neighbours for it
    while (i != size){

        //call find_neighbours for not checked nodes
        if (!tf[i]){
            number_of_components++;
            find_neighbours(graph, tf, i);
        }
        i++;
    }
    std::cout << std::endl;
    std::cout << number_of_components << std::endl;
    return number_of_components;
}