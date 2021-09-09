#include <iostream>
#include <cstdlib>

using namespace std;

struct BSTnode {
    int key;
    BSTnode* left;
    BSTnode* right;
    BSTnode(int key, BSTnode* left = nullptr, BSTnode* right = nullptr) : key(key), left(left), right(right){}
};

int suma_do_poziomu(BSTnode* t, int poziom) {
    if (poziom == 0 || t == nullptr) {
        return 0;
    }
    return suma_do_poziomu(t->left, poziom-1) + t->key + suma_do_poziomu(t->right, poziom-1);
}

int main() {



    return 0;
}