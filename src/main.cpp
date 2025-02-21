#include <iostream>
#include <cmath>
#include "VecMat.h"
#include "utils.h"

using namespace std;

int main(){
    Vector vec(5, 1);
    cout << pow(vec.norm(), 2.0) <<endl;
}
