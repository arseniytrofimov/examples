#include <iostream>
#include <vector>

//class of element in matrix
class Elem{
public:

    //value in position
    double value;

    //number of row
    size_t row;

    //number of column
    size_t column;

    //simple constructor, creates elem with 0,0,0
    Elem();

    //constructor that initializes all fields
    Elem(size_t r, size_t c, double val);

    //operator < for comparison
    //though, I didn't use it:)
    bool operator < (const Elem & el) const;

    //operator converts to double
    operator double () const;

    //for *iterator
    double operator *() const;
};

//class for keeping reference to element
class Ref{

    //reference
    Elem & r;
public:

    //constructor
    explicit Ref(Elem& val);

    //converts Ref to Elem
    operator Elem &() const;

    //converts Ref to double
    operator double & () const;

    //returns double value
    double operator *() const;
};

//for simplifying names
using RefV = std::vector<Ref>;
using Cols_Iterator = std::vector<Ref>::const_iterator;
using Rows = std::vector<Elem>;
using Rows_Iterator = Rows::const_iterator;

//interface
class IterableSquareMatrix{
public:
    //iterator to beginning of row
    virtual Rows_Iterator iterate_rows(size_t) = 0;

    //iterator to ending of row
    virtual Rows_Iterator end_row(size_t) = 0;

    //iterator to beginning of column
    virtual Cols_Iterator iterate_columns(size_t) = 0;

    //iterator to ending of column
    virtual Cols_Iterator end_column(size_t) = 0;

    //get value in position
    virtual double get(size_t, size_t) const = 0;

    //set value in position
    virtual void set(size_t, size_t, double) = 0;

    //get the size of matrix
    virtual size_t size() const = 0;

    //destructor
    virtual ~IterableSquareMatrix() = default;
};

//class of dense matrix
class IterableDenseMatrix: public IterableSquareMatrix{

    //Size of matrix
    size_t size_matrix;

    //The matrix, vector of vectors of Elem
    std::vector<Rows> data;

    //Columns, vector of vectors of references to Elem
    std::vector<RefV> columnReferences;

public:

    //Single argument constructor
    explicit IterableDenseMatrix(size_t s);

    //iterator to beginning of row
    Rows_Iterator iterate_rows(size_t row) override;

    //iterator to ending of row
    Rows_Iterator end_row(size_t row) override;

    //iterator to beginning of column
    Cols_Iterator iterate_columns(size_t column) override;

    //iterator to ending of column
    Cols_Iterator end_column(size_t column) override;

    //for testing and simple usage
    std::vector<Elem>& operator [](size_t row);

    //gets value
    double get(size_t x, size_t y) const override;

    //sets value
    void set(size_t x, size_t y, double value) override;

    //size of matrix
    size_t size() const override;

    //destructor
    ~IterableDenseMatrix() override;
};


class IterableSparseMatrix: public IterableSquareMatrix{

    //The matrix, vector of vectors of Elem
    std::vector<Rows> data;

    //Columns, vector of vectors of references to Elem
    std::vector<RefV> columnReferences;

    //size of matrix
    size_t size_matrix;

    //uses for method 'get' to find elem value
    double find_elem(size_t x, size_t y) const;

    //makes new elem if 'set' didn't find existing one
    void add_elem(size_t x, size_t y, double val);

    //clears references before creating new ones
    void clear_references();

    //makes new column references
    void set_references();

public:

    //single argument constructor
    explicit IterableSparseMatrix(int s);

    //size of matrix
    size_t size() const override;

    //iterator to beginning of row
    Rows_Iterator iterate_rows(size_t row) override;

    //iterator to ending of row
    Rows_Iterator end_row(size_t row) override;

    //iterator to beginning of column
    Cols_Iterator iterate_columns(size_t column) override;

    //iterator to ending of column
    Cols_Iterator end_column(size_t column) override;

    //gets value
    double get(size_t x, size_t y) const override;

    //sets value
    void set(size_t x, size_t y, double value) override;

    //for testing: show all elements using get
    void show() const;

    //destructor
    ~IterableSparseMatrix() override;
};

//for the first task: find nodes with highest grade
void find_highest_grade_nodes(IterableSquareMatrix & graph);

//supporting function for find_components
//takes number of node
//and calls same function for its all neighbours
void find_neighbours(IterableSquareMatrix & graph, std::vector<bool> & arr, size_t num);

//function for task 3: find number of components
//considers that graph is not oriented
int find_components(IterableSquareMatrix & graph);