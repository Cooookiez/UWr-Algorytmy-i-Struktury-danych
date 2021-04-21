#include <iostream>
#include <cassert>
#include <sstream>


using namespace std;

class RBTsentinel
{	
	public:


	struct node 
	{ 
		int key;
		bool black;
		node* parent;
		node* left;
		node* right;
		
		node(int x0,bool b, node*p, node* lr)
			:key(x0),black(b),parent(p),left(lr),right(lr){
		}
	};

	node *root;
	node NIL;

	RBTsentinel():root(&NIL),NIL(0,true,&NIL,&NIL){}
	~RBTsentinel(){destroy(root);}

    node * nil(){return &NIL;}

	node* find(int x)
	{	node* t=root;
		while(t!=&NIL && t->key!=x)
			if(x<t->key)
				t=t->left; 
			else
				t=t->right; 
		return t;
	}

	void insert(int x)
	{		
		if(root==&NIL)
			root=new node(x,true,&NIL,&NIL);
		else
		{
			node *t=root;
			for(;;)
			if(x<t->key)
			{
				if(t->left!=&NIL)
					t=t->left;
				else
				{
					t->left=new node(x,false,t,&NIL);
					if(!t->black)
						fix_up(t->left);
					break;
				}
			}
			else
			{
				if(t->right!=&NIL)
					t=t->right;
				else
				{
					t->right=new node(x,false,t,&NIL);
					if(!t->black)
						fix_up(t->right);
					break;
				}
			}
		}
	}  



	void fix_up(node* t)
	{

		while(t->parent!=&NIL && !t->parent->black)
		{
			if(t->parent==t->parent->parent->left)
			{ 

				node *y=t->parent->parent->right;
				if(!y->black)
				{
					t->parent->black=y->black=true;
					t=t->parent->parent;
					t->black=false;
				}
				else  //y->black
				{
					if(t==t->parent->right)
					{
						t=t->parent;
						rotate_left(t);
					}
					t->parent->black=true;
					t->parent->parent->black=false;
					rotate_right(t->parent->parent);
					return;
				}
				
			}  	
			else 
			{
				node *y=t->parent->parent->left;
				if(!y->black)
				{
					t->parent->black=true;
					y->black=true;
					t=t->parent->parent;
					t->black=false;
				}
				else  //y->black
				{
				
					if(t==t->parent->left)
					{
						t=t->parent;
						rotate_right(t);
					}
					t->parent->black=true;
					t->parent->parent->black=false;
					rotate_left(t->parent->parent);
					return;
				}
			}  	
		}
		root->black=true;
	}

	void rotate_left(node *a)
	{
		node *c=a->right, *b=c->left;

		if(a->parent!=&NIL)
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
		if(b!=&NIL) b->parent=a;
			
	}

	void rotate_right(node *c)
	{
		node *a=c->left, *b=a->right;

		if(c->parent!=&NIL)
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
		if(b!=&NIL) 
			b->parent=c;
			
	}


	void remove(int x)
	{
		node *t=find(x);
		if(t==&NIL) return;
		
		if(t->left!=&NIL && t->right!=&NIL)
		{  	node *d=t;
			for(t=t->right;t->left!=&NIL;t=t->left) // idź do następnika
				continue;
			d->key=t->key; 
			//kopiuj też inne informacje
		}
		node *p= t->parent;	
		node *d= t->right!=&NIL ? t->right : t->left;
		if(d!=&NIL) 
			d->parent=p;
		if(p!=&NIL)
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
			rem_fix_up(d,p);
	}


	void rem_fix_up(node* x,node* p)
	{
		// x child of the deleted node
		// p parent of the deleted node
		while(x!=root && x->black)
		{
		if(x==p->left)
		{
			node* w=p->right;
			
			if(!w->black)
			{	
				w->black=true;
				p->black=false;
				rotate_left(p);
				w=p->right;
			}
			
			if( w->left->black  && w->right->black)
			{
				w->black=false;
				x=p;	
				p=x->parent;
			}
			else
			{ 
				if(w->right->black)
				{
					w->left->black=true;
					w->black=false;
					rotate_right(p->right);
					w=p->right;
				}
				w->black=p->black;
				w->right->black=true;
				p->black=true;
				rotate_left(p);
				x=root;
			}
			
		} 
		else
		{
			node* w=p->left;
			
			if(!w->black)
			{	
				w->black=true;
				p->black=false;
				rotate_right(p);
				w=p->left;
			}
			
			if(w->left->black  && w->right->black)
			{
				w->black=false;
				x=p;
				p=x->parent;	
			}
			else
			{ 
				if(w->left->black)
				{
					w->right->black=true;
					w->black=false;
					rotate_left(p->left);
					w=p->left;
				}
				w->black=p->black;
				w->left->black=true;
				p->black=true;
				rotate_right(p);
				x=root;
			}
		}
		}
		if(x)
			x->black=true;
	}


	void destroy(node*&t)
	{
		if(t!=&NIL)
		{	destroy(t->left);
			destroy(t->right);
			delete t;
			t=&NIL;
		}
	}

	class iterator
	{
		node *t;
		node *nil;
		
		public:
		
		iterator(node* t0,node *nil0):t(t0),nil(nil0){}
		
		int operator*(){return t->key;}
		
		void operator++()
		{
			if(t->right!=nil)
				for(t=t->right;t->left!=nil;t=t->left)
					continue;
			else
			{
				while(t==t->parent->right)
					t=t->parent;
				t=t->parent;
			}
		}

		void operator--()
		{
			if(t->left!=nil)
				for(t=t->left;t->right!=nil;t=t->right)
					continue;	
			else
			{
				while(t==t->parent->left)
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
		while(t->left!=&NIL)
			t=t->left;
		return iterator(t,&NIL);	
	}

	iterator rbegin()
	{ 
		node* t=root;
		while(t->right!=&NIL)
			t=t->right;
		return iterator(t,&NIL);	
	}

	iterator end()
	{
		return iterator(&NIL,&NIL);
	}

	iterator rend()
	{
		return iterator(&NIL,&NIL);
	}

	int H(node* t)  // wysokość drzewa BST (rekurencyjnie)
	{
		if(t==&NIL) return 0;
		int hL=H(t->left);                  // wysokość lewego poddrzewa
		int hR=H(t->right);	                // wysokość prawego poddrzewa
		return 1+ (hR > hL ? hR : hL);      // większa z nich plus jeden 
	}


	void prettyLine2(node*t, int &n, string c1, string c2, int level=0)
	{	
		/*     
			Jedna linia rysunku dla procedurki pretty2
		*/
		if(t!=&NIL)
		{	int k=n;
			prettyLine2(t->left,n," "+c1,"-"+c1,level-1);
			stringstream s;
			string C="([";
			string J=")]";
			s << ' '<<C[t->black]<<t->key<<J[t->black]<<' ';
			int l=s.str().length();
			n+=l;
			if(level==0)
				cout<<""<<s.str()<<"";
			else if(level==-1)
			{	
				for(int i=0;i<(l)/2;i++)
					cout<<(c1[0]==' ' ? " " : "─");
				
				cout<<(c1[0]==' ' ? "┌" : "┐");
				
				for(int i=(l)/2+1;i<l;i++)
					cout<<(c2[0]==' ' ? " " : "─");
			}
			else 
				for(int i=0;i<l;i++)
					cout<< (level>=0 ? " " : c2[-level-1]=='-'?"─":" ");
			prettyLine2(t->right,n,"-"+c2," "+c2,level-1);		 
		}
	}

	void pretty2()
	{
		/*
			Pokazuje drzewo w terminalu w taki sposób:
								┌──────7────┐
							┌───4─┐     ┌───9───┐
						  ┌─3   ┌─5─┐ ┌─8     ┌─10─┐
						  1     4   6 7       9    11 
		*/
		
		int h=H(root);
		char c=' ';
		for(int i=0;i<h;i++)
		{
			int n=0;
			prettyLine2(root,n,"","",i); // wyświetl i-tą linię rysunku
			cout<<endl;
		}
	}
};


