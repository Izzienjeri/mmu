#include <iostream>
using namespace std;
// Function to perform Bubble Sort in descending order
void bubbleSortDescending(int arr[], int n) {
for (int i = 0; i < n-1; i++) {
Page 108 of 122
Compiled: Wairagu G.Rbool swapped = false;
// Last i elements are already sorted
for (int j = 0; j < n-i-1; j++) {
if (arr[j] < arr[j+1]) {
// Swap if the current element is smaller than the next one
int temp = arr[j];
arr[j] = arr[j+1];
arr[j+1] = temp;
swapped = true;
}
}
// If no two elements were swapped, break the loop
if (!swapped) break;
}
}
// Function to display the array
void displayArray(int arr[], int n) {
for (int i = 0; i < n; i++) {
cout << arr[i] << " ";
}
cout << endl;
}
int main() {
const int SIZE = 10;
int arr[SIZE];
// Prompting user to enter 10 values
cout << "Enter 10 values:" << endl;
Page 109 of 122
Compiled: Wairagu G.Rfor (int i = 0; i < SIZE; i++) {
cout<< "Enter value in cell :" <<i<< "\n";
cin >> arr[i];
}
// Display values before sorting
cout << "Array before sorting: ";
displayArray(arr, SIZE);
// Sort the array in descending order using Bubble Sort
bubbleSortDescending(arr, SIZE);
// Display values after sorting
cout << "Array after sorting in descending order: ";
displayArray(arr, SIZE);
return 0;
}