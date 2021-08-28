#include <iostream>
#include <cstdlib>

using namespace std;

struct lnode {
    int key;
    lnode *next;
    lnode(int key0,lnode* next0=nullptr):key(key0),next(next0){}
};

void rek_wypisz(lnode* L) {
    if (L == nullptr) {
        return;
    }
    cout << L->key << " ";
    rek_wypisz(L->next);
}

int rek_suma(lnode* L) {
    if (L == nullptr) {
        return 0;
    }
    return L->key + rek_suma(L->next);
}

int rek_nty(int n, lnode* L) {
    if (L == nullptr) {
        return 0;
    }
    if (n == 1) {
        return L->key;
    }
    return rek_nty(n-1, L->next);
}

void rek_insert_after_smaller(lnode* &L, int x) {
    if (L == nullptr) {
        return;
    }
    if (L->key < x) {
        lnode* l = new lnode(x, L->next);
        L->next = l;
    }
    rek_insert_after_smaller(L->next, x);
}
//*
void rek_remove(lnode* &L, int x) {  // zalozenie ze 1 element nie jest X
    if (L == nullptr || L ->next == nullptr) {
        return;
    }
    if (L->next->key == x) {
        lnode* tmp = L->next->next;
        delete L->next;
        L->next = tmp;
        rek_remove(L, x);
    }
    else {
        rek_remove(L->next, x);
    }
}

void rek_remove2(lnode* &L, int x) {  // TODO czy to dziala jesli pierwszy element to x
    if (L == nullptr) {
        return;
    }
    if (L->key == x) {
        lnode* tmp = L->next;
        delete L;
        L = tmp;
        rek_remove(L, x);
    }
    else {
        rek_remove(L->next, x);
    }
}

void rek_destroy(lnode* &L) {
    if (L == nullptr) {
        return;
    }
    rek_destroy(L->next);
    delete L;
}

void rek_reverse(lnode* &L) {
    L = rek_reverse_aux(L);
}

lnode* rek_reverse_aux(lnode* L) {
    if (L->next == nullptr) {
        return L;
    }
    lnode* P = rek_reverse_aux(L->next);
    L->next->next = L;
    return P;
}

void ite_wypisz(lnode* L) {
    while (L != nullptr) {
        cout << L->key << " ";
        L = L->next;
    }
}

int ite_suma(lnode* L) {
    int s = 0;
    while (L != nullptr) {
        s += L->key;
        L = L->next;
    }
    return s;
}

int ite_nty(int n, lnode* L) {
    for (int i = 1; i < n; i++) {
        if (L->next == nullptr) {
            return 0;
        }
        L = L->next;
    }
    return L->key;
}

void ite_insert(lnode* &L, int x) {
    lnode* tmp = new lnode(x, L);
    L = tmp;
}

void ite_insert_after_smaller(lnode* &L, int x) {
    lnode* it = L;
    while (it != nullptr ) {
        if (it->key < x) {
            it->next = new lnode(x, it->next);
            it = it -> next; // opcjonalnie
        }
        it = it->next;
    }
}

int ite_remove(lnode* &L, int x) {
    lnode* tmp;
    while (L != nullptr && L->key == x) {
        tmp = L->next;
        delete L;
        L = tmp;;
    }
    lnode* it = L;

    while (it != nullptr && it->next != nullptr) {
        if (it->next->key == x) {
            tmp = it->next->next;
            delete it->next;
            it->next = tmp;
        }
        it = it->next;
    }
}

void ite_destroy(lnode* &L, int x) {
    lnode* tmp;
    while (L->next != nullptr) {
        tmp = L->next;
        delete L;
        L = tmp;
    }
    delete L;
}

void ite_reverse(lnode* &L) {
    lnode* prev = nullptr;
    lnode* act = L;
    lnode* next;
    while (act != nullptr) {
        next = act->next;
        act->next = prev;
        
        prev = act;
        act = next;
    }
    L = prev;
}

int main() {

    lnode* L = new lnode(7, nullptr);

    ite_wypisz(L);

    return 0;
}