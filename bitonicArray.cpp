#include <iostream>
using namespace std;

int comparisons = 0, swaps = 0;

void bubbleSortAsc(int arr[], int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = start; j < end - (i - start); j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

void selectionSortDesc(int arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        int maxIdx = i;
        for (int j = i + 1; j <= end; j++) {
            comparisons++;
            if (arr[j] > arr[maxIdx])
                maxIdx = j;
        }
        if (maxIdx != i) {
            swap(arr[i], arr[maxIdx]);
            swaps++;
        }
    }
}

int findMaxIndex(int arr[], int n) {
    int maxIdx = 0;
    for (int i = 1; i < n; i++) {
        comparisons++;
        if (arr[i] > arr[maxIdx])
            maxIdx = i;
    }
    return maxIdx;
}

void makeBitonic(int arr[], int n) {

    int BITONIC_POINT = findMaxIndex(arr, n);
    int mid = n / 2;
    swap(arr[BITONIC_POINT], arr[mid]);
    swaps++;

    bubbleSortAsc(arr, 0, mid - 1);
    selectionSortDesc(arr, mid + 1, n - 1);
}

int linearSearch(int arr[], int n, int target) {
    int search = 0;

    for (int i = 0; i < n; i++) {
        search++;
        if (arr[i] == target) {
            cout << "Search count : " << search << endl;
            return i;
        }
    }
    cout << "Search count : " << search << endl;

    return -1;
}
void printArray(int arr[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "]" << endl;
}

void testCase(int arr[], int n, int target) {
    comparisons = 0;
    swaps = 0;

    printArray(arr, n);

    makeBitonic(arr, n);

    cout << "Bitonic:  ";
    printArray(arr, n);

    cout << "Sorting comparisons: " << comparisons
         << ", swaps: " << swaps << endl;

    cout << "Searching for: " << target << endl;

    int result = linearSearch(arr, n, target);

    if (result != -1)
        cout << "Found at index: " << result << endl;
    else
        cout << "Not found!" << endl;
}

int main() {

    int a1[] = {3, 1, 8, 6, 4, 10, 2, 7, 5};
    cout << "\n--- Target at bitonic point ---\n";
    testCase(a1, 9, 10);

    int a2[] = {5, 2, 9, 7, 1};
    cout << "\n--- Target in left half ---\n";
    testCase(a2, 5, 2);

    int a3[] = {9, 7, 5, 3, 1,12,2,4};
    cout << "\n--- Target in right half ---\n";
    testCase(a3, 8, 1);

    int a4[] = {8, 1, 14, 7, 10, 2, 13, 5, 11, 6};
    cout << "\n--- Target not found ---\n";
    testCase(a4, 10, 4);

    int a5[] = {3, 3, 2, 7, 7};
    cout << "\n--- Duplicates ---\n";
    testCase(a5, 5, 3);

    return 0;
}
