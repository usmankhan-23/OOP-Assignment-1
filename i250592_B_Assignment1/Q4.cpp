#include <iostream>
#include <cstdlib>
using namespace std;

char*** createGrid(int size);
void allocateLayers(char*** grid, int z, int size);
void allocateRows(char** layer, int y, int size);
void initializeGrid(char*** grid, int z, int y, int x, int size);
bool checkBounds(int z, int y, int x, int size);
void displayColumns(char* row, int x, int size);
void displayRows(char** layer, int y, int size);
void displayLayers(char*** grid, int z, int size);
void deleteRows(char** layer, int y, int size);
void deleteGrid(char*** grid, int z, int size);
bool searchDirection(char*** grid,const char* word,int z,int y,int x,int dz,int dy,int dx,int index,int size);
bool searchDirections(char*** grid,const char* word,int z,int y,int x,int size);
void searchCells(char*** grid,const char* word,int z,int y,int x,int size);


char*** createGrid(int size){
    char*** grid = new char** [size];
    allocateLayers(grid, 0, size);
    return grid;
}

void allocateLayers(char*** grid, int z, int size){
    if (z == size){
        return;
    }
    *(grid + z) = new char* [size];
    allocateRows(*(grid + z), 0, size);
    allocateLayers(grid, z + 1, size);
}

void allocateRows(char** layer, int y, int size){
    if (y == size){
        return;
    }
    *(layer + y) = new char[size];
    allocateRows(layer, y + 1, size);
}

void deleteRows(char** layer, int y, int size)
{
    if (y == size)
    {
        return;
    }

    deleteRows(layer, y + 1, size);

    delete[] * (layer + y);
}

void deleteGrid(char*** grid, int z, int size)
{
    if (z == size)
    {
        return;
    }

    deleteGrid(grid, z + 1, size);

    deleteRows(*(grid + z), 0, size);

    delete[] * (grid + z);
}

void initializeGrid(char*** grid, int z, int y, int x, int size){
    if (z >= size){ 
        return;
    }
    *(*(*(grid + z) + y) + x) = 'A' + (rand() % 26);
    if (x + 1 < size){
        initializeGrid(grid, z, y, x + 1, size);
    }
    else if (y + 1 < size){
        initializeGrid(grid, z, y + 1, 0, size);
    }
    else{
        initializeGrid(grid, z + 1, 0, 0, size);
    }
}

void displayColumns(char* row, int x, int size){
    if (x == size){
        return;
    }
    cout << *(row + x) << " ";
    displayColumns(row, x + 1, size);
}

void displayRows(char** layer, int y, int size){
    if (y == size){
        return;
    }
    displayColumns(*(layer + y), 0, size);
    cout << endl;
    displayRows(layer, y + 1, size);
} 

void displayLayers(char*** grid, int z, int size){
    if (z == size){
        return;
    }
    cout << "--- LAYER " << z << " ---" << endl;
    displayRows(*(grid + z), 0, size);
    cout << endl;
    displayLayers(grid, z + 1, size);
}

bool checkBounds(int z, int y, int x, int size)
{
    if (z < 0 || z >= size)
    {
        return false;
    }

    if (y < 0 || y >= size)
    {
        return false;
    }

    if (x < 0 || x >= size)
    {
        return false;
    }

    return true;
}


bool searchDirection(char*** grid,const char* word,int z,int y,int x,int dz,int dy,int dx,int index,int size){
    if (*(word + index) == '\0'){
        return true;
    }
    if (!checkBounds(z, y, x, size)){
        return false;
    }
    if (*(*(*(grid + z) + y) + x) != *(word + index)){
        return false;
    }
    return searchDirection(grid,word,z + dz,y + dy,x + dx,dz,dy,dx,index + 1,size);
}

bool searchDirections(
    char*** grid,
    const char* word,
    int z,
    int y,
    int x,
    int size
)
{
    static int direction = 0;

    if (direction == 13)
    {
        direction = 0;
        return false;
    }

    bool found = false;

    if (direction == 0)
    {
        found = searchDirection(
            grid, word, z, y, x,
            0, 0, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                0, 0, -1, 0, size
            );
        }
    }
    else if (direction == 1)
    {
        found = searchDirection(
            grid, word, z, y, x,
            0, 1, 0, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                0, -1, 0, 0, size
            );
        }
    }
    else if (direction == 2)
    {
        found = searchDirection(
            grid, word, z, y, x,
            1, 0, 0, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                -1, 0, 0, 0, size
            );
        }
    }
    else if (direction == 3)
    {
        found = searchDirection(
            grid, word, z, y, x,
            0, 1, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                0, -1, -1, 0, size
            );
        }
    }
    else if (direction == 4)
    {
        found = searchDirection(
            grid, word, z, y, x,
            0, -1, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                0, 1, -1, 0, size
            );
        }
    }
    else if (direction == 5)
    {
        found = searchDirection(
            grid, word, z, y, x,
            1, 0, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                -1, 0, -1, 0, size
            );
        }
    }
    else if (direction == 6)
    {
        found = searchDirection(
            grid, word, z, y, x,
            -1, 0, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                1, 0, -1, 0, size
            );
        }
    }
    else if (direction == 7)
    {
        found = searchDirection(
            grid, word, z, y, x,
            1, 1, 0, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                -1, -1, 0, 0, size
            );
        }
    }
    else if (direction == 8)
    {
        found = searchDirection(
            grid, word, z, y, x,
            -1, 1, 0, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                1, -1, 0, 0, size
            );
        }
    }
    else if (direction == 9)
    {
        found = searchDirection(
            grid, word, z, y, x,
            1, 1, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                -1, -1, -1, 0, size
            );
        }
    }
    else if (direction == 10)
    {
        found = searchDirection(
            grid, word, z, y, x,
            -1, 1, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                1, -1, -1, 0, size
            );
        }
    }
    else if (direction == 11)
    {
        found = searchDirection(
            grid, word, z, y, x,
            1, -1, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                -1, 1, -1, 0, size
            );
        }
    }
    else if (direction == 12)
    {
        found = searchDirection(
            grid, word, z, y, x,
            -1, -1, 1, 0, size
        );

        if (!found)
        {
            found = searchDirection(
                grid, word, z, y, x,
                1, 1, -1, 0, size
            );
        }
    }

    if (found)
    {
        direction = 0;
        return true;
    }

    direction++;

    return searchDirections(
        grid,
        word,
        z,
        y,
        x,
        size
    );
}
void searchCells(
    char*** grid,
    const char* word,
    int z,
    int y,
    int x,
    int size
)
{
    if (z == size)
    {
        return;
    }

    if (searchDirections(grid, word, z, y, x, size))
    {
        cout << "==========================================" << endl;
        cout << "              WORD MATCH REPORTED" << endl;
        cout << "==========================================" << endl;

        cout << "Word Found           : " << word << endl;

        cout << "Starting Coordinate  : ("
            << z << ", "
            << y << ", "
            << x << ")" << endl;

        if (searchDirection(grid, word, z, y, x,
            0, 0, 1, 0, size))
        {
            cout << "Direction Name       : X Axis Forward" << endl;
            cout << "Movement Vector      : (dz=0, dy=0, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            0, 0, -1, 0, size))
        {
            cout << "Direction Name       : X Axis Reverse" << endl;
            cout << "Movement Vector      : (dz=0, dy=0, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            0, 1, 0, 0, size))
        {
            cout << "Direction Name       : Y Axis Forward" << endl;
            cout << "Movement Vector      : (dz=0, dy=+1, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            0, -1, 0, 0, size))
        {
            cout << "Direction Name       : Y Axis Reverse" << endl;
            cout << "Movement Vector      : (dz=0, dy=-1, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, 0, 0, 0, size))
        {
            cout << "Direction Name       : Z Axis Forward" << endl;
            cout << "Movement Vector      : (dz=+1, dy=0, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, 0, 0, 0, size))
        {
            cout << "Direction Name       : Z Axis Reverse" << endl;
            cout << "Movement Vector      : (dz=-1, dy=0, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            0, 1, 1, 0, size))
        {
            cout << "Direction Name       : XY Diagonal 1 Forward" << endl;
            cout << "Movement Vector      : (dz=0, dy=+1, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            0, -1, -1, 0, size))
        {
            cout << "Direction Name       : XY Diagonal 1 Reverse" << endl;
            cout << "Movement Vector      : (dz=0, dy=-1, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            0, -1, 1, 0, size))
        {
            cout << "Direction Name       : XY Diagonal 2 Forward" << endl;
            cout << "Movement Vector      : (dz=0, dy=-1, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            0, 1, -1, 0, size))
        {
            cout << "Direction Name       : XY Diagonal 2 Reverse" << endl;
            cout << "Movement Vector      : (dz=0, dy=+1, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, 0, 1, 0, size))
        {
            cout << "Direction Name       : XZ Diagonal 1 Forward" << endl;
            cout << "Movement Vector      : (dz=+1, dy=0, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, 0, -1, 0, size))
        {
            cout << "Direction Name       : XZ Diagonal 1 Reverse" << endl;
            cout << "Movement Vector      : (dz=-1, dy=0, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, 0, 1, 0, size))
        {
            cout << "Direction Name       : XZ Diagonal 2 Forward" << endl;
            cout << "Movement Vector      : (dz=-1, dy=0, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, 0, -1, 0, size))
        {
            cout << "Direction Name       : XZ Diagonal 2 Reverse" << endl;
            cout << "Movement Vector      : (dz=+1, dy=0, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, 1, 0, 0, size))
        {
            cout << "Direction Name       : YZ Diagonal 1 Forward" << endl;
            cout << "Movement Vector      : (dz=+1, dy=+1, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, -1, 0, 0, size))
        {
            cout << "Direction Name       : YZ Diagonal 1 Reverse" << endl;
            cout << "Movement Vector      : (dz=-1, dy=-1, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, 1, 0, 0, size))
        {
            cout << "Direction Name       : YZ Diagonal 2 Forward" << endl;
            cout << "Movement Vector      : (dz=-1, dy=+1, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, -1, 0, 0, size))
        {
            cout << "Direction Name       : YZ Diagonal 2 Reverse" << endl;
            cout << "Movement Vector      : (dz=+1, dy=-1, dx=0)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, 1, 1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 1 Forward" << endl;
            cout << "Movement Vector      : (dz=+1, dy=+1, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, -1, -1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 1 Reverse" << endl;
            cout << "Movement Vector      : (dz=-1, dy=-1, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, 1, 1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 2 Forward" << endl;
            cout << "Movement Vector      : (dz=-1, dy=+1, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, -1, -1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 2 Reverse" << endl;
            cout << "Movement Vector      : (dz=+1, dy=-1, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, -1, 1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 3 Forward" << endl;
            cout << "Movement Vector      : (dz=+1, dy=-1, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, 1, -1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 3 Reverse" << endl;
            cout << "Movement Vector      : (dz=-1, dy=+1, dx=-1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            -1, -1, 1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 4 Forward" << endl;
            cout << "Movement Vector      : (dz=-1, dy=-1, dx=+1)" << endl;
        }
        else if (searchDirection(grid, word, z, y, x,
            1, 1, -1, 0, size))
        {
            cout << "Direction Name       : XYZ Diagonal 4 Reverse" << endl;
            cout << "Movement Vector      : (dz=+1, dy=+1, dx=-1)" << endl;
        }

        cout << "==========================================" << endl;
    }

    if (x + 1 < size)
    {
        searchCells(grid, word, z, y, x + 1, size);
    }
    else if (y + 1 < size)
    {
        searchCells(grid, word, z, y + 1, 0, size);
    }
    else
    {
        searchCells(grid, word, z + 1, 0, 0, size);
    }
}



int main()
{
    int size;

    cout << "==========================================" << endl;
    cout << "          3D WORD SEARCH PUZZLE" << endl;
    cout << "==========================================" << endl;

    cout << "Enter grid size: ";
    cin >> size;

    if (size <= 0)
    {
        cout << "Invalid grid size." << endl;
        return 0;
    }

    char*** grid = createGrid(size);

    initializeGrid(grid, 0, 0, 0, size);

    cout << endl;
    cout << "==========================================" << endl;
    cout << "              3D GRID" << endl;
    cout << "==========================================" << endl;

    displayLayers(grid, 0, size);

    cout << endl;
    cout << "==========================================" << endl;
    cout << "             WORD SEARCH" << endl;
    cout << "==========================================" << endl;

    cout << endl;
    cout << "Searching for CODE..." << endl;
    searchCells(grid, "CODE", 0, 0, 0, size);

    cout << endl;
    cout << "Searching for CPLUS..." << endl;
    searchCells(grid, "CPLUS", 0, 0, 0, size);

    cout << endl;
    cout << "Searching for ARRAY..." << endl;
    searchCells(grid, "ARRAY", 0, 0, 0, size);

    cout << endl;
    cout << "Searching for SEARCH..." << endl;
    searchCells(grid, "SEARCH", 0, 0, 0, size);

    deleteGrid(grid, 0, size);

    delete[] grid;

    cout << endl;
    cout << "==========================================" << endl;
    cout << "       PROGRAM COMPLETED SUCCESSFULLY" << endl;
    cout << "==========================================" << endl;

    return 0;
}