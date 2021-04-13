#include <iostream>
#include <vector>

using namespace std;

// a)

// [30, 12, 21, 11]

// 0 -> [30]
// 1 -> [21, 11]
// 2 -> [12]

// ...
// 9 -> []

// [30, 21, 11, 12]
void counting_sort(int t[], int n, int c) {
    vector<int> vec[10];
    int num;
    for (int i = 0; i < n; i++) {
        num = (int)(t[i] / pow(10, c)) % 10;
        vec[num].push_back(t[i]);
    }

    int ti = 0;
    for (int i = 0; i < 10; i++) {
        for(int j=0; j<vec[i].size(); j++) {
            t[ti++] = vec[i][j];
        }
    }
}

void print_t(int t[], int n) {
    for (int i = 0; i < n; i++) {
        cout << t[i];
        if (i != n-1)
            cout << ", ";
    }
    cout << endl;
}

int main() {

    int t[] = {101, 345, 103, 333, 432, 132, 543, 651, 791, 532, 987, 910, 643, 641, 12, 342, 498, 987, 965, 322, 121, 431, 350};
    int n = sizeof(t) / sizeof(int);
    print_t(t, n);
    counting_sort(t, n, 0);
    print_t(t, n);
    counting_sort(t, n, 1);
    print_t(t, n);
    counting_sort(t, n, 2);
    print_t(t, n);

    return 0;
}

