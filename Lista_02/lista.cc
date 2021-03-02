#include <iostream>
using namespace std;

// Podstawowa struktura listy jednokierunkowej

struct node
{
  int key;
  node* next;
 
  node(int k, node* n):key(k),next(n){}
};

typedef node* list;

void push(list & l,int k) // wkładanie na początek listy
{ 
  l=new node(k,l);
}

int pop(list &l) // wyciąganie pierwszego
{ 
    list tmp=l;
    int res=l->key;
    l=l->next;
    delete tmp;
    return res;
}  

bool empty(list l) // sprawdzanie czy lista jest pusta
{ 
  return l==NULL;
}

void destroy(list& l) //usuwa wszystkie elementy z listy  
{ 
  while(l)
    {
      list l1=l;
      l=l->next;
      delete l1;
    }
}

void wypisz(list l)
{
    for(;l;l=l->next)
      cout<<l->key<<" ";
    cout<<endl;  
}

 int main()
 {
    list l=nullptr;
    for(int i=1;i<=10;i++)
    {
      push(l,i);
      wypisz(l);
    }
    
    while(l)
    {
      pop(l);
      wypisz(l);
    }
    
    destroy(l);
 }
