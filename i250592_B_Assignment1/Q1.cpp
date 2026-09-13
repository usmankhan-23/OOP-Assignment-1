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





bool isValidMove(int** grid, int** visited, int rows, int cols, int r, int c){
    if (r < 0 || r >= rows || c < 0 || c >= cols){
        return false;
    }
    if (*(*(grid + r) + c) == 1){
        return false;
    }
    if (*(*(visited + r) + c) == 1){
        return false;
    }
    return true;
}




int countReachable(int** grid, int** visited, int rows, int cols, int r, int c){
    if (!isValidMove(grid, visited, rows, cols, r, c)){
        return 0;
    }
    *(*(visited + r) + c) = 1;
    int count = 1;
    count = count + countReachable(grid, visited, rows, cols, r - 1, c);
    count = count + countReachable(grid, visited, rows, cols, r + 1, c);
    count = count + countReachable(grid, visited, rows, cols, r, c - 1);
    count = count + countReachable(grid, visited, rows, cols, r, c + 1);
    return count;
}








int countAccessibleVictims(int** grid, int** visited, int rows, int cols){
    int count = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (*(*(grid + i) + j) == 2 &&
                *(*(visited + i) + j) == 1){
                count++;
            }
        }
    }
    return count;
}




int countIsolatedVictims(int** grid, int** visited, int rows, int cols){
    int count = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (*(*(grid + i) + j) == 2 && *(*(visited + i) + j) == 0){
                bool hasReachableNeighbor = false;

                if (i - 1 >= 0 && *(*(visited + i - 1) + j) == 1){
                    hasReachableNeighbor = true;
                }
                if (i + 1 < rows && *(*(visited + i + 1) + j) == 1){
                    hasReachableNeighbor = true;
                }
                if (j - 1 >= 0 && *(*(visited + i) + j - 1) == 1){
                    hasReachableNeighbor = true;
                }
                if (j + 1 < cols && *(*(visited + i) + j + 1) == 1){
                    hasReachableNeighbor = true;
                }
                if (!hasReachableNeighbor){
                    count++;
                }
            }
        }
    }
    return count;
} 





void analyzeSupplyPoints(int** grid, int** visited, int rows, int cols){
    int supplyCount = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (*(*(grid + i) + j) == 3){
                supplyCount++;
                cout << "Supply Point at (" << i << ", " << j << "): ";
                if (*(*(visited + i) + j) == 1){
                    cout << "Reachable" << endl;
                }
                else{
                    cout << "Not Reachable" << endl;
                }
            }
        }
    }
    if (supplyCount == 0)
    {
        cout << "No supply point exists." << endl;
    }
}




int** createVictimReport(int** grid, int** visited, int rows, int cols, int& count){
    count = countAccessibleVictims(grid, visited, rows, cols);
    if (count == 0){
        return nullptr;
    }
    int** report = new int* [count];
    for (int i = 0; i < count; i++){
        *(report + i) = new int[2];
    }
    int reportIndex = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (*(*(grid + i) + j) == 2 &&
                *(*(visited + i) + j) == 1){
                *(*(report + reportIndex) + 0) = i;
                *(*(report + reportIndex) + 1) = j;
                reportIndex++;
            } 
        }
    }
    return report;
}





int** createEvacuationGrid(int** grid, int** visited, int rows, int cols){
    int** evacuationGrid = new int* [rows];
    for (int i = 0; i < rows; i++){
        *(evacuationGrid + i) = new int[cols];
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int value = *(*(grid + i) + j);

            if (value == 0){
                if (*(*(visited + i) + j) == 1){
                    value = 5;
                }
            }
            else if (value == 1){
                value = 1;
            }
            else if (value == 2){
                if (*(*(visited + i) + j) == 1){
                    value = 6;
                }
            }
            else if (value == 3){
                value = 3;
            }
            else if (value == 4){
                value = 4;
            }
            *(*(evacuationGrid + i) + j) = value;
        }
    }
    return evacuationGrid;
}




int countRegion(int** grid, int** visited, int rows, int cols, int r, int c){
    if (r < 0 || r >= rows || c < 0 || c >= cols){
        return 0;
    }
    if (*(*(grid + r) + c) == 1){
        return 0;
    }
    if (*(*(visited + r) + c) == 1){
        return 0;
    }
    *(*(visited + r) + c) = 1;
    int count = 1;
    count = count + countRegion(grid, visited, rows, cols, r - 1, c);
    count = count + countRegion(grid, visited, rows, cols, r + 1, c);
    count = count + countRegion(grid, visited, rows, cols, r, c - 1);
    count = count + countRegion(grid, visited, rows, cols, r, c + 1);
    return count;
}




int largestConnectedRegion(int** grid, int rows, int cols){
    int** visited = new int* [rows];
    for (int i = 0; i < rows; i++){
        *(visited + i) = new int[cols];
        for (int j = 0; j < cols; j++){
            *(*(visited + i) + j) = 0;
        }
    }
    int largest = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (*(*(grid + i) + j) != 1 && *(*(visited + i) + j) == 0){
                int regionSize = countRegion(grid,visited,rows,cols,i,j);
                if (regionSize > largest){
                    largest = regionSize;
                }
            }
        }
    }
    for (int i = 0; i < rows; i++){
        delete[] * (visited + i);
    }
    delete[] visited;
    return largest;
}





int main()
{
    int rows = 4;
    int cols = 4;

    int** grid = createGrid(rows, cols);

    int values[4][4] =
    {
        {0, 0, 1, 0},
        {0, 2, 1, 0},
        {1, 1, 1, 0},
        {3, 0, 0, 0}
    };

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(grid + i) + j) = values[i][j];
        }
    }

    cout << "Original Grid:" << endl;
    displayGrid(grid, rows, cols);

    cout << endl;

    int result = largestConnectedRegion(grid, rows, cols);

    cout << "Largest Connected Region: " << result << endl;

    cout << endl;

    cout << "Original Grid After Calculation:" << endl;
    displayGrid(grid, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        delete[] * (grid + i);
    }

    delete[] grid;

    return 0;
}