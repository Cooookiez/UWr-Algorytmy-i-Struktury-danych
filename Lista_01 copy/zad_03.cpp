#include <iostream>

using namespace std;

//* wyciągamy x przed nawias

double oblicz(double a[], int n, double x) {
    if (n == 0) {
        return a[0];
    } else {
        return x * oblicz(a, n-1, x) + a[n];
    }
}

int main() {
    double a[] = {1, 4, 3, 6};
    int a_size = sizeof(a) / sizeof(double);
    
    cout << oblicz(a, a_size-1, 5) << endl;

    return 0;
}