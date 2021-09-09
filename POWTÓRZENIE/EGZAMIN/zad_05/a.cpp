
#include <iostream>
#include <cstdlib>

using namespace std;

void merge(double t1[], int n1, double t2[], int n2, double t3[]) {
    int i1 = 0, i2 = 0, i3 = 0;

    while (i1 < n1 && i2 < n2) {
        if (t1[i1] > t2[i2]) {
            t3[i3++] = t2[i2++];
        } else {
            t3[i3++] = t1[i1++];
        }
    }

    while (i1 < n1) {
        t3[i3++] = t1[i1++];
    }

    while (i2 < n2) {
        t3[i3++] = t2[i2++];
    }
}

void print(double t1[], int n1) {
    for (int i = 0; i < n1; i++) {
        cout << t1[i] << ", ";
    }
    cout << endl;
}

int main() {

    const int n1 = 5;
    const int n2 = 7;
    double t1[n1] = {5, 6, 10, 12, 20};
    double t2[n2] = {1, 5, 7, 12, 16, 18, 22};
    double t3[n1+n2];

    merge(t1, n1, t2, n2, t3);

    print(t1, n1);
    print(t2, n2);
    print(t3, n1+n2);


    return 0;
}