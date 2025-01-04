#include <iostream>

using namespace std;

int main() {
    int Numbers[10], i, big;

    cout << "We are illustrating arrays" << endl;
    cout << "*** Assign values ***" << endl;

    for (i = 0; i < 10; i++) {
        cout << "Enter Number in Cell :- " << i << endl;
        cin >> Numbers[i];
    }

    cout << "Elements Entered" << endl;
    for (i = 0; i < 10; i++) {
        cout << Numbers[i] << ", "; 
    }
    cout << endl; // Add a newline after the last element

    // Get the biggest element
    big = Numbers[0]; 
    for (i = 0; i < 10; i++) {
        if (Numbers[i] > big) {
            big = Numbers[i];
        }
    }

    cout << "The Biggest number is :" << big << endl; 

    return 0;
}