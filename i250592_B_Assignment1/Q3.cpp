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




int diagonalDifference(int** matrix, int n){
    int primarySum = 0;
    int secondarySum = 0;
    for (int i = 0; i < n; i++){
        primarySum = primarySum + *(*(matrix + i) + i);
        secondarySum = secondarySum + *(*(matrix + i) + (n - 1 - i));
    }
    return primarySum - secondarySum;
}




int main(){
    int n = 3;
    int** matrix = createMatrix(n, n);
    cout << "Enter matrix:" << endl;
    inputMatrix(matrix, n, n);
    cout << "Diagonal difference: "<< diagonalDifference(matrix, n) << endl;

    for (int i = 0; i < n; i++){
        delete[] * (matrix + i);
    }
    delete[] matrix;
    return 0;
}



