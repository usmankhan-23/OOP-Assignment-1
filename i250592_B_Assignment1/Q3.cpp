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




int dominantRow(int** matrix, int n){
    int bestSum = 0;
    for (int j = 0; j < n; j++){
        bestSum = bestSum + *(*(matrix + 0) + j);
    }
    int bestRow = 0;

    for (int i = 1; i < n; i++){
        int rowSum = 0;
        for (int j = 0; j < n; j++){
            rowSum = rowSum + *(*(matrix + i) + j);
        }
        if (rowSum > bestSum){
            bestSum = rowSum;
            bestRow = i;
        }
    }
    return bestRow;
}




int** rotateMatrix(int** matrix, int n){
    int** rotatedMatrix = createMatrix(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            *(*(rotatedMatrix + j) + (n - 1 - i))
                = *(*(matrix + i) + j);
        }
    }
    return rotatedMatrix;
}




int matrixBalance(int** matrix, int n){
    int aboveSum = 0;
    int belowSum = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j > i){
                aboveSum = aboveSum + *(*(matrix + i) + j);
            }
            else if (i > j){
                belowSum = belowSum + *(*(matrix + i) + j);
            }
        }
    }
    return aboveSum - belowSum;
}




int main(){
    int n = 3;
    
    int** matrix = createMatrix(n, n);
    
    cout << "Enter matrix:" << endl;
    inputMatrix(matrix, n, n);

    int result = matrixBalance(matrix, n);
    cout << "Matrix balance: " << result << endl;
    for (int i = 0; i < n; i++){
    delete[] * (matrix + i);
    
    }

    delete[] matrix;
    
    return 0;
}




