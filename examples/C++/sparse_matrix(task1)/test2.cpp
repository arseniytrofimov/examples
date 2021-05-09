#include "matrix.hpp"

int main(){
    SparseMatrix m(5, 10);
    m.set(2, 1, 5);
    m[4][3] = 1;
    *(*(m + 1) + 5) = 5;
    std::cout << m.get(0, 1) << ' ' << m.get(1, 5) << std::endl;
    std::cout << m.num_rows() << ' ' << m.num_cols() << std::endl;
    std::cout << std::endl;
    m.show_matrix();
    return 0;
}