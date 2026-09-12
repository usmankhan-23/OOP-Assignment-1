#include <iostream>
using namespace std;

int** createMatrix(int rows, int cols){
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++){
        *(matrix + i) = new int[cols];
    }
    return matrix;
}




void inputMatrix(int** matrix, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cin >> *(*(matrix + i) + j);
        }
    }
}




int main(){
    int rows = 3;
    int cols = 3;
    int** matrix = createMatrix(rows, cols);
    cout << "Enter matrix:" << endl;
    inputMatrix(matrix, rows, cols);

    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < rows; i++){
        delete[] * (matrix + i);
    }

    delete[] matrix;
return 0;
}



