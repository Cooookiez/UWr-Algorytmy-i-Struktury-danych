#include <iostream>
#include <cstdlib>

using namespace std;

struct lnode { int key; lnode* next; };

int get_first(lnode* &L) {
    int toReturn = L->key;
    L = L->next;
    return toReturn;
}

int increment_x(lnode* L,int x) {
    lnode* tmp = L;
    int ile = 0;
    while (tmp != nullptr) {
        if (tmp->key == x) {
            tmp->key++;
            ile++;
        }
        tmp = tmp->next;
    }
    return ile;
}

void show(lnode* &L) {
    lnode* tmp = L;
    while(tmp != nullptr) {
        cout << tmp->key << ", ";
        tmp = tmp->next;
    }
    cout << endl;
}

int main() {

    lnode* node1 = new lnode();
    lnode* node2 = new lnode();
    lnode* node3 = new lnode();

    node1->key = 5;
    node1->next = node2;

    node2->key = 7;
    node2->next = node3;

    node3->key = 7;
    node3->next = nullptr;

    show(node1);
    // int x = get_first(node1);
    int x = increment_x(node1, 7);
    show(node1);
    cout << x << endl;

    return 0;
}