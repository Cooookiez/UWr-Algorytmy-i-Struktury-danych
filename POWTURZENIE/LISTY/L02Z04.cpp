#include <iostream>
#include <cstdlib>

using namespace std;

int por = 0;

int maks_a(int t[], int n) {
    int x=t[--n];
    while(n--) {
        if(t[n]<x) {
            x=t[n]; 
        }
        por++;
    }
    return x;
}

int maks_b(int t[], int n) {
    if (n == 1) {
        return t[0];
    }
    por++;
    int m = maks_b(t, n-1);
    if (m > t[n-1]) {
        return m;
    }
    else {
        return t[n-1];
    }
}

int maks_c(int t[], int l, int r) {
    int n = r - l;
    if (n == 1) {
        return t[l];
    }
    int k = n/2+l;
    int m1 = maks_c(t, l, k);
    int m2 = maks_c(t, k, r);
    por++;
    return (m1 > m2? m1 : m2);
}

int main() {

    por = 0;
    const int n = 1024;
    int t[n];
    int x = maks_c(t, 0, n);
    int y = por;

    return 0;
}