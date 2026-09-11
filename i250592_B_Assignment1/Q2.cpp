#include <iostream>
using namespace std;

int* findEquilibriumIndices(int* arr, int size, int& count){
    count = 0;
    int totalSum = 0;
    for (int i = 0; i < size; i++){
        totalSum = totalSum + *(arr + i);
    }

    int leftSum = 0;
    for (int i = 0; i < size; i++){
        int current = *(arr + i);
        int rightSum = totalSum - leftSum - current;
        if (leftSum == rightSum){
            count = count + 1;
        }
        leftSum = leftSum + current;
    }
    if (count == 0){
        return nullptr;
    }

    int* result = new int[count];
    int resultIndex = 0;
    leftSum = 0;

    for (int i = 0; i < size; i++){
        int current = *(arr + i);
        int rightSum = totalSum - leftSum - current;
        if (leftSum == rightSum){
            *(result + resultIndex) = i;
            resultIndex = resultIndex + 1;
        }
        leftSum = leftSum + current;
    }
    return result;
}



int main(){
    int size;
    cout << "Enter size:";
    cin >> size;
    int* arr = new int[size];
    cout << "Enter " << size << " elements:" << endl;

    for (int i = 0; i < size; i++){
        cin >> *(arr + i);
    }
    int count = 0;

    int* result = findEquilibriumIndices(arr, size, count);

    if (result == nullptr){
        cout << "No equilibrium found " << endl;
    }
    else{
        cout << "No. of equilibrium indices: " << count << endl;
        cout << "Equilibrium indices are: ";
        for (int i = 0; i < count; i++){
            cout << *(result + i) << " ";
        }
        cout << endl;
        delete[] result;
    }
    delete[] arr;
    return 0;
}