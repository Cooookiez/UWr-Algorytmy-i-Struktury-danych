#include <iostream>
#include <cstdlib>

using namespace std;

struct BSTnode {
    int key;
    BSTnode* left;
    BSTnode* right;
    int nL;
    BSTnode(
        int key,
        BSTnode* left = nullptr,
        BSTnode* right = nullptr,
        int nL = 0
    ):
        key(key),
        left(left),
        right(right),
        nL(nL)
    {}
};

BSTnode* ity(BSTnode* t, int i) {
    while(t != nullptr) {
        if (t->nL > i) {
            t = t->left;
        } else if (t->nL == i) {
            return t;
        } else {
            i -= (t->nL + 1);
            t = t->right;
        }
    }
    return nullptr;
}

int main() {

    

    return 0;
}