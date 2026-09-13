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


void deleteGrid(int** grid, int rows){
    for (int i = 0; i < rows; i++){
        delete[] * (grid + i);
    }
    delete[] grid;
}


int main(){
    int rows;
    int cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    int** grid = createGrid(rows, cols);
    cout << "Enter grid values:" << endl;
    inputGrid(grid, rows, cols);

    int** visited = createGrid(rows, cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            *(*(visited + i) + j) = 0;
        }
    }
    int teamRow;
    int teamCol;
    findFirstCell(grid, rows, cols, 4, teamRow, teamCol);
    int reachableCells = 0;
    if (teamRow != -1 && teamCol != -1){
        reachableCells = countReachable(grid,visited,rows,cols,teamRow,teamCol);
    }
    int blockedAreas = countCells(grid, rows, cols, 1);
    int victims = countCells(grid, rows, cols, 2);
    int supplyPoints = countCells(grid, rows, cols, 3);
    int emergencyTeams = countCells(grid, rows, cols, 4);
    int emptyAreas = countCells(grid, rows, cols, 0);
    int accessibleVictims = countAccessibleVictims(grid,visited,rows,cols);
    int inaccessibleVictims = victims - accessibleVictims;
    int isolatedVictims = countIsolatedVictims(grid,visited,rows,cols);
    int reachableSupplyPoints = 0;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (*(*(grid + i) + j) == 3 &&
                *(*(visited + i) + j) == 1){
                reachableSupplyPoints++;
            }
        }
    }
    int victimReportCount;
    int** victimReport = createVictimReport(grid,visited,rows,cols,victimReportCount);
    analyzeSupplyPoints(grid,visited,rows,cols);
    int largestRegion = largestConnectedRegion(grid,rows,cols);
    int** evacuationGrid = createEvacuationGrid(grid,visited,rows,cols);
    cout << endl;

    cout << "============================================" << endl;
    cout << "EMERGENCY RESPONSE REPORT" << endl;
    cout << "============================================" << endl;
    cout << "Grid Size : " << rows << " x " << cols << endl;
    cout << "Total Cells : " << rows * cols << endl;
    cout << "Empty Areas : " << emptyAreas << endl;
    cout << "Blocked Areas : " << blockedAreas << endl;
    cout << "Victims : " << victims << endl;
    cout << "Supply Points : " << supplyPoints << endl;
    cout << "Emergency Teams : " << emergencyTeams << endl;
    cout << "Reachable Cells : " << reachableCells << endl;
    cout << "Accessible Victims : " << accessibleVictims << endl;
    cout << "Inaccessible Victims : " << inaccessibleVictims << endl;
    cout << "Isolated Victims : " << isolatedVictims << endl;
    cout << "Reachable Supply Points : " << reachableSupplyPoints << endl;
    cout << "Largest Connected Region : " << largestRegion << endl;
    cout << "============================================" << endl;

    cout << endl;
    cout << "Accessible Victim Coordinates:" << endl;
    if (victimReportCount == 0){
        cout << "No accessible victims." << endl;
    }
    else{
        for (int i = 0; i < victimReportCount; i++){
            cout << "("<< *(*(victimReport + i) + 0)<< ", " << *(*(victimReport + i) + 1) << ")" << endl;
        }
    }
    cout << endl;
    cout << "Evacuation Grid:" << endl;
    displayGrid(evacuationGrid,rows,cols);

    if (victimReport != nullptr){
        for (int i = 0; i < victimReportCount; i++){
            delete[] * (victimReport + i);
        }
        delete[] victimReport;
    }
    deleteGrid(evacuationGrid, rows);
    deleteGrid(visited, rows);
    deleteGrid(grid, rows);
    return 0;
}