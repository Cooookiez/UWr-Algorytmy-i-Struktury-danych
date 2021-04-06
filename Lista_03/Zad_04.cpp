#include <iostream>

using namespace std;

struct node
{
    int key;
    node* next;

    node(int k, node* n) :key(k), next(n) {}
};

typedef node* list;

void push(list& l, int k) { // wkładanie na początek listy
    l = new node(k, l);
}

void wypisz(list l)
{
    for (; l; l = l->next)
        cout << l->key << " ";
    cout << endl;
}

void my_insert_sort(list& L, int size) {
    list l2 = L;
    for (int i = 0; i < size; i++) {
        
    }
}

int main() {
    list l1 = nullptr;
    int wielkosc = 0;
    push(l1, 6); wielkosc++;
    push(l1, 2); wielkosc++;
    push(l1, 6); wielkosc++;
    push(l1, 7); wielkosc++;
    push(l1, 9); wielkosc++;
    push(l1, 4); wielkosc++;
    push(l1, 1); wielkosc++;
    push(l1, 3); wielkosc++;
    push(l1, 8); wielkosc++;
    push(l1, 3); wielkosc++;
    push(l1, 9); wielkosc++;
    push(l1, 3); wielkosc++;
    push(l1, 5); wielkosc++;
    push(l1, 7); wielkosc++;
    wypisz(l1);
    my_insert_sort(l1, wielkosc);
    wypisz(l1);

    return 0;
}