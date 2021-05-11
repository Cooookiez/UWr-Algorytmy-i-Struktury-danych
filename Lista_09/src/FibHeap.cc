#include <iostream>
#include <cmath>

using namespace std;

struct node
{
    int key;
    node * parent;
    node * left;
    node * right;
    node * child;
    int degree;
    bool mark;

    node(int k):key(k),
                parent(nullptr),
                left(this),
                right(this),
                child(nullptr),
                degree(0),
                mark(false)
    {}

    ~node(){
        left->right=right;
        right->left=left;
    }

    void join(node* b)
    {   // połącz dwie niepuste listy kołowe 
        if(b)
        {
            swap(right,b->right);         
            right->left = this;
            b->right->left = b;
        }
    }

    void adopt(node* b)
    {   // usuń element b z listy korzeni i dołącz do listy dzieci
        b->right->left = b->left;
        b->left->right = b->right;
    
        b->left = b->right = b;
        if(child)
            child->join(b);
        else
            child = b;
        degree++;

        b->mark = false;
        b->parent = this;
    }
};

void show(node *a, int i=0)
{
    static const string A="(((";
    static const string B=")))";
    
    if(a==nullptr)
    {
        cout<<"NULL"<<endl;
        return;
    }
    node *x=a;
    int k=0;
    do
    {   
        if(k++>0)
            cout<<' ';
        if(x!=a && x->degree>0 && i==0)
            cout<<endl;
        if(i==0)
            cout<<'[';
        cout<<x->key;
        cout<<"/"<<x->degree;
        if(x->degree>0)
        {
            cout<<":";
        }
        
        if(x->child){
            cout<<A[i%3];
            show(x->child,i+1);
            cout<<B[i%3];
        }
        if(i==0)
            cout<<']';

        x=x->right;
    } while (x!=a);
    if(i==0)
    {
        cout<<endl;
        cout<<"==============="<<endl;
    }
}

node *godeep(node* k)
{   // funkjca szuka jakiegoś dodatniego klucza 
    node *x=k;
    do{
        if(x->child!=nullptr)
        {
            node *y=godeep(x->child);
            if(y->key>0)
                return y;
        }
        x=x->right;
    } while (x!=k);
    return k;
}

class FibHeap
{
    public:
    node * min;
    int n;
    bool say;

    public:
    FibHeap():min(nullptr),n(0),say(false){}

    void join(FibHeap b)
    {
        n+=b.n;
        min->join(b.min);
        if(b.min->key < min->key);
            min=b.min;
    }

    void insert(node* b)
    {
        if(say)
            cout<<"Insert("<<b->key<<")"<<endl;
        if(min==nullptr)
            min=b;
        else
        {
            min->join(b);
            if( b->key < min->key)
                 min=b;
        }
        n++;
    }



    void Insert(int k)
    {        
        insert(new node(k));
    }

    int Min()
    {
        if(min)
            return min->key;
        return 0;
    }

    int N(bool say=false)
    {
        if(say)
            cout<<"N="<<n<<endl;
        return n;
    }

    void Consolidate()
    {
        // if(say)
        //     cout<<"Consolidate()"<<endl;
        int N=ceil(log2(n)+1);
        node * A[N];        
        for(int i=0;i<N;i++)
            A[i]=nullptr;
        node * cur=min->right;
        node * x;
        bool end=false;
        while(!end)
        {         
            if(cur==min)
                end=true;
            x=cur;
            cur=cur->right;
            int d=x->degree;
            while(A[d]!=nullptr)
            {   node* y=A[d];
                if(x->key > y->key)
                    std::swap(x,y);
                x->adopt(y); // usuwa y z listy korzeni i dołącza do dzieci x 
                A[d]=nullptr;
                d++;
            }
            A[d]=x;
        }
        x->parent=nullptr; // x na pewno jest na liście korzeni
        min=x;  // szukamy nowego minimum 
        for(node* c=min->right;c!=x;c=c->right)
        {
            c->parent=nullptr;
            if(c->key < min->key)
                min=c;
        }
    }

    void ExtractMin()    
    {
        if(say)
            cout<<"Extractmin("<<min->key<<")"<<endl;
        if(min!=nullptr)
        {   
            if(min->child) // włóż dzici min na listę korzeni
                min->join(min->child);
            node *brat=min->right;  
            node *z=min; 
            delete z; // usuwa z min listy kołowej i z pamięci
            n--;
            if(min==brat) // lista jednoelementowa
                min=nullptr;
            else
            {
                min=brat;
                Consolidate(); 
            }        
        }
    }

    void Cut(node *y)
    {
        node * p=y->parent;
        if(!p)
            exit(1);
        p->degree--;
        if(y->right==y) // jeśli y jest ostatnim dzieckiem
            p->child=nullptr;
        else
            p->child=y->right;
            
        y->left->right=y->right;
        y->right->left=y->left;

        y->right=min->right;
        y->right->left=y;

        y->left=min;
        min->right=y;

        y->parent=nullptr;
        y->mark=false;
    }

    void CascadingCut(node* y)
    {
        node *p=y->parent;
        if (p) {
            if(y->mark)
            {
                Cut(y);
                CascadingCut(p);
            }
            else
               y->mark =true;
        }
    }

    bool DecreaseKey(node* x, int val)
    {
        if(say)
            cout<<"DecreaseKey("<<x->key<<","<<val<<")"<<endl;
        if(x->key<=val) 
            return false;
        x->key=val;
        node *y=x->parent;
        if(y && x->key < y->key)
        {
            Cut(x);
            CascadingCut(y);
        }
        if(x->key<min->key)
             min=x;
    }

    FibHeap* Union (FibHeap& b)
    {
        n+=b.n;
        if(min)
            min->join(b.min);
        else
            min=b.min;        
        b=FibHeap();
        return this;
    }

    void Show()
    {
        cout<<"n="<<n;
        if(min) 
            cout<< " min="<<min->key;
        cout<<" Rootnodes:"<<endl;
        show(min,0);
    }

};


void test1(int n)
{
    FibHeap H;
    cout<<"początek"<<endl;
    H.say=true;
    for(int i=0;i<n;i++)
    {
       H.Insert(i);
       H.Show();
    }
    while(H.N()>0)
    {
        H.ExtractMin();
        H.Show();
    }
    cout<<"koniec"<<endl;
    exit(1);
}



int test2()
{
    FibHeap H1,H2;
    
    H1.say=H2.say=true;
    node *x=nullptr;
    for(int i = 1 ;i<20;i++)
    {   node *y=new node(i*10);
        H1.insert(y);
        if(i==8)
            x=y;
    }
    H1.Show();
    cout<<"Consolidate:"<<endl;
    H1.Consolidate();
    H1.Show();
    H1.Insert(3);
    H1.Show();
    H1.ExtractMin();
    H1.Show();
    cout<<"Consolidate:"<<endl;
    H1.Consolidate();
    H1.Show();
    for(int i = 1 ;i<10;i++)
        H2.Insert(i*9);
    H2.Show();

    cout<<"Consolidate:"<<endl;
    H2.Consolidate();
    H2.Show();

    H1.DecreaseKey(x,-1);
    for(int k=0;k<4;k++){
         node *x=godeep(H1.min);
         if(x==H1.min)
            continue;
         H1.DecreaseKey(x,-k-1); 
         show(H1.min);
    }
    cout<<"Union H1 H2"<<endl;
    H1.Union(H2);
    H1.Show();
    cout<<"Consolidate:"<<endl;
    H1.Consolidate();
    H1.Show();
    int i=H1.N();
    cout<<"Klucze rosnąco:"<< endl;
    while( H1.N()>0)
    {
        H1.ExtractMin();
        H1.Show();
   }
   cout<<endl;
}


int main()
{    
    //test1(20);
    test2();
}