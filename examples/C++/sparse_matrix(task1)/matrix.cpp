#include <iostream>
#include "matrix.hpp"

Triplet::Triplet(int x, int y, double val): row(x), col(y),
    value(val), next(nullptr), prev(nullptr){}

Row::Row(SparseMatrix * m): matrix(m), first_value(0),
    list_first(nullptr), list_last(nullptr), result(nullptr),
    array_rows(new bool[m->a_]), array_cols(new bool[m->b_]){}

double & Row::operator[](int k){
    return matrix->get_link(k);
}

double Row::operator[](int k) const{
    std::cout << '%' << std::endl;
    return matrix->get_link(k);
}

double * Row::operator+(int y){
    return &matrix->get_link(y);
}

double const* Row::operator+(int y) const{
    return &matrix->get_link(y);
}

Row::~Row(){
    delete [] array_cols;
    delete [] array_rows;
    while (list_first != list_last){
        list_first = list_first->next;
        delete list_first->prev;
    }
}

void SparseMatrix::handle_exception_out_of_range(int i, int normal_size){
    std::cout << "Segmentation fault! " << i << " >= "
              << normal_size << std::endl;
    exit(1);
}

void SparseMatrix::handle_exception_incorrect_size(){
    std::cout << "It's impossible to multiply such matrixes!" << std::endl;
    exit(2);
}

void SparseMatrix::handle_wrong_size_assignment(){
    std::cout << "Matrixes must have same sizes for assignment!" << std::endl;
    exit(3);
}

double & SparseMatrix::get_link (int second_value) const{
    return find_elem(rows->first_value, second_value);
}

double & SparseMatrix::find_elem(int x, int y) const{
    if (x >= a_){
        handle_exception_out_of_range(x, a_);
    }
    if (y >= b_){
        handle_exception_out_of_range(y, b_);
    }
    Triplet * tmp = rows->list_first;
    while ((tmp != nullptr) &&
           (!((tmp->row == x) && (tmp->col == y))))
        tmp = tmp->next;
    if (tmp == nullptr) return add_elem(x, y, 0);
    return tmp->value;
}

double * SparseMatrix::find(int x, int y) const{
    Triplet * tmp = rows->list_first;
    while ((tmp != nullptr) &&
           (!((tmp->row == x) && (tmp->col == y))))
        tmp = tmp->next;
    if (tmp == nullptr) return nullptr;
    return &tmp->value;
}

double & SparseMatrix::add_elem(int x, int y, double value) const{
    if (rows->list_first == nullptr){
        rows->list_first = new Triplet(x, y, value);
        rows->list_last = rows->list_first;
    }else{
        rows->list_last->next = new Triplet(x, y, value);
        rows->list_last->next->prev = rows->list_last;
        rows->list_last = rows->list_last->next;
    }
    return rows->list_last->value;
}

bool SparseMatrix::tf(SparseMatrix & m1) const{
    if (a_ != m1.a_) return false;
    if (b_ != m1.b_) return false;
    Triplet * tmp = rows->list_first;
    double * p;
    while (tmp != nullptr){
        if (tmp->value == 0){
            tmp = tmp->next;
            continue;
        }
        p = m1.find(tmp->row, tmp->col);
        if (p == nullptr) return false;
        if (tmp->value != *p) return false;
        tmp = tmp->next;
    }
    tmp = m1.rows->list_first;
    while (tmp != nullptr){
        if (tmp->value == 0){
            tmp = tmp->next;
            continue;
        }
        p = find(tmp->row, tmp->col);
        if (p == nullptr) return false;
        if (tmp->value != *p) return false;
        tmp = tmp->next;
    }
    return true;
}

void SparseMatrix::set_zero_rows_cols() const{
    for (int i = 0; i < a_; i++){
        rows->array_rows[i] = true;
    }
    for (int i = 0; i < b_; i++){
        rows->array_cols[i] = true;
    }
    Triplet * tmp = rows->list_first;
    while (tmp != nullptr){
        if (tmp->value != 0){
            rows->array_cols[tmp->col] = false;
            rows->array_rows[tmp->row] = false;
        }
        tmp = tmp->next;
    }
}

SparseMatrix::SparseMatrix(int a, int b): a_(a), b_(b),
    rows(new Row(this)){}

SparseMatrix::SparseMatrix(const SparseMatrix & m): a_(m.a_), b_(m.b_),
    rows(new Row(this)){
    Triplet * tmp = m.rows->list_first;
    while (tmp != nullptr){
        add_elem(tmp->row, tmp->col, tmp->value);
        tmp = tmp->next;
    }
}

SparseMatrix & SparseMatrix::operator=(const SparseMatrix & m){
    if (a_ != m.a_) handle_wrong_size_assignment();
    if (b_ != m.b_) handle_wrong_size_assignment();
    delete rows->result;
    delete rows;
    rows = new Row(this);
    Triplet * tmp = m.rows->list_first;
    while (tmp != nullptr){
        add_elem(tmp->row, tmp->col, tmp->value);
        tmp = tmp->next;
    }
    return *this;
}

Row & SparseMatrix::operator[](int k){
    rows->first_value = k;
    return *rows;
}

const Row & SparseMatrix::operator[](int k) const{
    rows->first_value = k;
    return *rows;
}

void SparseMatrix::show_matrix() const{
    Triplet * tmp = rows->list_first;
    while (tmp != nullptr){
        std::cout << "x = " << tmp->row <<
                  " y = " << tmp->col << " value = " << tmp->value << std::endl;
        tmp = tmp->next;
    }
}

SparseMatrix & SparseMatrix::operator*(const SparseMatrix & m) const{
    delete rows->result;
    if (b_ != m.a_) handle_exception_incorrect_size();
    set_zero_rows_cols();
    m.set_zero_rows_cols();
    rows->result = new SparseMatrix(a_, m.b_);
    double sum;
    double * elem1;
    double * elem2;
    for (int i = 0; i < a_; i++){
        for (int j = 0; j < m.b_; ++j){
            if (rows->array_rows[i] || m.rows->array_cols[j]) continue;
            sum = 0;
            for (int k = 0; k < b_; k++){
                elem1 = find(i, k);
                elem2 = m.find(k, j);
                if ((elem1 != nullptr) && (elem2 != nullptr)){
                    sum += (*elem1) * (*elem2);
                }
            }
            if (sum != 0) rows->result->add_elem(i, j, sum);
        }
    }
    return *(rows->result);
}

SparseMatrix & SparseMatrix::operator+(const SparseMatrix & m) const{
    delete rows->result;
    rows->result = new SparseMatrix(*this);
    Triplet * tmp = m.rows->list_first;
    while (tmp != nullptr){
        rows->result->find_elem(tmp->row, tmp->col) += tmp->value;
        tmp = tmp->next;
    }
    return *(rows->result);
}

bool SparseMatrix::operator==(SparseMatrix & m1) const{
    return tf(m1);
}

bool SparseMatrix::operator!=(SparseMatrix & m1) const{
    return !(tf(m1));
}

Row const* SparseMatrix::operator+(int x) const{
    rows->first_value = x;
    return rows;
}

Row * SparseMatrix::operator+(int x){
    rows->first_value = x;
    return rows;
}

double SparseMatrix::get(int x, int y) const{
    if (x >= a_){
        handle_exception_out_of_range(x, a_);
    }
    if (y >= b_){
        handle_exception_out_of_range(y, b_);
    }
    Triplet * tmp = rows->list_first;
    while ((tmp != nullptr) &&
           (!((tmp->row == x) && (tmp->col == y))))
        tmp = tmp->next;
    if (tmp == nullptr) return 0;
    return tmp->value;
}

void SparseMatrix::set(int x, int y, double val){
    if (x >= a_){
        handle_exception_out_of_range(x, a_);
    }
    if (y >= b_){
        handle_exception_out_of_range(y, b_);
    }
    double & p = find_elem(x, y);
    p = val;
}

int SparseMatrix::num_rows() const{
    return a_;
}

int SparseMatrix::num_cols() const{
    return b_;
}

SparseMatrix::~SparseMatrix(){
    delete rows->result;
    delete rows;
}

