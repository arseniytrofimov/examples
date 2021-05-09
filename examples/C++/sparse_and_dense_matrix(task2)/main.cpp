#include "matrix.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    IterableDenseMatrix m1(20);
    int k, l, v;

    for (int i = 0; i < 1000; ++i){
        k = random() % 20;
        l = random() % 20;
        v = random() % 1000;
        m1.set(k, l, v);
    }
    auto x = m1.iterate_rows(3);
    std::cout << *x << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::for_each(m1.iterate_columns(i), m1.end_column(i),
                      [](Elem & x){std::cout << "| " << x.column << ' ' << x.value << ' ';});
        std::cout << std::endl;
    }



    std::cout << std::endl << "----------------------" << std::endl;
    IterableSparseMatrix m2(20);


    for (int i = 0; i < 30; ++i){
        k = random() % 20;
        l = random() % 20;
        v = random() % 1000;
        m2.set(k, l, v);
    }

    std::cout << "xxxxxx" << std::endl;
    m2.show();
    std::cout << "++++++++++++++++++++++++++++" << std::endl;
    for (int i = 0; i < m2.size(); ++i) {
        std::for_each(m2.iterate_columns(i), m2.end_column(i),
                      [](Elem x){std::cout << x.row << ' ' << x.column << ' ' << x.value << std::endl;});
    }
    std::cout << "++++++++++++++++++++++++++++" << std::endl;
    find_components(m2);
    return 0;
}
