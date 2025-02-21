#include <iostream>
#include <random>
#include "VecMat.h"

Matrix diagnal(const size_t size, const double value) {
    Matrix rst(size, size);
    for (size_t i = 0; i < size; i++){
        rst(i, i) = value;
    }
    return rst;
}

Matrix Randomize_Matrix_Entries(const Matrix& mat, double start=0., double end=1.) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> unif(start, end);
    Matrix rst(mat.num_rows(), mat.num_cols());
    for (size_t i = 0; i < mat.num_rows(); i++) {
        for (size_t j = 0; j < mat.num_cols(); j++) {
            rst(i, j) = unif(gen);
        }
    }
    return rst;
}