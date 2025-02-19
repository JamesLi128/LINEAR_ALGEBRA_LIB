#ifndef VECTOR_H
#define VECTOR_H

#include "linear_algebra_object.h"
#include <iostream>

class Vector : public LinearAlgebraObject{
private:
    double* vec;
    int size;

public:
    // default constructor
    Vector() {
        size = 0;
    }

    // initialize with fixed value
    Vector(const int& size, const double& init_value=0){
        vec = new double[size];
        std::fill(vec, vec + size, init_value);
        this->size = size;
    }

    // initialize with a double arr
    Vector(const double* init_arr) : size(sizeof(init_arr)){
        vec = new double[size];
        for (int i=0 ; i < size; i++){
            vec[i] = init_arr[i];
        }
    }

    // initialize with another vector instance
    Vector(const Vector& another_vector) : size(another_vector.size){
        vec = new double[size];
        for (int i=0 ; i < size; i++){
            vec[i] = another_vector[i];
        }
    }

    // destructor, avoid memory leak
    ~Vector() {
        delete[] vec;
    }

    double dot(const Vector& other_vector) const{
        if (size != other_vector.size){
            throw std::invalid_argument("Dot product dimension doesn't match.");
        }
        double rst = 0;
        for (int i=0; i<size; i++){
            rst += vec[i] * other_vector[i];
        }
        return rst;
    }

    // overload operator [], read & write
    double& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        return vec[index];
    }

    // overload operator [] for const, read only
    const double& operator[] (int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        return vec[index];
    }

    // overload operator +
    Vector operator + (const Vector& another_vector) {
        if (size != another_vector.size) {
            throw std::invalid_argument("Array sizes must match. ");
        }
        Vector rst(size);
        for (int i=0; i<size; i++) {
            rst[i] = vec[i] + another_vector[i];
        }
        return rst;
    }

    // overload operator -
    Vector operator - (const Vector& another_vector) {
        if (size != another_vector.size) {
            throw std::invalid_argument("Array sizes must match. ");
        }
        Vector rst(size);
        for (int i=0; i<size; i++) {
            rst[i] = vec[i] - another_vector[i];
        }
        return rst;
    }
};



#endif // VECTOR_H