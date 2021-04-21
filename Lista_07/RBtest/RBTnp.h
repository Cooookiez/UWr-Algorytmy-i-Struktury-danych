#include <iostream>
#include <sstream>

using namespace std;

struct RBnode
{ 
  int key;
  bool red;
  RBnode *left;
  RBnode *right;
  
  RBnode(int x):key(x),red(true),left(NULL),right(NULL){} 
};


RBnode* find(RBnode * a, int x)
{ 
  while(a && a->key !=x)
    a= x<a->key ? a->left : a->right;
  return a;
} 


void RBtraverse (RBnode *a)
{
  if(a)
  { 
    cout<<(a->red? '(' : '[');
    RBtraverse (a->left);
    cout<< a->key ;
    RBtraverse (a->right);
    cout<<(a->red ? ')' : ']');
  }
} 

int hb(RBnode *a)
{
  if(a)
    return  !a->red + max( hb(a->left), hb(a->right) );
  else 
    return 0;
} 


int minkey(RBnode * a)
{ while(a->left) a=a->left;
  return a->key;
}  


void rot_r(RBnode *&a)
{
  bool kolor=a->red;
  a->red=a->left->red;
  a->left->red=kolor;
       
  RBnode * n=a->left;
  a->left=n->right;
  n->right=a;
	a=n;
}

void rot_l(RBnode *&a)
{
  bool kolor=a->red;
  a->red=a->right->red;
  a->right->red=kolor;
       
  RBnode * n=a->right;
  a->right=n->left;
  n->left=a;
	a=n;
}
	  
	  
// RBinsert(a,x) zwraca następujące wartości
// 0 - wszystko jest ok
// 1 - po wstawieniu 'x' węzeł 'a' stał się czerwony, ale ma czarne dzieci
// 2 - po wstawieniu 'x' węzły 'a' oraz  'a->l' są czerwone
// 3 - po wstawieniu 'x' węzły 'a' oraz  'a->r' są czerwone
// dzięki temu wiadomo jak po wywołaniu RBinsert poprawiać drzewo
int RBinsert(RBnode *& a,int x)
{ 
  if(a==NULL)
  {
    a=new RBnode(x);
    return 1;
  }
  if(x<a->key)
  {
    int res=RBinsert(a->left,x);
    if(res)  //
    {
      if(a->right && a->right->red)
      {
        if(res>1) // przypadek 1 (przekolorowanie)
	      {
          a->left->red=false;
          a->right->red=false;  
          a->red=true;  
          return 1;
	      }
	    }
      else
        switch(res)
        {
          case 2:rot_l(a->left);       //przypadek 2
          case 3:rot_r(a);return 0; //przypadek 3
          case 1:if(a->red) return 3;
        }   	
    }
  }
  else
  {
    int res=RBinsert(a->right,x);
    if(res)
    {
      if(a->left && a->left->red)
      {
        if(res>1)  //przypadek 1 (przekolorowanie)
        {
          a->right->red=false;
          a->left->red=false; 
          a->red=true; 
          return 1;
        }
      }
      else
        switch(res)
        {
          case 3:rot_r(a->right);       //przypadek 2
          case 2:rot_l(a);return 0; //przypadek 3
          case 1:if(a->red) return 2;
        }   	
    }    
  }
  return 0;  // oznacza, że wszystko jest już ok
}


// poprawianie drzwa w przypadkach (b) (c) lub (d)
// zwraca 1 jeśli po poprawieniu węzeł a jest podwójnie czarny
int fix_l(RBnode * &a )
{ 
  RBnode * t=a->right;
  if(! (t->left && t->left->red)&& ! (t->right && t->right->red) ) //przypadek (b)
  { 
    t->red=true;                // przekolorowanie
    if(! a->red )               // jeśli 'a' był czarny
        return 1;                // to teraz będzie podwójnie czarny
    else
        a->red=false;	          //jeśli był czerwony, to staje się czarny
  }
  else
  {
    if (! (t->right &&  t->right->red) )  // przypadek (c)
      rot_r(a->right);              // sprowadzamy do przypadku (d) 
    rot_l(a);                   // przypadek (d) 
    a->right->red=false;
  }
  return 0; // w pozostałych przypadkach algorytm kończy działanie
}

// poprawianie drzwwa w przypadkach (b) (c) lub (d)
// zwraca 1 jeśli po poprawieniu węzeł a jest podwójnie czarny
int fix_r(RBnode * &a )
{ RBnode * t=a->left;
  if( !(t->right && t->right->red) && !(t->left && t->left->red) ) //przypadek (b) 
  { 
    t->red=true;                //przekolorowanie
    if(! a->red )               // jeśli 'a' był czarny
      return 1;                // to teraz będzie podwójnie czarny
    else
      a->red=false;	          //jeśli był czerwony, to staje się czarny 
  }
  else
  {
    if (! (t->left && t->left->red))  // przypadek (c)
      rot_l(a->left);              // sprowadzamy do przypadku (d)
    rot_r(a);                   // przypadek (d)
    a->left->red=false;
  }
  return 0;
}
          	     	 

// zwraca 1 jeśli węzeł 'a' po usunięciu 'x' stał się "podwójnie czarny"       
int RBdel(RBnode *& a, int x)
{
  int res=-1;
  if(! a)
  {
    cout<< x <<" not in tree "<<endl;  
    return 0;
  }
  if (x<a->key)
  {
    res=RBdel(a->left,x);
    if(res)                  // a->l jest teraz podwójnie czarny
    {
      if(a->right->red)           // przypadek (a)
      {
        rot_l(a);            // sprowadzamy do jednego
        fix_l(a->left);         // pozostałych przypadków
	      return 0;
      }
      else
        return fix_l(a);      // pozostałe przypadki
    }
    
  } 
  else     
  if (x>a->key) 
    res=RBdel(a->right,x);
  else                        // x == a->x więc usuwamy a 
    if(a->left && a->right)          // ale jest dwójka dzieci
    {
       a->key=minkey(a->right);    // więc zamazuję klucz 'a' jego następnikiem 
       res=RBdel(a->right,a->key); // i usuwam następnika
    }
  if(res>0)                   // a->r jest teraz podwójnie czarny
  {
    if(a->left->red)             // przypadek (a)
    {
      rot_r(a);             // sprowadzamy do jednego
      fix_r(a->right);          // z pozostałych przypadków
	    return 0;  
    }
    else
       return fix_r(a);       // pozostałe przypadki
  }
  if(res<0) // x==a->x oraz 'a' ma co najwyżej 1 dziecko 
  {        // przeprowadzamy teraz faktyczne usunięcie węzła 'a'
    bool isred=a->red;         // zapamiętuje kolor usuwanego węzła
    RBnode* t=a;               // oraz jego adres 
    a=(a->left ? a-> left : a->right);   // adopcja potomka przez dziadka
    delete t;                  // zwolnienie pamięci
    if( a && a->red)           // jeśli potomek usuniętego jest czerwony    
    {
      a->red=isred;           // to dziedziczy kolor usuniętego ojca
      return 0;               // i wszystko jest ok
    }
    else
      return isred==false; // jeśli usunięty węzeł był czarny, 
                          // a jego dziecko jest czarne (lub NULL)
                          // to a jest teraz podwójnie czarny
  }       
  return 0;  // w pozostałych przypadkach wszystko jest ok  
}    

int H(RBnode* t)  // wysokość drzwea BST (rekurencyjnie)
{
	if(!t) return 0;
	int hL=H(t->left);                  // wysokość lewego poddrzewa
	int hR=H(t->right);	                // wysokość prawego poddrzewa
	return 1+ (hR > hL ? hR : hL);      // większa z nich plus jeden 
}


void prettyLine2(RBnode*t, int &n, string c1, string c2, int level=0)
{	
	/*     
		Jedna linia rysunku dla procedurki pretty2
	*/
	if(t)
	{	int k=n;
		prettyLine2(t->left,n," "+c1,"-"+c1,level-1);
		stringstream s;
		string C="[(";
		string J="])";
		s << ' '<<C[t->red]<<t->key<<J[t->red]<<' ';
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

void pretty2(RBnode*t)
{
	/*
		Pokazuje drzewo w terminalu w taki sposób:
	                        ┌──────7────┐
	                    ┌───4─┐     ┌───9───┐
                      ┌─3   ┌─5─┐ ┌─8     ┌─10─┐
					  1     4   6 7       9    11 
	*/
	
	int h=H(t);
	char c=' ';
	for(int i=0;i<h;i++)
	{
	    int n=0;
		prettyLine2(t,n,"","",i); // wyświetl i-tą linię rysunku
		cout<<endl;
	}
}

class iter
{
	RBnode *cur=nullptr;
  RBnode **stos=nullptr;
  RBnode **par=nullptr;

	public:

  iter (const iter &i);
  iter (iter &i);

  iter operator=(const iter &i);
  iter operator=(iter &i);

  iter(RBnode* n):cur(n),stos(nullptr),par(nullptr){
	  if(cur)
    { stos=par=new RBnode*[100];
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

iter begin(RBnode* t){return iter(t);}
iter end(RBnode*t){return iter(nullptr);}
	
void destroy(RBnode*&t)
{
  if(t)
  {	destroy(t->left);
    destroy(t->right);
    delete t;
    t=nullptr;
  }
}

class RBTnp
{
  public:

  RBnode *root;

  RBTnp():root(nullptr){}
  ~RBTnp(){destroy(root);}
  RBnode * nil(){return nullptr;}
  RBnode * find(int x){return ::find(root,x);}
  void insert(int x){RBinsert(root,x);}
  void remove(int x){RBdel(root,x);}
  iter begin(){return ::begin(root);}
  iter end(){return ::end(root);}
};
