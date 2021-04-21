#include <iostream>
#include <cassert>
#include <sstream>


using namespace std;

class RBT
{	
	public:


	struct node 
	{ 
		int key;
		bool black;
		node* parent;
		node* left;
		node* right;
		
		node(int x0, node*p, bool b=false)
			:key(x0),black(b),parent(p),left(nullptr),right(nullptr){
		}
	};

	node *root;

	RBT():root(nullptr){}

	~RBT(){destroy(root);}

    node * nil(){return nullptr;}

	node* find(int x)
	{	node* t=root;
		while(t && t->key!=x)		
			if(x<t->key) 
				t=t->left; 
			else
				t=t->right; 
		
		return t;
	}

	void insert(int x)
	{	
		
		if(root==nullptr)
			root=new node(x,nullptr,true);
		else
		{
			node *t=root;
			for(;;)
			if(x<t->key)
			{
				if(t->left)
					t=t->left;
				else
				{
					t->left=new node(x,t);
					fix_up(t->left);
					break;
				}
			}
			else
			{
				if(t->right)
					t=t->right;
				else
				{
					t->right=new node(x,t);
					fix_up(t->right);
					break;
				}
			}
		}
	}  


	void fix_up(node* t) 
	{   // poprawa uruchamiana jeśli ojciec wstawianego węzła jest czerwony
	    // właśnie wstawiony czerwony węzeł
		node *p,*pp; // p = ojciec t, pp = dziadek t
		while((p=t->parent)!=nullptr && !p->black) // dopóki ojciec jest czerwony
		{	
			pp=p->parent;  // pp = dziadek t
			if(p==pp->left)
			{ 
				node *q=pp->right; // q = brat ojca czyli wujek t
				if(q && !q->black) // jeśli czerwony to przekolorowanie
				{
					p->black=q->black=true; // ojca, wujka
					pp->black=false;        // i dziadka
					t=pp;                   // i idzemy dwa poziomy wyżej 
				}
				else                // a jeśli czarny to
				{
					if(t==p->right)        // w przypadku zygzaku   
						rotate_left(p);    // rotacja prostująca linię t-p-pp
					rotate_right(pp);      // rotacja pp-p naprawia drzewo
					return;
				}
				
			}  	
			else  // analogicznie z zamianą left <-> right
			{
				node *q=pp->left; 
				if(q && !q->black)
				{
					p->black=q->black=true;
					pp->black=false;
					t=pp;
				}
				else  //q->black
				{
				
					if(t==p->left)
						rotate_right(p);
					rotate_left(pp);
					return;
				}
			}  	
		}
		root->black=true;
	}


	void rotate_left(node *a)
	{
		node *c=a->right, *b=c->left;

		if(a->black!=c->black)  // jeśli kolory się różnią
		{
			a->black=!a->black; // zmień na przeciwne
			c->black=!c->black;
		}

		if(a->parent!=nullptr)
		{
			if(a==a->parent->right)
				a->parent->right=c;
			else
				a->parent->left=c;
		}
		else
			root=c;

		c->parent=a->parent;      	
		c->left=a; 
		a->parent=c;    
		a->right=b; 
		if(b!=nullptr) b->parent=a;
			
	}

	void rotate_right(node *c)
	{
		node *a=c->left, *b=a->right;

		if(a->black!=c->black)   // jeśli kolory się różnią
		{
			a->black=!a->black;  // zmień na przeciwne
			c->black=!c->black;
		}

		if(c->parent!=nullptr)
		{
			if(c==c->parent->right)
				c->parent->right=a;
			else
				c->parent->left=a;
		}
		else
			root=a;

		a->parent=c->parent;      
		a->right=c; 
		c->parent=a;    
		c->left=b; 
		if(b!=nullptr) 
			b->parent=c;
			
	}


	void remove(int x)
	{
		node *t=find(x);
		if(t==nullptr) return;
		
		if(t->left && t->right)
		{  	node *d=t;
			for(t=t->right;t->left;t=t->left) // idź do następnika
				continue;
			d->key=t->key; 
			//kopiuj też inne informacje
		}
		node *p= t->parent;	
		node *d= t->right ? t->right : t->left;		
		if(d) 
			d->parent=p;
		if(p)
		{
			if(t==p->left)
				p->left=d;
			else
				p->right=d;	
		}
		else 
			root=d;
		bool black=t->black;	
		delete t;
		if(black)
			if(d)
				d->black=true;
			else
				rem_fix_up(d,p);
	}



	void rem_fix_up(node* x,node* p)
	{
		// x child of the deleted node
		// p parent of the deleted node
		while(x!=root && (!x || x->black))
		if(x==p->left)
		{
			node* w=p->right;
			
			if(w && !w->black)
			{	
				rotate_left(p);
				w=p->right;
			}
			
			if( (!w->left || w->left->black ) && (!w->right || w->right->black ))
			{
				w->black=false;
				x=p;	
				p=x->parent;
			}
			else
			{ 
				if(!w->right || w->right->black)
				{
					rotate_right(p->right);
					w=p->right;
				}
				w->right->black=true;
				rotate_left(p);
				x=root;
			}
			
		} 
		else
		{
			node* w=p->left;
			
			if(w && !w->black)
			{	
				rotate_right(p);
				w=p->left;
			}
			
			if( (!w->left || w->left->black ) && (!w->right || w->right->black ))
			{
				w->black=false;
				x=p;
				p=x->parent;	
			}
			else
			{ 
				if(!w->left || w->left->black)
				{
					rotate_left(p->left);
					w=p->left;
				}
				w->left->black=true;
				rotate_right(p);
				x=root;
			}
		}
		if(x)
			x->black=true;
	}

	void destroy(node*&t)
	{
		if(t)
		{	destroy(t->left);
			destroy(t->right);
			delete t;
			t=nullptr;
		}
	}

	class iterator
	{
		node *t;
		
		public:
		
		iterator(node* t0):t(t0){}
		
		int operator*(){return t->key;}
		
		void operator++()
		{	
			if(t->right)
			{
				t=t->right;
				while(t->left)
					t=t->left;
			}
			else
			{
				while(t->parent && t==t->parent->right)
					t=t->parent;
				t=t->parent;
			}
				
		}

		void operator--()
		{
			if(t->left)
			{	
				t=t->left;
				while(t->right)
					t=t->right;
			}
			else
			{
				while(t->parent && t==t->parent->left)
					t=t->parent;
				t=t->parent;
			}
		}
		
		bool operator==(const iterator&b)
		{
			return t==b.t;
		}

		bool operator!=(const iterator& b)
		{
			return t!=b.t;
		}
							
	};

	iterator begin()
	{ 	node* t=root;
		while(t->left)
			t=t->left;
		return t;	
	}

	iterator rbegin()
	{ 
		node* t=root;
		while(t->right)
			t=t->right;
		return t;	
	}

	iterator end()
	{	
		return nullptr;
	}

	iterator rend()
	{
		return nullptr;
	}
};

