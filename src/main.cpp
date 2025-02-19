#include <iostream>
#include "VecMat.h"

using namespace std;

int main(){
    Matrix mat_1(5, 5, 1), mat_2(5, 5, 2);
    Vector vec_1(5, 1), vec_2(5, 2);
    mat_1.dot(mat_2).display();
    mat_1.dot(vec_1).display();
    vec_1.dot(mat_2).display();
    cout << vec_1.dot(vec_2) << endl;
}
