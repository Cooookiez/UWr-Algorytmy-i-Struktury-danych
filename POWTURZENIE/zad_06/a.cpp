#include <iostream>
#include <cstdlib>

using namespace std;

void counting_sort(int t[], int n, int m) {
    int ttmp[m];
    for (int i = 0; i < m; i++) { // m
        ttmp[i] = 0;
    }

    for (int i = 0; i < n; i++) { // n
        ttmp[t[i]]++;
    }

    int tn = 0;
    for (int i = 0; i < m; i++) { 
        for (int j = 0; j < ttmp[i]; j++) {
            t[tn++] = i;  // n
        }
    }
}

void print(int t1[], int n1) {
    for (int i = 0; i < n1; i++) {
        cout << t1[i] << ", ";
    }
    cout << endl;
}

int main() {

    int n = 6;
    int t[] = {5, 6, 2, 8, 2, 10};
    int m = 10;

    print(t, n);
    counting_sort(t, n, m);
    print(t, n);

    return 0;
}