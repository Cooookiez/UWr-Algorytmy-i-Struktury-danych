
#include <iostream>

using namespace std;

struct lnode {
    int key;
    lnode *next;
    lnode(int key0, lnode* next0 = nullptr): key(key0), next(next0) {}
};

// a)
void wypisz(lnode* L) {
    lnode* l = L;
    while(l != nullptr) {
        cout << l->key << "->";
        l = l->next;
    }
    cout << "nullptr" << endl;
}

// b)
int suma(lnode* L) {
    int sum = 0;
    while(L != nullptr) {
        sum += L->key;
        L = L->next;
    }
    return sum;
}

// c)
int nty(int n, lnode* L) {
    for (int i = 0; i < n-1; i++) {
        L = L->next;
        if (L == nullptr) {
            throw "out of range";
        }
    }
    return L->key;
}

// d)
void insert(lnode* &L, int key) {
    L = new lnode(key, L);
}

// e)
void insert_after_smaller(lnode* &L, int x) {
    lnode* tmp = L;
    while (tmp != nullptr) {
        if (tmp->key < x) {
            tmp->next = new lnode(x, tmp->next);
        }
        // wypisz(tmp); cout << endl << endl; 
        tmp = tmp->next;
    }
}

// f)
void remove(lnode* &L, int x) {
    lnode* tmp = L;
    lnode* tmp2 = L;
    // while (tmp->next != nullptr) {
    //     if (tmp->next->key == x) {
    //         tmp2 = tmp->next;
    //         delete tmp->next;
    //         tmp->next = tmp2;
    //     }
    //     wypisz(tmp); cout << endl << endl; 
    //     tmp = tmp->next;
    // }
}

// g)

// h)
void destroy(lnode* &L) {
    while (L != nullptr) {
        lnode* l1 = L;
        L = L->next;
        delete l1;
    }
}

// i)

int main() {

    lnode* L = nullptr;
    // d)
    insert(L, 8);
    insert(L, 14);
    insert(L, 9);
    insert(L, 12);
    insert(L, 32);

    cout << endl;

    // a)
    cout << "wypisz: ";
    wypisz(L);
    cout << endl;

    // b)
    cout << "suma: " << suma(L) << endl << endl;

    // c)
    cout << "nty (2): " << nty(2, L) << endl << endl;

    //e)
    insert_after_smaller(L, 10);
    cout << "insert_after_smaller (10): ";
    wypisz(L);
    cout << endl;

    // f)
    // remove(L, 10);
    // cout << "remove (10): ";
    // wypisz(L);
    // cout << endl;

    // i)

    // h)
    destroy(L);
    cout << "destroy: ";
    wypisz(L);
    cout << endl;


    return 0;
}