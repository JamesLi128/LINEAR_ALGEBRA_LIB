#ifndef LINEAR_ALGEBRA_OBJECT_H
#define LINEAR_ALGEBRA_OBJECT_H

class LinearAlgebraObject{
public:
    virtual ~LinearAlgebraObject() = default;
    virtual double dot(const LinearAlgebraObject& another_LAO) const = 0;
    virtual int* shape() const = 0;
};

#endif