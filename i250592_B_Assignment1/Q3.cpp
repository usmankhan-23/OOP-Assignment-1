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




bool isBalancedMatrix(int** matrix, int n)
{
    if (diagonalDifference(matrix, n) != 0){
        return false;
    }
    if (matrixBalance(matrix, n) != 0){
        return false;
    }
    int maximumSum = 0;

    for (int j = 0; j < n; j++){
        maximumSum = maximumSum + *(*(matrix + 0) + j);
    }
    int maximumCount = 1;
    for (int i = 1; i < n; i++){
        int rowSum = 0;
        for (int j = 0; j < n; j++){
            rowSum = rowSum + *(*(matrix + i) + j);
        }
        if (rowSum > maximumSum){
            maximumSum = rowSum;
            maximumCount = 1;
        }
        else if (rowSum == maximumSum){
            maximumCount = maximumCount + 1;
        }
    }
    if (maximumCount != 1){
        return false;
    }
    return true;
}




int** transformMatrix(int** matrix, int n){
    int** transformedMatrix = createMatrix(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int value = *(*(matrix + i) + j);
            if (i == j){
                value = value * value;
            }
            else if (j == n - 1 - i){
                if (value < 0){
                    value = -value;
                }
            }
            *(*(transformedMatrix + i) + j) = value;
        }
    }
    return transformedMatrix;
}



int main()
{
    int n;

    cout << "Enter matrix size: ";
    cin >> n;

    int** matrix = createMatrix(n, n);

    cout << "Enter matrix:" << endl;

    inputMatrix(matrix, n, n);

    int** transformedMatrix = transformMatrix(matrix, n);

    cout << endl;

    cout << "Original Matrix:" << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << *(*(matrix + i) + j) << " ";
        }

        cout << endl;
    }

    cout << endl;

    cout << "Transformed Matrix:" << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << *(*(transformedMatrix + i) + j) << " ";
        }

        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        delete[] * (matrix + i);
        delete[] * (transformedMatrix + i);
    }

    delete[] matrix;
    delete[] transformedMatrix;

    return 0;
}





