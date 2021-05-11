/*
 * C++ Program to Implement Binomial Heap
 */

#include <iostream>
#include <cstdlib>
using namespace std;

/*
 * Node Declaration
 */
struct node
{
    int key;
    int degree;
    node* parent;
    node* child;
    node* sibling;

    node(int n0, node* sib=nullptr):key(n0),degree(0),parent(nullptr),child(nullptr),sibling(sib){
    }

    node* adopt(node * b)
    {
        b->sibling=this->child;
        b->parent=this;
        this->child=b;
        this->degree++;
        return this;
    }

};

/*
 * Union of Binomial Heaps
 */

node* merge(node* y, node* z)
{
    node* H;
    node* T;

    if(y==nullptr)
        return z;
        
    if(z==nullptr)
        return y;

    if (y->degree <= z->degree)
    {   H = T = y;
        y = y->sibling;
    }
    else 
    {
        H = T = z;
        z = z->sibling;
    }
    
    while(T->sibling)
    {
        if (y->degree <= z->degree)
        {   
            T = T->sibling = y;
            y = y->sibling;
        }
        else 
        {
            T = T->sibling = z;
            z = z->sibling;
        }
    }

    T->sibling = y ? y : z;
    
    return H;
}

node * linkSame(node* H)
{
    if(H == nullptr)
        return H;
    node* a = nullptr;
    node* b = H;
    node* c = H->sibling;
    while (c)
    {
        if ((b->degree != c->degree) || ((c->sibling != nullptr)
            && (c->sibling)->degree == b->degree))
        {
            a = b;
            b = c;
        }
        else
	    {
            if (b->key <= c->key)
            {
                b->sibling = c->sibling;
                b->adopt(c);
            }
            else
            {
                c->adopt(b);
                b = c;
                if (a == nullptr)
                    H = b;
                else
                    a->sibling = b;
            }
	    }
        c = b->sibling;
    }
    return H;
}

node* Union(node* H1, node* H2)
{
    return linkSame(merge(H1, H2));
}

void Insert(node*& F, int x)
{
    F=linkSame(new node(x,F)) ;
}

node* revert(node* Hr) 
{
    if(Hr == nullptr)
        return Hr;
    node *a;
    node *b = nullptr;
    node *c = Hr;
    do
    {
        a=b;
        b=c;
        c=c->sibling;

        b->sibling=a;
        b->parent=nullptr;
    } while(c);

    return b;
}

int Extract_Min(node*& H1)
{
    if(H1 == nullptr)
        return 0;
    node* Hr = nullptr;
    node* t = nullptr;
    node* x = H1;
    int min = x->key;
    node* p = x;
    while (p->sibling != NULL)
    {
        if ( p->sibling->key < min)
        {
            min = (p->sibling)->key;
            x = p->sibling; // usuwany element
            t = p; // poprzednik usuwanego
        }
        p = p->sibling;
    }
    if (t == NULL)  // usuwany był pierwszy na liście
        H1 = x->sibling;
    else
        t->sibling = x->sibling;
    if (x->child != NULL)
        H1 = Union(H1, revert(x->child));
    delete x;
    return min;
}


void Show(node *H, int i=0)
{
    while(H)
    {   if(i==0)
            cout<< H->degree << ":";
        cout << " " << H->key;
        Show(H->child,1);
        if(i==0)
            cout<<endl;
        H=H->sibling;
    }
}

void Destroy(node *H)
{
    while(H)
    {   
        Destroy(H->child);
        node* next=H->sibling;
        delete(H);
        H=next;
    }
}

void Destroy2(node *H)
{
    if(H)
    {   
        Destroy2(H->child);
        Destroy2(H->sibling);
        delete(H);
    }
}


void test1(int n)
{
    node *H=nullptr;
    cout<<"początek"<<endl;
    for (size_t i = 0; i < n; i++)
        Insert(H,i);
    cout<<n<<endl;
    while(H)
    {
        Extract_Min(H);
    }
    cout<<"Koniec"<<endl;
    exit(0);
}

int main()
{
    //test1(2e5);
    //srandom(time(NULL));
    
    node * a=nullptr;
    node * b=nullptr;
    
    int la=rand()%50;
    int lb=rand()%50;

    while(0<la--)
        Insert(a,random()%100);
    while(0<lb--)
        Insert(b,random()%100);

    cout<<"Kopiec A:"<<endl;
    Show(a);cout<<endl;

    cout<<"Kopiec B:"<<endl;
    Show(b);cout<<endl;
 
    a=Union(a,b);
    cout<<"Union(A,B):"<<endl;
    Show(a);cout<<endl;
 
    cout<<"Elementy rosnąco: "<<endl;
    while(a)
    {
        cout<<Extract_Min(a) <<" ";
    }
    cout<<endl;
}