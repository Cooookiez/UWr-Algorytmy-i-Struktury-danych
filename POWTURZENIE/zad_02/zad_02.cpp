#include <iostream>
#include <cstdlib>

using namespace std;

struct node{ 
    int x; 
    node* left; 
    node* right; 
};

void remove_min(node*& T) {
    node* tmp_p = T;
    node* tmp_n = T->left;

    if(tmp_n != nullptr) {
        while (tmp_n->left != nullptr) {
            tmp_p = tmp_n;
            tmp_n = tmp_n->left;
        }
        tmp_p->left = tmp_n->right;
        delete(tmp_n);
    } else {
        T = T->right;
        delete(tmp_p);
    }

}

int even_minus_odd(node* T) {
    if(T == nullptr) return 0;

    int wartosc;
    if (T->x % 2 == 0) {
        wartosc = 1;
    } else {
        wartosc = -1;
    }
    
    return wartosc + even_minus_odd(T->left) + even_minus_odd(T->right);
}

void show(node* T) {
    if (T == nullptr) {
        return;
    }

    show(T->left);
    cout << T -> x << " ";
    show(T->right);
}

int main() {
    node* root = new node();
    root -> x = 10;

    node* node1 = new node();//{5, nullptr, nullptr};
    node1->x = 5;
    node1->left = nullptr;
    node1->right = nullptr;
    node* node2 = new node();//{12, nullptr, nullptr};
    node2 -> x = 12;
    node2->left = nullptr;
    node2->right = nullptr;
    node* node3 = new node();//{6, nullptr, nullptr};
    node3->x = 6;
    node3->left = nullptr;
    node3->right = nullptr;

    root->left = node1;
    root->right = node2;

    node1->right = node3;

    show(root);
    cout << endl;
    int x = even_minus_odd(root);
    //remove_min(root);
    show(root);
    cout << endl;
    cout << x << endl;
    return 0;
}