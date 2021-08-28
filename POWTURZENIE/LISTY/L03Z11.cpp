#include <iostream>
#include <cstdlib>

using namespace std;

struct BSTnode {
    int key;
    BSTnode* left;
    BSTnode* right;
    BSTnode(int key, BSTnode* left = nullptr, BSTnode* right = nullptr) : key(key), left(left), right(right){}
};

int poziom(BSTnode* t, int klucz) {
    BSTnode* tmp = t;
    int level = 0;
    while (tmp != nullptr) {
        level++;
        if (tmp->key == klucz) {
            return level;
        } else if (tmp->key > klucz) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
    }
    return 0;
}

int main() {



    return 0;
}