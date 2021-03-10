#include <iostream>

using namespace std;

void max_min(int a[], int n) {
    int max = a[0];
    int min = a[0];
    int ile = 0;
    for (int i = 1; i < n; i++) {
        if (min > a[i]) {
            ile++;
            min = a[i];
        } else if (max < a[i]) {
            ile++;
            max = a[i];
        }
    }
    cout << "porownan:\t" << ile << endl;
    cout << "min:\t" << min << endl;
    cout << "max:\t" << max << endl;
}

int main() {
    int a[] = {10, 8, 9, 7, 5, 6, 3, 4, 1, 2};
    int n = sizeof(a) / sizeof(int);
    cout << "n: " << n << endl;
    cout << "3n/2: " << 3 * n / 2 << endl;
    max_min(a, n);

    return 0;
}