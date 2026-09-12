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




int countCells(int** grid, int rows, int cols, int value){
    int count = 0;
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            if (*(*(grid + r) + c) == value){
                count = count + 1;
            }
        }
    }
    return count;
}




void findFirstCell(int** grid, int rows, int cols, int value, int& row, int& col){
    row = -1;
    col = -1;
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            if (*(*(grid + r) + c) == value)
            {
                row = r;
                col = c;
                return;
            }
        }
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

    displayGrid(grid, rows, cols);

    int value;
    int row;
    int col;

    cout << endl;
    cout << "Enter value to find: ";
    cin >> value;

    findFirstCell(grid, rows, cols, value, row, col);

    cout << "First occurrence: (" << row << ", " << col << ")" << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] * (grid + i);
    }

    delete[] grid;

    return 0;
}