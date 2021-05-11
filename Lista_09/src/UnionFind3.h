#ifndef UNION_FIND_3
#define UNION_FIND_3

#include <iostream>
using namespace std;

class UnionFind3
{
    public:
    int n;
    int *parent;
    int *rank;

    UnionFind3(int n0):n(n0),parent(new int[n0]),rank(new int[n0])
    {
        for(int i=0;i<n;i++)
        {
            parent[i]=i;
            rank[i]=0;
        }
    }

    ~UnionFind3(){
        delete[] parent;
        delete[] rank;
    }

    int Find(int i)
    {
        if(parent[i]==i)
            return i;
        parent[i]=Find(parent[i]); // kompresja ścieżki
        // teraz parent[i] jest korzeniem drzewa                                
        return parent[i];
    }

    void Union(int i, int j)
    {
        int I=Find(i);
        int J=Find(j);
        // podpinamy niższe drzewko pod wyższe (więc wysokość wyższego nie zmienia się)
        if(rank[I]>rank[J]) 
            parent[J]=I;
        else
        // podpinamy niższe drzewko pod wyższe (więc wysokość wyższego nie zmienia się)
        if(rank[I]<rank[J])
            parent[I]=J;
        else
        // tylko jak równe to  wysokość się zwiększa
        if(rank[I]==rank[J]) 
        {
            parent[I]=J;
            rank[J]++;  
        }
    }

    void Print() {
        for(int i=0; i<n; i++) {
            cout << parent[i] << " ";
        }
        cout << endl;
    }
};

#endif