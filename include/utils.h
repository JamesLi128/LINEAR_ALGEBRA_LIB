#include <iostream>
#include "VecMat.h"

Matrix diagnal(const size_t size, const double value) {
    Matrix rst(size, size);
    for (size_t i = 0; i < size; i++){
        rst(i, i) = value;
    }
    return rst;
}