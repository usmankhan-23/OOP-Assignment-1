#include <iostream>
using namespace std;

int** createGrid(int rows, int cols){
    int** grid = new int* [rows];
    for (int i = 0; i < rows; i++){
        *(grid + i) = new int[cols];
    }
    return grid;
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

    cout << "Grid created successfully." << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(grid + i) + j) = 0;
        }
    }

    cout << "Memory allocated successfully." << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] * (grid + i);
    }

    delete[] grid;

    cout << "Memory released successfully." << endl;

    return 0;
}