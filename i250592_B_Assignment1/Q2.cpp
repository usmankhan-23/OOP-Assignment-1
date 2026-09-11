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




int balanceValue(int* arr, int size) {
    int count = 0;
    int* equilibriumIndices = findEquilibriumIndices(arr, size, count);
    if (count == 0) {
        return 0;
    }
    int firstEquilibrium = *(equilibriumIndices + 0);
    int lastEquilibrium = *(equilibriumIndices + count - 1);
    int sumBeforeFirst = 0;

    for (int i = 0; i < firstEquilibrium; i++) {
        sumBeforeFirst = sumBeforeFirst + *(arr + i);
    }
    int sumAfterLast = 0;
    for (int i = lastEquilibrium + 1; i < size; i++){
        sumAfterLast = sumAfterLast + *(arr + i);
    }
    int balance = sumBeforeFirst + sumAfterLast;
    delete[] equilibriumIndices;
    return balance;
}




int* createBalancedArray(int* arr, int size, int& newSize){
    int count = 0;
    int* equilibriumIndices = findEquilibriumIndices(arr, size, count);

    if (count == 0){
        newSize = 0;
        return nullptr;
    }
    int firstEquilibrium = *(equilibriumIndices + 0);
    int lastEquilibrium = *(equilibriumIndices + count - 1);
    newSize = firstEquilibrium + (size - lastEquilibrium - 1);
    
    if (newSize == 0){
        delete[] equilibriumIndices;
        return nullptr;
    }
    int* balancedArray = new int[newSize];
    for (int i = 0; i < firstEquilibrium; i++){
        *(balancedArray + i) = *(arr + i);
    }
    int newIndex = firstEquilibrium;
    for (int i = lastEquilibrium + 1; i < size; i++){
        *(balancedArray + newIndex) = *(arr + i);
        newIndex = newIndex + 1;
    }
    delete[] equilibriumIndices;
    return balancedArray;
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
    int balance = balanceValue(arr, size);
    cout << "Balance value: " << balance << endl;

    int newSize = 0;
    int* balancedArray = createBalancedArray(arr, size, newSize);
    if (balancedArray == nullptr){
        cout << "Balanced array is empty" << endl;
    }
    else{
        cout << "balanced array: ";
        for (int i = 0; i < newSize; i++){
            cout << *(balancedArray + i) << " ";
        }
        cout << endl;
        delete[] balancedArray;
    }
    delete[] arr;
    return 0;
}