#include <iostream>

using namespace std;

// Podstawowa struktura listy jednokierunkowej

struct node
{
    int key;
    node* next;

    node(int k, node* n) :key(k), next(n) {}
};

typedef node* list;

void push(list& l, int k) // wkładanie na początek listy
{
    l = new node(k, l);
}

int pop(list& l) // wyciąganie pierwszego
{
    list tmp = l;
    int res = l->key;
    l = l->next;
    delete tmp;
    return res;
}

bool empty(list l) // sprawdzanie czy lista jest pusta
{
    return l == NULL;
}

void destroy(list& l) //usuwa wszystkie elementy z listy  
{
    while (l)
    {
        list l1 = l;
        l = l->next;
        delete l1;
    }
}

void wypisz(list l)
{
    for (; l; l = l->next)
        cout << l->key << " ";
    cout << endl;
}

void odwroc(list& lista)
{
    list pop = nullptr;
    list nast = lista;

    while (nast->next != nullptr)
    {
        list nast2 = nast->next;
        nast->next = pop;//przelaczenie
        pop = nast;
        nast = nast2;
    }

    nast->next = pop;
    lista =  nast;
}

list merge(list l1, list l2) {
    if (l1 == NULL) {
        return l2;
    }
    if (l2 == NULL) {
        return l1;
    }
    if (l1->key > l2->key) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}

int main()
{
    list l1 = nullptr;
    list l2 = nullptr;
    list l0 = nullptr;
    for (int i = 1; i <= 10; i+=2)
    {
        push(l1, i);
        push(l2, i+1);
        // wypisz(l);
    }

    wypisz(l1);
    wypisz(l2);
    
    l0 = merge(l1, l2);

    wypisz(l0);
}

