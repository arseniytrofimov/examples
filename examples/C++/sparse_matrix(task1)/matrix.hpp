#include <iostream>

struct Triplet{
    Triplet(int x, int y, double val);
    int row;
    int col;
    double value;
    Triplet * next;
    Triplet * prev;
};

class SparseMatrix;

class Row{
private:
    SparseMatrix * matrix;
    int first_value;
    Triplet * list_first;
    Triplet * list_last;
    bool * array_rows;
    bool * array_cols;
    SparseMatrix * result;
public:
    explicit Row(SparseMatrix * m);
    double & operator[](int k);
    double operator[](int k) const;
    double * operator+(int y);
    double const* operator+(int y) const;
    ~Row();
    friend class SparseMatrix;
};

class SparseMatrix{
private:
    int a_;
    int b_;
    Row * rows;
    static void handle_exception_out_of_range(int i, int normal_size);
    static void handle_exception_incorrect_size();
    static void handle_wrong_size_assignment();
    double & get_link (int second_value) const;
    double & find_elem(int x, int y) const;
    double * find(int x, int y) const;
    double & add_elem(int x, int y, double value) const;
    bool tf(SparseMatrix & m1) const;
    void set_zero_rows_cols() const;

public:
    SparseMatrix(int a, int b);
    SparseMatrix(const SparseMatrix & m);
    SparseMatrix & operator=(const SparseMatrix & m);
    Row & operator[](int k);
    const Row & operator[](int k) const;
    void show_matrix() const;
    SparseMatrix & operator*(const SparseMatrix & m) const;
    SparseMatrix & operator+(const SparseMatrix & m) const;
    bool operator==(SparseMatrix & m1) const;
    bool operator!=(SparseMatrix & m1) const;
    Row * operator+(int x);
    Row const* operator+(int x) const;
    double get(int x, int y) const;
    void set(int x, int y, double val);
    int num_rows() const;
    int num_cols() const;
    ~SparseMatrix();
    friend class Row;
};





