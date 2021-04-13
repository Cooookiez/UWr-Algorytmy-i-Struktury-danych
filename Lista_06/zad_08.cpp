#include <iostream>

using namespace std;


int partitionAux(int t[], int low, int hi) {
    if (low >= hi) {
        return low;
    }
    
    int pi = low;
    int i = low+1;
    int j = hi;

    while(i <= j) {
        while (i <= j && t[i] <= t[pi]) i++;
        while (i <= j && t[j] >= t[pi]) j--;

        if (i <= j)
        {
            swap(t[i], t[j]);
        }
        else 
            break;
    }
    swap(t[j], t[pi]);
    return j;
}

int partition(int t[], int n) {
    return partitionAux(t, 0, n-1);
}

void quicksort(int t[], int n, int low, int hi) {
    int m = partition(t, n);
    quicksort(t, n, 0, m-1);
    quicksort(t, n, m+1, n-1);
}

int ktyAux(int t[], int k, int low, int hi);

int kty(int t[], int k, int n) {
    return ktyAux(t, k, 0, n-1);
}

int ktyAux(int t[], int k, int low, int hi) {
    int m = partitionAux(t, low, hi);
    if (k == m) {
        return t[k];
    } else if (k < m) {
        return ktyAux(t, k, low, m-1);
    } else {
        return ktyAux(t, k, m+1, hi);
    }
}

int main() {

    // int tab[] = {1, 5, 6, 3, 7, 9, 3, 7, 3, 8, 1};
    int tab[] = {3, 5, 2, 4, 1};
    int n = sizeof(tab)/sizeof(tab[0]);

    partition(tab, n);
    for(int i=0; i<n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;
    cout << kty(tab, 3, n) << endl;
    return 0;
}