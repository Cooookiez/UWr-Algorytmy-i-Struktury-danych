#include <iostream>
#include <cstdlib>

using namespace std;

struct lnode {
    int key;
    lnode *next;
    lnode(int key0,lnode* next0=nullptr):key(key0),next(next0){}
};

lnode* merge(lnode* L1, lnode* L2) {
    lnode* nNode;
    lnode* nNodeTmp;
    if(L1->key > L2->key) {
        nNode = L2;
        L2 = L2->next;
    } else {
        nNode = L1;
        L1 = L1->next;
    }

    nNodeTmp = nNode;
    while (L1 != nullptr && L2 != nullptr) {
        if(L1->key > L2->key) {
            nNodeTmp->next = L2;
            L2 = L2->next;
        } else {
            nNodeTmp->next = L1;
            L1 = L1->next;
        }
    }

    if (L1 != nullptr) {
        nNodeTmp->next = L1;
    } else {
        nNodeTmp->next = L2;
    }

    return nNode;
}

int main() {
    lnode* l1 = new lnode(1, nullptr);
    lnode* l2 = new lnode(1, nullptr);

    return 0;
}