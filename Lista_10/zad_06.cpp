
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void mnozenie(multiset<int>& parts, int* l, int n) 
{
    if (n == 0) {
        parts.insert(0);
    }
    else if (n > 0) {
        int r = l[n];
        if (r == -1) {
            parts.insert(n);
        }
        else {
            mnozenie(parts, l, r);
            mnozenie(parts, l, n-r);
        }
    }
}

int a(int* cena, int n) {
    int* w = new int[n+1];
    int* last = new int[n+1];
    w[0] = 0;
    int myMax, myTmpMax;
    for (int i = 1; i < n+1; i++) {
        myMax = cena[i];
        last[i] = -1;
        for (int r = i-1; r > 0; r--) {
            myTmpMax = w[r] + w[i-r];
            if (myMax < myTmpMax) {
                myMax = myTmpMax;
                last[i] = r;
            }
        }
        w[i] = myMax;
    }
    for (int i = 0; i < n+1; i++) {
        cout << last[i] << ", ";
    }
    cout << endl;
    int res = w[n];
    multiset<int> parts;
    mnozenie(parts, last, n);
    
    cout << endl;
    for(multiset<int>::reverse_iterator it=parts.rbegin(); it != parts.rend(); it++) {
        cout << "(" << *it << ")";
    }
    cout << endl;

    // mozesz posrotowac wektor

    cout << endl;
    delete[] w;
    delete[] last;
    return res;
}

int b(int* cena, int n, int c) {
    int* w = new int[n+1];
    int* last = new int[n+1];
    w[0] = 0;
    int myMax, myTmpMax;
    for (int i = 1; i < n+1; i++) {
        myMax = cena[i];
        last[i] = -1;
        for (int r = i-1; r > 0; r--) {
            myTmpMax = w[r] + w[i-r] - c; // <- jedyna zmiana
            if (myMax < myTmpMax) {
                myMax = myTmpMax;
                last[i] = r;
            }
        }
        w[i] = myMax;
    }
    for (int i = 0; i < n+1; i++) {
        cout << last[i] << ", ";
    }
    cout << endl;
    int res = w[n];
    multiset<int> parts;
    mnozenie(parts, last, n);
    
    cout << endl;
    for(multiset<int>::reverse_iterator it=parts.rbegin(); it != parts.rend(); it++) {
        cout << "(" << *it << ")";
    }
    cout << endl;

    // mozesz posrotowac wektor

    cout << endl;
    delete[] w;
    delete[] last;
    return res;
}

int main() {

    int cena[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24}; 
    int c = 5; 
    int n = sizeof(cena) / sizeof(cena[0])  - 1;

    cout << a(cena, n) << endl;
    cout << b(cena, n, c) << endl;
    return 0;
}