#include <iostream>
#include "zad_04.h"
#include <set>

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

    bool t[n][n] = {
        {1, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0},
        {1, 1, 1, 0, 1, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 1}
    };
    UnionFind3 uf3(n*n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(t[i][j] == 1) {
                k1 = nth(i, j, n);
                if (i > 0 && t[i-1][j] == 1) {
                    k2 = nth(i-1, j, n);
                    uf3.Union(k1, k2);
                }
                if (j > 0 && t[i][j-1] == 1) {
                    k2 = nth(i, j-1, n);
                    uf3.Union(k1, k2);
                }
            }
        }
    }
    uf3.Print();
    cout << endl;
    printTab(t, n);

    set<int> island;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(t[i][j] == 1) {
                int k = nth(i, j, n);
                int top = uf3.Find(k);
                island.insert(top);
            }
        }
    }

    cout << "wyspy " << island.size() << endl;

    uf3.Print();
    cout << endl;
    printTab(t, n);



    return 0;
}