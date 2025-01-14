#include <iostream>
using namespace std;

int main () {
    const int size = 5;
    int arr[size];
    int searchEl, position = -1;

    cout<< "Provide 5 numbers:\n";

    for (int i = 0; i < size; i++ ) {
        cout<<"Enter number " << i + 1 << ":";
        cin>> arr[i];
    }

    cout<<"Enter the elemnt to search for: ";
    cin>> searchEl;

    for (int i = 0; i<size; i++) {
        if (arr[i] == searchEl) {
            position = i;
            break;
        }
    }

    if(position != -1) {
       cout << "Element " <<searchEl <<" found at position " << position + 1 << "(index " << position <<" )\n";
    }
    else {
        cout << "Element " <<searchEl <<" not found in the array";
    }
    return 0;


}
