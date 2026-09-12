#include <iostream>
using namespace std;

int** createMatrix(int rows, int cols){
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++){
        *(matrix + i) = new int[cols];
    }
    return matrix;
}



int main(){
    int rows = 3;
    int cols = 3;

    int** matrix = createMatrix(rows, cols);

    cout << "Matrix created successfully." << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(matrix + i) + j) = 0;
        }
    }

    cout << "Memory allocated successfully." << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] * (matrix + i);
    }

    delete[] matrix;

    cout << "Memory released successfully." << endl;

    return 0;
}
