#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
    int key;
    node* next;
    node(int key, node* next = nullptr) : key(key), next(next){}
};

node* shift_sorted(node* &L) {

    node* newList = L;
    node* prev = L;
    node* tmp = prev->next;
    // niezmiennik prev->next == tmp

    while (tmp != nullptr && prev->key <= tmp->key) {
        prev = tmp;
        tmp = tmp->next;
    }
    L = tmp;
    prev->next = nullptr;

    return newList;
}
/*
    0785278245
    0 7 8 | 5 2 7 ...

    54321
    5 | 4321

    12345
    12345 |
*/
int main() {



    return 0;
}