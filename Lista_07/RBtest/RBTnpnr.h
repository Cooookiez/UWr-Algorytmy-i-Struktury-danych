
class RBTnpnr
{	
	public:
	
	struct node 
	{ 
		int key;
		bool black;
		node* left;
		node* right;
		
		node(int x0,bool b=false)
			:key(x0),black(b),left(nullptr),right(nullptr){
		}
	};

	node *root;

	RBTnpnr():root(nullptr){}
	~RBTnpnr(){destroy(root);}

    node * nil(){return nullptr;}

	node* find(int x)
	{	node* t=root;
		while(t && t->key!=x)	// dopóki nie znaleziono	
			t = x<t->key?
				t->left:
				t->right; 

		return t;
	}


	void insert(int x)
	{	// nie korzysta z pola parent 
		if(root==nullptr)          // jeśli drzewo jest puste
			root=new node(x,true); // wstaw do niego nowy czarny korzeń
		else
		{	node** stos[100];
			node*** p=stos;
			node **t=&root;
			*p=nullptr;
			while(*t)   // szukaj liścia w którym należy umieścić klucz x
			{	*++p=t; // zapamiętując adresy odwiedzanych węzłów na stosie
				t= x<(*t)->key? 
				    &(*t)->left: 
					&(*t)->right;
			}
			*t=new node(x,false); // wstaw w liści nowy czerwony węzeł
			fix_up3(p,*t); // popraw drzewo jeśli jego ojciec też jest czerwony
		}
	}  



	void fix_up3(node***P,node* t)
	{	// P tablica adresów przodków
		// t- nowo wstawiony czerwony węzeł 
		node *p,*pp; // p ojciec, pp - dziadek 
		while((*P)!=nullptr && !(p=**P)->black) // dopóki ojciec czerwony
		{	
			pp=*P[-1];              // odczytaj adres dziadka z listy
			if(p==pp->left)         // jeśli ojciec jest lewym synem dziadka
			{ 
				node *q=pp->right; // to wujek jest prawym synem dziadka
				if(q && !q->black) // jeśli wujek czerwony (i ojciec też)
				{	               // przekolorowanie:
					p->black=q->black=true; // ojca, wujka
					pp->black=false;        // i dziadka 
					t=pp;            // i przejście 
					P-=2;            // 2 poziomy wyżej
				}
				else                   // a jeśli wujek jest czarny
				{
					if(t==p->right)    // to gdy t-p-q nie są na lini prostej
						rot_left(**P); // rotacja ojca w lewo ją prostuje
					rot_right(*P[-1]); // teraz rotacja dziadka w prawo
					break;             // rozwiązuje problem
				}	
			}  	
			else                   // a jeśli ojciec jest prawym synem dziadka
			{
				node *q=pp->left;  // to wujek jest lewym  synem dziadka 
				if(q && !q->black) // jeśli wujek czerwony (i ojciec też)
				{                  // przekolorowanie
					p->black=q->black=true; // ojca, wujka
					pp->black=false;        // i dziadka   
					t=pp;              // i przejście  
					P-=2;              // 2 poziomy wyżej
				}
				else                   // a jeśli wujek jest czarny
				{				
					if(t==p->left)      // to gdy t, ojciec i dziadek nie są na lini prostej
						rot_right(**P); // rotacja oja w prawo ją prostuje
					rot_left(*P[-1]);   // teraz rotacja dziadka w lewo
					break;              // rozwiązuje problem
				}
			}  	
		}
		root->black=true; // jeśli korzeń stał się czerwony zamaluj na czarno 
	}



	void rot_left(node *&a) // no parent
	{
		node *c=a->right;
		if(a->black!=c->black)
		{   // zamiana kolorów
			a->black=!a->black;
			c->black=!c->black;
		}
		a->right=c->left; 
		c->left=a; 
		a=c;

	}

	void rot_right(node *&c)
	{
		node *a=c->left;
		
		if(a->black!=c->black)
		{   // zamiana kolorów
			a->black=!a->black;
			c->black=!c->black;
		}

		c->left=a->right; 
		a->right=c; 
		c=a;

	}

	void remove(int x)
	{
		node** stos[100];
		node*** p=stos;
		node **t=&root;
		*p=nullptr;
		while(*t && (*t)->key!=x)
		{	*++p=t;
			t= x<(*t)->key? 
				&(*t)->left: 
				&(*t)->right;
		}
		if(*t==nullptr) return;
		
		if((*t)->left && (*t)->right) // jeśli
		{  	node *d=*t;
			*++p=t;
			for(t=&(*t)->right;(*t)->left;t=&(*t)->left) // idź do następnika
				*++p=t;
			d->key=(*t)->key; 
			//kopiuj też inne informacje
		}
		node *d= (*t)->right ? (*t)->right : (*t)->left;
		bool black=(*t)->black;
		delete *t;
		*t=d;
		if(black)
			if(d)
				d->black=true;
			else
				rem_fix_up3(d,p);
	}

	void rem_fix_up3(node* x,node*** P)
	{
		// x child of the deleted node
		// **P parent of the deleted node
		node *p,*pp;
		while(x!=root && (!x || x->black))
		{ 
		  p=**P;
		if(x==p->left)
		{
			node* w=p->right; 
			
			if(w && !w->black)  // jeśli brat nie jest czarny
			{	
				rot_left(**P);  // rotacja w lewo
				*++P=&w->left;  // brat będzie taraz dziadkiem a ojciec jego lewym synem
				w=p->right;     // wskaźnik na brata trzeba zaktualizować
			}

			// tutaj brat jest już czarny 
			
			if( (!w->left || w->left->black ) && (!w->right || w->right->black ))
			{   // jeśli dzieci brata nie są czerwone, to można zrobić przekolorowanie
				w->black=false; // brata na czerwono, x - na zwykły czarny 
				x=p;	        // i przejść o poziom wyżej
				P--;
			}
			else
			{ 
				if(!w->right || w->right->black) // jeśli prawy syn brata jest czarny
					rot_right(p->right);         // to teraz będzie czerwony
				rot_left(**P);            // czarny brat wchodzi nad ojca
				(**P)->right->black=true; // a jego prawy syn staje się czarny
				x=root;
			}
			
		} 
		else // analogiczne dla zamienionego right <-> left
		{
			node* w=p->left;
			
			if(w && !w->black)
			{	
				rot_right(**P);
				*++P=&w->right;
				w=p->left;
			}
			
			if( (!w->left || w->left->black ) && (!w->right || w->right->black ))
			{
				w->black=false;
				x=p;
				P--;
			}
			else
			{ 
				if(!w->left || w->left->black)
					rot_left(p->left);
				rot_right(**P);
				(**P)->left->black=true;
				x=root;
			}
		}
		}
		if(x)  // doszliśmy do czerwonego węzła lub korzenia
			x->black=true; // który pochłania nadmiar czarnego koloru
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
	


	class iter
	{
		node *cur=nullptr;
		node **stos=nullptr;
		node **par=nullptr;

		public:

	iter (const iter &i);
	iter (iter &i);

	iter operator=(const iter &i);
	iter operator=(iter &i);

	iter(node* n):cur(n),stos(nullptr),par(nullptr){
		if(cur)
		{ stos=par=new node*[100];
		*par++=nullptr;
		for(;cur->left;cur=cur->left)
			*par++=cur;
		}
	}

	~iter(){
		delete []stos;
	}

		int operator*(){
			return cur->key;
		}

		void operator++(){
			if(cur->right)
				for(cur=cur->right;cur->left;cur=cur->left)
					*par++=cur;
			else
				cur=*--par;
		}

		bool operator!=(const iter & b){ return cur!=b.cur;}
		bool operator==(const iter & b){ return cur==b.cur;}

	};

	iter begin(){return iter(root);}
	iter end(){return iter(nullptr);}

};

