#include <iostream>

using namespace std;

double oblicz(double a[], int n, double x) {
    if (n == 0) {
        return a[0];
    } else {
        return x * oblicz(a, n-1, x) + a[n];
    }
}

int main()
{
    const int ROZMIAR = 3;
    double a[ROZMIAR + 1] ={1, 4, 3, 6};
    
    cout << oblicz(a, ROZMIAR, 5) << endl;

    return 0;
}