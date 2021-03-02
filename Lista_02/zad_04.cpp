
#include <cstdlib>
#include <iostream>

using namespace std;

int poruwnan;

int max_a(int t[], int n) {
    int x = t[--n];
    while (n--) {
        poruwnan++;
        if (t[n] > x) {
            x = t[n];
        }
    }
    return x;
}

int max_b(int t[], int n) {
    if (n == 1) {
        return t[0];
    } else {
        int pom = max_b(t, n-1);
        poruwnan++;
        if (pom > t[n-1]) {
            return pom;
        } else {
            return t[n-1];
        }
    }
}

int max_c(int t[], int start, int end) {
    if (end - start == 0) {
        return t[start];
    } else {
        int mid = (start+end)/2;
        int p1 = max_c(t, start, mid);
        int p2 = max_c(t, mid+1, end);
        poruwnan++;
        if (p1 > p2) {
            return p1;
        } else {
            return p2;
        }
    }
}

int main() {
    
    int t[] = {1, 5, 7, 2, 7, 9, 12, 22, 12, 30};

    int max;

    cout << "n = " << sizeof(t)/sizeof(int) << endl << endl;

    // a)
    // ilosc porownan: n-1
    // pamiec: (int) * (n+2)
    poruwnan = 0;
    max = max_a(t, sizeof(t)/sizeof(int));
    cout << "max a: " << max << endl;
    cout << "poruwnan a: " << poruwnan << endl;

    // b)
    // ilosc porownan: n-1
    // pamiec: (int) * (4n + 8)
    poruwnan = 0;
    max = max_b(t, sizeof(t)/sizeof(int));
    cout << "max b: " << max << endl;
    cout << "poruwnan b: " << poruwnan << endl;

    // c)
    // ilosc porownan: n-1
    // pamiec: (int) * (3n-1)
    poruwnan = 0 ;
    max = max_c(t, 0, sizeof(t)/sizeof(int)-1);
    cout << "max c: " << max << endl;
    cout << "poruwnan c: " << poruwnan << endl;

    return 0;
}
