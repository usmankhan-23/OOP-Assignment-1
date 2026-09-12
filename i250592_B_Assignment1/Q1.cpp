#include <iostream>
using namespace std;

int** createGrid(int rows, int cols){
    int** grid = new int* [rows];
    for (int i = 0; i < rows; i++){
        *(grid + i) = new int[cols];
    }
    return grid;
}





void inputGrid(int** grid, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int value;
            cin >> value;
            while (value < 0 || value > 4){
                cout << "Invalid enter again: ";
                cin >> value;
            }
            *(*(grid + i) + j) = value;
        }
    }
}





void displayGrid(int** grid, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << *(*(grid + i) + j) << " ";
        }
        cout << endl;
    }
}




int main()
{
    int rows;
    int cols;

    cout << "Enter rows: ";
    cin >> rows;

    cout << "Enter columns: ";
    cin >> cols;

    int** grid = createGrid(rows, cols);

    cout << "Enter grid values:" << endl;

    inputGrid(grid, rows, cols);

    cout << endl;

    cout << "Grid:" << endl;

    displayGrid(grid, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        delete[] * (grid + i);
    }

    delete[] grid;

    return 0;
}