#include <iostream>
using namespace std;

int main() {
  const int SIZE = 8; 
  int arr[SIZE]; 
  int sum = 0;
  float average;

  // Prompt the user to enter 8 values
  cout << "Enter 8 values: " << endl;
  for (int i = 0; i < SIZE; i++) {
    cout << "Value " << i + 1 << ": ";
    cin >> arr[i];
    sum += arr[i]; // Add each value to the sum
  }

  // Calculate the average
  average = static_cast<float>(sum) / SIZE; 

  // Display the entered values
  cout << "\nThe entered values are: ";
  for (int i = 0; i < SIZE; i++) {
    cout << arr[i] << " ";
  }

  // Display the sum and average
  cout << "\nSum of the values: " << sum;
  cout << "\nAverage of the values: " << average << endl;

  return 0;
}