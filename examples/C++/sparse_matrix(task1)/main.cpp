#include "matrix.hpp"

int main(){
    SparseMatrix m(5, 10);
    m.set(2, 1, 5);
    m[4][3] = 1;
    SparseMatrix m2 = m;
    *(*(m2+0)+0) = 5;
    m2.set(4, 9, 100);
    m2[1][9] = 20;
    SparseMatrix m1 = m + m2;
    SparseMatrix m3(10, 10);
    m3[1][2] = 10;
    m3.set(2, 3, 15);
    m3[3][4] = 5;
    *(*(m3+9)+0) = 30;
    SparseMatrix m4 = m1 * m3;
    m3.show_matrix();
    std::cout << std::endl;
    m4.show_matrix();
    std::cout << std::endl;
    m1.show_matrix();
    return 0;
}