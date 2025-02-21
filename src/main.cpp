#include <iostream>
#include <cmath>
#include "VecMat.h"
#include "utils.h"

using namespace std;

int main(){
    Matrix mat(5, 5, 1);
    mat = Randomize_Matrix_Entries(mat);
    cout << "Matrix after randomization:" << endl;
    mat.display();
    for (auto row : mat){
        row.display();
    }
    return 0;
}
