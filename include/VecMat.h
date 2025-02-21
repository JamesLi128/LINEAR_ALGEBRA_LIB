#ifndef VECMAT_H
#define VECMAT_H

#include <iostream>
#include <vector>
#include <cmath>


class Matrix;


class Vector {
private:
    std::vector<double> vec;

public:

    // initialize with fixed value
    Vector(const size_t& size, const double& init_value=0){
        vec.assign(size, init_value);
    }

    // initialize with a double arr
    Vector(const double* init_arr) {
        int size = sizeof(init_arr);
        for (int i=0 ; i < size; i++){
            vec[i] = init_arr[i];
        }
    }

    // initialize with another vector instance
    Vector(const Vector& another_vector){
        for (size_t i=0 ; i < another_vector.size(); i++){
            vec.push_back(another_vector[i]);
        }
    }

    size_t size() const {
        return vec.size();
    }

    size_t size() {
        return vec.size();
    }

    double dot(const Vector& other_vector) const {
        if (vec.size() != other_vector.size()){
            throw std::invalid_argument("Dot product dimension doesn't match.");
        }
        double rst = 0;
        for (size_t i=0; i<vec.size(); i++){
            rst += vec[i] * other_vector[i];
        }
        return rst;
    }

    Vector dot(const Matrix& mat);

    double norm() const{
        return sqrt(this->dot(*this));
    }

    Vector& operator= (const Vector& another_vec) {
        if (this == &another_vec){
            return *this;
        }
        vec.clear();
        for (auto num : another_vec) {
            vec.push_back(num);
        }
        return *this;
    }

    auto operator[] (size_t idx) -> double& {
        if (idx >= size()) {
            throw std::out_of_range("Index out of range.");
        }
        return vec[idx];
    }

    auto operator[] (size_t idx) const -> const double& {
        if (idx >= size()) {
            throw std::out_of_range("Index out of range.");
        }
        return vec[idx];
    }

    auto begin() -> std::vector<double>::iterator {
        return vec.begin();
    }

    auto begin() const -> std::vector<double>::const_iterator {
        return vec.begin();
    }

    auto end() -> std::vector<double>::iterator {
        return vec.end();
    }

    auto end() const -> std::vector<double>::const_iterator {
        return vec.end();
    }

    // overload operator +
    Vector operator + (const Vector& another_vector) const {
        if (vec.size() != another_vector.size()) {
            throw std::invalid_argument("Array sizes must match. ");
        }
        Vector rst(*this);
        for (size_t i=0; i<vec.size(); i++) {
            rst[i] += another_vector[i];
        }
        return rst;
    }

    template <typename Scalar>
    Vector operator + (const Scalar& value) const {
        if (vec.size() == 0) {
            throw std::invalid_argument("Can't add scalar to empty vector.");
        }
        double double_scalar = static_cast<double>(value);
        Vector rst(vec);
        for (int i=0; i<vec.size(); i++){
            rst[i] += double_scalar;
        }
        return rst;
    }

    // overload operator -
    Vector operator - (const Vector& another_vector) const {
        if (vec.size() != another_vector.size()) {
            throw std::invalid_argument("Array sizes must match. ");
        }
        Vector rst(*this);
        for (size_t i=0; i<vec.size(); i++) {
            rst[i] -= another_vector[i];
        }
        return rst;
    }

    template <typename Scalar>
    Vector operator - (const Scalar& value) const {
        if (vec.size() == 0) {
            throw std::invalid_argument("Can't subtract scalar to empty vector.");
        }
        double double_scalar = static_cast<double>(value);
        Vector rst(vec);
        for (size_t i=0; i<vec.size(); i++){
            rst[i] -= double_scalar;
        }
        return rst;
    }

    bool operator== (const Vector& another_vec) const {
        if (size() != another_vec.size()) {
            return false;
        }
        for (size_t i = 0; i < size(); i++) {
            if (vec[i] != another_vec[i]) {
                return false;
            }
        }
        return true;
    }

    void display() const {
        printf("[");
        for (size_t i = 0; i < vec.size(); i++) {
            printf("%.2lf ", vec[i]);
        }
        printf("]\n");
    }

};


class Matrix {
private:
    std::vector<Vector> mat;
    size_t n_rows, n_cols;
    void check_dimension(const Matrix& another_mat) const{
        if (n_rows != another_mat.n_rows) {
            throw std::invalid_argument("Number of Rows doesn't match.");
        }
        else if (n_cols != another_mat.n_cols) {
            throw std::invalid_argument("Number of Cols doesn't match.");
        }
    }

public: 
    Matrix() : n_rows(0), n_cols(0) {};

    Matrix(const size_t nrows, const size_t ncols, const double init_value = 0) {
        if (nrows == 1 or ncols == 1){
            throw std::invalid_argument("Matrix can't be 1 dimensional, both nrows and ncols must > 1.");
        }
        n_rows = nrows;
        n_cols = ncols;
        for (size_t i = 0; i < n_rows; i++) {
            Vector new_row(n_cols, init_value);
            mat.push_back(new_row);
        }
    }

    Matrix(const Matrix& another_mat) {
        n_rows = another_mat.num_rows();
        n_cols = another_mat.num_cols();
        for (auto row_vec : another_mat.mat) {
            Vector new_row_vec(row_vec);    // ensures deep copy
            mat.push_back(new_row_vec);
        }
    }

    Matrix& operator=(const Matrix& another_mat) {
        if (this == &another_mat) {
            return *this; // handle self-assignment
        }
        n_rows = another_mat.num_rows();
        n_cols = another_mat.num_cols();
        mat.clear();
        for (auto row : another_mat) {
            Vector new_row(row);
            mat.push_back(new_row);
        }
        return *this;
    }

    size_t num_cols() const{
        return n_cols;
    }

    size_t num_rows() const{
        return n_rows;
    }

    Matrix transpose() const {
        Matrix rst(n_cols, n_rows);
        for (size_t i = 0; i < n_cols; i++) {
            for (size_t j = 0; j < n_rows; j++) {
                rst[i][j] = mat[j][i];
            }
        }
        return rst;
    }

    auto begin() -> std::vector<Vector>::iterator {
        return mat.begin();
    }

    auto end() -> std::vector<Vector>::iterator {
        return mat.end();
    }

    auto begin() const -> std::vector<Vector>::const_iterator {
        return mat.begin();
    }

    auto end() const -> std::vector<Vector>::const_iterator {
        return mat.end();
    }


    auto operator[] (size_t row) -> Vector& {
        if (row >= n_rows){
            throw std::invalid_argument("Range out of bound.");
        }
        return mat[row];
    }

    auto operator[] (size_t row) const -> const Vector& {
        if (row >= n_rows){
            throw std::invalid_argument("Range out of bound.");
        }
        return mat[row];
    }

    Matrix operator+ (const Matrix& another_mat) const {
        check_dimension(another_mat);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] += another_mat[i][j];
            }
        }
        return rst;
    }

    Matrix operator- (const Matrix& another_mat) const {
        check_dimension(another_mat);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] -= another_mat[i][j];
            }
        }
        return rst;
    }

    Matrix operator* (const Matrix& another_mat) const {
        check_dimension(another_mat);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] +=  another_mat[i][j] * mat[i][j];
            }
        }
        return rst;
    }

    Matrix operator/ (const Matrix& another_mat) const {
        check_dimension(another_mat);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] /= another_mat[i][j];
            }
        }
        return rst;
    }


    template <typename Scalar>
    Matrix operator- (const Scalar& value) const {
        double double_value = static_cast<double>(value);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] -= double_value;
            }
        }
        return rst;
    }

    template <typename Scalar>
    Matrix operator+ (const Scalar& value) const {
        double double_value = static_cast<double>(value);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] += double_value;
            }
        }
        return rst;
    }

    template <typename Scalar>
    Matrix operator* (const Scalar& value) const {
        double double_value = static_cast<double>(value);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] *= double_value;
            }
        }
        return rst;
    }

    template <typename Scalar>
    Matrix operator/ (const Scalar& value) const {
        double double_value = static_cast<double>(value);
        Matrix rst(*this);
        for (size_t i=0; i<n_rows; i++){
            for (size_t j=0; j<n_cols; j++){
                rst[i][j] /= double_value;
            }
        }
        return rst;
    }

    void display() const {
        for (size_t i = 0; i < n_rows; i++) {
            mat[i].display();
        }
        printf("\n");
    }
};

// class Matrix {
// private:
//     double** mat;
//     size_t n_rows, n_cols;
//     void check_dimension(const Matrix& another_mat) const{
//         if (n_rows != another_mat.n_rows) {
//             throw std::invalid_argument("Number of Rows doesn't match.");
//         }
//         else if (n_cols != another_mat.n_cols) {
//             throw std::invalid_argument("Number of Cols doesn't match.");
//         }
//     }

// public:
//     Matrix(){
//         n_rows = n_cols = 0;
//         mat = nullptr;
//     }

//     Matrix(const size_t nrows, const size_t ncols, const double init_value = 0){
//         n_rows = nrows;
//         n_cols = ncols;
//         mat = new double*[n_rows];
//         for (size_t i=0; i<n_rows; i++) {
//             mat[i] = new double[n_cols];
//             std::fill(mat[i], mat[i] + n_cols, init_value);
//         }
//     }

//     Matrix(const Matrix& another_mat) {
//         n_rows = another_mat.num_rows();
//         n_cols = another_mat.num_cols();
//         mat = new double*[n_rows];
//         for (size_t i=0; i<n_rows; i++){
//             mat[i] = new double[n_cols];
//             for (size_t j=0; j<n_cols; j++){
//                 mat[i][j] = another_mat(i, j);
//             }
//         }
//     }

//     ~Matrix() {
//         for (size_t i=0; i<n_rows; i++) {
//             delete[] mat[i];
//         }
//         delete[] mat;
//     }

//     size_t num_rows() {
//         return n_rows;
//     }

//     size_t num_rows() const{
//         return n_rows;
//     }

//     size_t num_cols() {
//         return n_cols;
//     }

//     size_t num_cols() const{
//         return n_cols;
//     }

//     double& operator() (const size_t& row, const size_t& col) const {
//         if (row >= n_rows || col >= n_cols){
//             throw std::invalid_argument("Range out of bound.");
//         }
//         return mat[row][col];
//     }

//     template <typename Scalar>
//     Matrix operator- (const Scalar& value) const {
//         double double_value = static_cast<double>(value);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) -= double_value;
//             }
//         }
//         return rst;
//     }

//     Matrix operator- (const Matrix& another_mat) const {
//         check_dimension(another_mat);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) -= another_mat(i, j);
//             }
//         }
//         return rst;
//     }

//     template <typename Scalar>
//     Matrix operator+ (const Scalar& value) const {
//         double double_value = static_cast<double>(value);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) += double_value;
//             }
//         }
//         return rst;
//     }

//     Matrix operator+ (const Matrix& another_mat) const {
//         check_dimension(another_mat);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) += another_mat(i, j);
//             }
//         }
//         return rst;
//     }

//     template <typename Scalar>
//     Matrix operator* (const Scalar& value) const {
//         double double_value = static_cast<double>(value);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) *= double_value;
//             }
//         }
//         return rst;
//     }

//     Matrix operator* (const Matrix& another_mat) const {
//         check_dimension(another_mat);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) +=  another_mat(i, j) * mat[i][j];
//             }
//         }
//         return rst;
//     }

//     template <typename Scalar>
//     Matrix operator/ (const Scalar& value) const {
//         double double_value = static_cast<double>(value);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) /= double_value;
//             }
//         }
//         return rst;
//     }

//     Matrix operator/ (const Matrix& another_mat) const {
//         check_dimension(another_mat);
//         Matrix rst(*this);
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++){
//                 rst(i, j) /= another_mat(i, j);
//             }
//         }
//         return rst;
//     }

//     bool operator== (const Matrix& another_mat) const {
//         check_dimension(another_mat);
//         for (size_t i = 0; i < n_rows; i++) {
//             for (size_t j = 0; j < n_cols; j++) {
//                 if (mat[i][j] != another_mat(i, j)) {
//                     return false;
//                 }
//             }
//         }
//         return true;
//     }

//     Matrix dot(const Matrix& another_mat) {
//         if (n_cols != another_mat.n_rows) {
//             throw std::invalid_argument("mat_1's n_cols does not match mat_2's n_rows.");
//         }
//         Matrix rst(n_rows, another_mat.n_cols);
//         for (size_t i=0; i<n_rows; i++) {
//             for (size_t j=0; j<another_mat.n_cols; j++) {
//                 for (size_t k=0; k<n_cols; k++) {
//                     rst(i, j) += mat[i][k] * another_mat(k, j);
//                 }
//             }
//         }
//         return rst;
//     }

//     Vector dot(const Vector& vec) {
//         if (n_cols != vec.size()) {
//             throw std::invalid_argument("mat's n_cols does not match vec's size.");
//         }
//         Vector rst(n_rows);
//         for (size_t i=0; i<n_rows; i++) {
//             for (size_t j=0; j<n_cols; j++) {
//                 rst[i] += mat[i][j] * vec[j];
//             }
//         }
//         return rst;
//     }

//     Matrix transpose() {
//         Matrix rst(n_cols, n_rows);
//         for (size_t i = 0; i < n_cols; i++) {
//             for (size_t j = 0; j < n_rows; j++) {
//                 rst(i, j) = mat[j][i];
//             }
//         }
//         return rst;
//     }

//     void display() const {
//         for (size_t i=0; i<n_rows; i++){
//             for (size_t j=0; j<n_cols; j++) {
//                 printf("%lf ", mat[i][j]);
//             }
//             printf("\n");
//         }
//         printf("\n");
//     }
// };

// Vector Vector::dot(const Matrix& mat){
//     if (size() != mat.num_rows()) {
//         throw std::invalid_argument("vec's size does not math mat's n_rows.");
//     }
//     Vector rst(mat.num_cols());
//     for (size_t i=0; i<mat.num_cols(); i++){
//         for (size_t j=0; j<size(); j++){
//             rst[i] += vec[j] * mat(j, i);
//         }
//     }
//     return rst;
// };

#endif