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


int main()
{
    int rows = 3;
    int cols = 3;

    int** grid = createGrid(rows, cols);
    int** visited = createGrid(rows, cols);

    cout << "Test 1:" << endl;

    *(*(grid + 0) + 0) = 4;
    *(*(grid + 0) + 1) = 0;
    *(*(grid + 0) + 2) = 2;

    *(*(grid + 1) + 0) = 0;
    *(*(grid + 1) + 1) = 1;
    *(*(grid + 1) + 2) = 0;

    *(*(grid + 2) + 0) = 2;
    *(*(grid + 2) + 1) = 0;
    *(*(grid + 2) + 2) = 3;

    *(*(visited + 0) + 0) = 1;
    *(*(visited + 0) + 1) = 1;
    *(*(visited + 0) + 2) = 1;

    *(*(visited + 1) + 0) = 1;
    *(*(visited + 1) + 1) = 0;
    *(*(visited + 1) + 2) = 1;

    *(*(visited + 2) + 0) = 1;
    *(*(visited + 2) + 1) = 1;
    *(*(visited + 2) + 2) = 1;

    int count = 0;

    int** report = createVictimReport(
        grid,
        visited,
        rows,
        cols,
        count
    );

    cout << "Accessible Victims: " << count << endl;

    for (int i = 0; i < count; i++)
    {
        cout << "("
            << *(*(report + i) + 0)
            << ", "
            << *(*(report + i) + 1)
            << ")" << endl;
    }

    for (int i = 0; i < count; i++)
    {
        delete[] * (report + i);
    }

    delete[] report;


    cout << endl;
    cout << "Test 2:" << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(grid + i) + j) = 0;
            *(*(visited + i) + j) = 0;
        }
    }

    *(*(grid + 0) + 0) = 4;
    *(*(grid + 0) + 1) = 0;
    *(*(grid + 0) + 2) = 2;

    *(*(grid + 1) + 0) = 1;
    *(*(grid + 1) + 1) = 1;
    *(*(grid + 1) + 2) = 1;

    *(*(grid + 2) + 0) = 0;
    *(*(grid + 2) + 1) = 0;
    *(*(grid + 2) + 2) = 0;

    *(*(visited + 0) + 0) = 1;
    *(*(visited + 0) + 1) = 1;
    *(*(visited + 0) + 2) = 0;

    int count2 = 0;

    int** report2 = createVictimReport(
        grid,
        visited,
        rows,
        cols,
        count2
    );

    cout << "Accessible Victims: " << count2 << endl;

    if (count2 == 0)
    {
        cout << "No accessible victims." << endl;
    }

    if (report2 != nullptr)
    {
        for (int i = 0; i < count2; i++)
        {
            delete[] * (report2 + i);
        }

        delete[] report2;
    }


    cout << endl;
    cout << "Test 3:" << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(grid + i) + j) = 0;
            *(*(visited + i) + j) = 0;
        }
    }

    *(*(grid + 0) + 0) = 2;
    *(*(grid + 0) + 1) = 0;
    *(*(grid + 0) + 2) = 0;

    *(*(grid + 1) + 0) = 0;
    *(*(grid + 1) + 1) = 2;
    *(*(grid + 1) + 2) = 0;

    *(*(grid + 2) + 0) = 0;
    *(*(grid + 2) + 1) = 0;
    *(*(grid + 2) + 2) = 2;

    *(*(visited + 0) + 0) = 1;
    *(*(visited + 0) + 1) = 0;
    *(*(visited + 0) + 2) = 0;

    *(*(visited + 1) + 0) = 0;
    *(*(visited + 1) + 1) = 1;
    *(*(visited + 1) + 2) = 0;

    *(*(visited + 2) + 0) = 0;
    *(*(visited + 2) + 1) = 0;
    *(*(visited + 2) + 2) = 1;

    int count3 = 0;

    int** report3 = createVictimReport(
        grid,
        visited,
        rows,
        cols,
        count3
    );

    cout << "Accessible Victims: " << count3 << endl;

    for (int i = 0; i < count3; i++)
    {
        cout << "("
            << *(*(report3 + i) + 0)
            << ", "
            << *(*(report3 + i) + 1)
            << ")" << endl;
    }

    for (int i = 0; i < count3; i++)
    {
        delete[] * (report3 + i);
    }

    delete[] report3;


    cout << endl;
    cout << "Test 4:" << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(grid + i) + j) = 0;
            *(*(visited + i) + j) = 0;
        }
    }

    int count4 = 0;

    int** report4 = createVictimReport(
        grid,
        visited,
        rows,
        cols,
        count4
    );

    cout << "Accessible Victims: " << count4 << endl;

    if (report4 == nullptr)
    {
        cout << "Report is empty." << endl;
    }


    for (int i = 0; i < rows; i++)
    {
        delete[] * (grid + i);
        delete[] * (visited + i);
    }

    delete[] grid;
    delete[] visited;

    return 0;
}
