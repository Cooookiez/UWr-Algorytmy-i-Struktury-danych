#include <iostream>
#include "zad_04.h"

using namespace std;

void printTab(bool t[6][6], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int nth(int i, int j, int n) {
    return i * n + j;
}

int main() {
    const int n = 6;
    int k1, k2;

    // a)
    bool t_a[n][n] = {
        {1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 0, 1},
        {0, 0, 0, 0, 1, 1},
        {1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1, 1}
    };
    UnionFind3 uf3(n*n);
    printTab(t_a, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(t_a[i][j] == 1) {
                k1 = nth(i, j, n);
                if (i > 0 && t_a[i-1][j] == 1) {
                    k2 = nth(i-1, j, n);
                    uf3.Union(k1, k2);
                }
                if (j > 0 && t_a[i][j-1] == 1) {
                    k2 = nth(i, j-1, n);
                    uf3.Union(k1, k2);
                }
            }
        }
    }

    if (uf3.Find(0) == uf3.Find(n*n-1)) {
        cout << "a znaleziono!" << endl;
    } else {
        cout << "a NIE znaleziono!" << endl;
    }

    uf3.Print();
    cout << endl;


    // b)
    UnionFind3 uf3b(n*n + 2);
    bool t_b[n][n] = {
        {1, 0, 0, 0, 1, 1},
        {0, 1, 1, 1, 0, 1},
        {0, 0, 0, 0, 1, 1},
        {1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(t_b[i][j] == 1) {
                k1 = nth(i, j, n);
                if (i > 0 && t_b[i-1][j] == 1) {
                    k2 = nth(i-1, j, n);
                    uf3b.Union(k1, k2);
                }
                if (j > 0 && t_b[i][j-1] == 1) {
                    k2 = nth(i, j-1, n);
                    uf3b.Union(k1, k2);
                }
            }
        }
    }

    // asign first and last row to 2 cells
    for (int i = 0; i < n; i++) {
        if (t_b[0][i] == 1) {
            uf3b.Union(i, n*n);
        }
        if (t_b[n-1][i] == 1) {
            uf3b.Union(nth(n-1, i, n), n*n+1);
        }
    }

    if (uf3b.Find(n*n+1) == uf3b.Find(n*n)) {
        cout << "b znaleziono!" << endl;
    } else {
        cout << "b NIE znaleziono!" << endl;
    }
    uf3b.Print();
    cout << endl;

    return 0;
}