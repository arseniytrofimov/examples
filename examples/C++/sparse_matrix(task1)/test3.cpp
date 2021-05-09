#include "matrix.hpp"

int main(){
    SparseMatrix m(5, 10);
    m.set(2, 1, 5);
    m[4][3] = 1;
    *(*(m + 1) + 5) = 5;
    m.set(4, 1, 0.1123);
    m.show_matrix();
    std::cout << "------" << std::endl;
    const SparseMatrix m2 = m;
    m[1][1] = 7.13;
    double q = *(*(m2 + 1) + 5);
    const SparseMatrix m3 = m2 + m;
    std::cout << q << std::endl;
    m3.show_matrix();
    return 0;
}