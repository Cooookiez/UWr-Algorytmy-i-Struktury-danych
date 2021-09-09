#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>


using namespace std;

void counting_sort(int t[], int n, int c) {

    vector<int> tmp[10];

    for (int i = 0; i < n; i++) {
        int tmpi = int(t[i] / pow(10, c)) % 10;
        tmp[tmpi].push_back(t[i]);
    }

    int tIndex = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < tmp[i].size(); j++) {
            t[tIndex++] = tmp[i][j];
        }
    }

}

int main() {

    const int n = 4;
    int t[n] = {3, 5, 10, 2};


    return 0;
}

/*

435353

x / 10^c % 10

*/