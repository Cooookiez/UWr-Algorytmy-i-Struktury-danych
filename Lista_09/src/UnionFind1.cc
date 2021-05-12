#include <iostream>
using namespace std;

class UnionFind1
{
    public:
    const int n;
    int *parent;

    UnionFind1(int n0): n(n0), parent(new int[n0])
    {
        for(int i=0;i<n;i++)
            parent[i]=i;
    }

    ~UnionFind1(){
        delete parent;
    }

    int Find(int i)
    {
        while(parent[i]!=i)
            i=parent[i];
        return i;
    }

    void Union(int i, int j)
    {
        parent[Find(i)]=Find(j);
    }
};
