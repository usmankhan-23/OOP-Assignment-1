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





bool isValidMove(int** grid, bool** visited, int rows, int cols, int r, int c){
    if (r < 0 || r >= rows || c < 0 || c >= cols){
        return false;
    }
    if (*(*(grid + r) + c) == 1){
        return false;
    }
    if (*(*(visited + r) + c)){
        return false;
    }
    return true;
} 




int countReachable(int** grid, bool** visited, int rows, int cols, int r, int c){ 
    if (!isValidMove(grid, visited, rows, cols, r, c)){
        return 0;
    }
    *(*(visited + r) + c) = true;
    int count = 1;
    count = count + countReachable(grid, visited, rows, cols, r - 1, c);
    count = count + countReachable(grid, visited, rows, cols, r + 1, c);
    count = count + countReachable(grid, visited, rows, cols, r, c - 1);
    count = count + countReachable(grid, visited, rows, cols, r, c + 1);
    return count;
}



int main()
{
    int rows = 3;
    int cols = 3;

    int** grid = createGrid(rows, cols);

    bool** visited = new bool* [rows];

    for (int i = 0; i < rows; i++)
    {
        *(visited + i) = new bool[cols];
    }

    *(*(grid + 0) + 0) = 0;
    *(*(grid + 0) + 1) = 0;
    *(*(grid + 0) + 2) = 1;

    *(*(grid + 1) + 0) = 0;
    *(*(grid + 1) + 1) = 0;
    *(*(grid + 1) + 2) = 1;

    *(*(grid + 2) + 0) = 1;
    *(*(grid + 2) + 1) = 0;
    *(*(grid + 2) + 2) = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(visited + i) + j) = false;
        }
    }

    int result = countReachable(grid, visited, rows, cols, 0, 0);

    cout << "Reachable cells: " << result << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] * (visited + i);
    }

    delete[] visited;

    for (int i = 0; i < rows; i++)
    {
        delete[] * (grid + i);
    }

    delete[] grid;

    return 0;
}