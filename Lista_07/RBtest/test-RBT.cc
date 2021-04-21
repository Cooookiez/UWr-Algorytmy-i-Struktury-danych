#include <iostream>
#include <cassert>
#include <sstream>
#include <sys/time.h>


#include "RBT.h"
#include "RBTsentinel3.h"
#include "RBTnp.h"
#include "RBTnpnr.h"



inline double stoper () 
{
  static double t=0;   
  double t1=t;
  struct timeval tv;
  gettimeofday (&tv, nullptr);
  t=tv.tv_sec+0.000001*tv.tv_usec;
  return t-t1;
}


using namespace std;

template <class T>
bool Black(T* t)
{
	return t->black;
}

template <>
bool Black(RBnode* t)
{
	return !t->red;
}

template <class T>
int Hp(T* t, T*null)  // wysokość drzewa BST (rekurencyjnie)
{
	if(t==null) return 0;
	int hL=Hp(t->left,null);                  // wysokość lewego poddrzewa
	int hR=Hp(t->right,null);	                // wysokość prawego poddrzewa
	return 1+ (hR > hL ? hR : hL);      // większa z nich plus jeden 
}

template <class T>
void prettyLine2(T* t, T* null, int &n, string c1, string c2, int level=0)
{	
	/*     
		Jedna linia rysunku dla procedurki pretty2
	*/
	if(t!=null)
	{	int k=n;
		prettyLine2(t->left,null, n," "+c1,"-"+c1,level-1);
		stringstream s;
		string C="([";
		string J=")]";
		s << ' '<<C[Black(t)]<<t->key<<J[Black(t)]<<' ';
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
		prettyLine2(t->right,null,n,"-"+c2," "+c2,level-1);		 
	}
}
template <class T>
void pretty2(T*t, T*null)
{
	/*
		Pokazuje drzewo w terminalu w taki sposób:
	                        ┌──────7────┐
	                    ┌───4─┐     ┌───9───┐
                      ┌─3   ┌─5─┐ ┌─8     ┌─10─┐
					  1     4   6 7       9    11 
	*/
	
	int h=Hp(t,null);
	char c=' ';
	for(int i=0;i<h;i++)
	{
	    int n=0;
		prettyLine2(t,null,n,"","",i); // wyświetl i-tą linię rysunku
		cout<<endl;
	}
}


template <class T>
int hbCheck(T*t,T*null)
{
	if(t==null) 
		return 0;

	int hl=hbCheck(t->left,null);

	if(hl==-1) 
		return -1;

	if(hl!=hbCheck(t->right,null))
		return -1;
	
	return hl+ t->black;
}

template <>
int hbCheck(RBnode*t,RBnode*null)
{
	if(t==null) 
		return 0;

	int hl=hbCheck(t->left,null);

	if(hl==-1) 
		return -1;

	if(hl!=hbCheck(t->right,null))
		return -1;
	
	return hl+ !t->red;
}


template <class T>
void test1(int n, string title="")
{
	cout<<endl;
	cout<<title<<endl;

	T t;
	stoper();
	for(int i=0;i<n;i++)
	{
		t.insert(i); 
	}
	cout<<"insert="<<stoper()<<endl;
	int found=0;
	for(int i=0;i<n;i++)
	{
		int key=i*7%n;
	 	if(t.find(key)!=t.nil())
		 	found++;
	}
	int sum=0;
	cout<<"find="<<stoper()<<" found="<<found<<endl;
	for(int i=0;i<100;i++)
	{
		for(auto x:t)
			sum+=x;
	}
	cout<<"100*iterate="<<stoper()<<" sum= "<<sum<<endl;	

	for(int i=0;i<n;i++)
	{	
		int key=i*7%n;
	 	t.remove(key);    
	}
	cout<<"remove="<<stoper()<<endl;
		
}


template <class T>
void testInsert(int n, string title="")
{
	cout<<endl;
	cout<<"test insert "<<title<<" n="<<n<<endl;
	T t;
	stoper();
	for(int i=0;i<n;i++)
	{
		t.insert(i); 
	}
	cout<<"insert="<<stoper()<<endl;		
}


template <class T>
void test2(int n, string title="", bool show=false)
{
	cout<<endl;
	cout<<title<<endl;
	T t;
	cout<<"node size ="<<sizeof(*t.root)<<endl;

	stoper();
	for(int i=0;i<n;i++)
	{
		t.insert(i); 
		if(show)
		{ cout<<"Wstawiam "<<i<<endl;
		  pretty2(t.root,t.nil());
		}
		int check=hbCheck(t.root,t.nil());
		if(check<0)
		{
			cout<<"hb("<<i<<")=="<<check<<endl;
			return;
		}
	}
	cout<<"insert="<<stoper()<<endl;

	

	for(int i=0;i<n;i++)
	{
		int key=i*7%n;
	 	t.find(key);    
	}
	cout<<"find="<<stoper()<<endl;

	for(int i=0;i<10;i++)
	{	int sum=0;
		for(auto x:t)
			sum+=x;
	}

	cout<<"10*iterate="<<stoper()<<endl;


	for(int i=0;i<n;i++)
	{	
		int key=i*7%n;
	 	t.remove(key);    
		if(show)
		{ 
			cout<<"usuwam "<<key<<endl;
		  pretty2(t.root,t.nil());
		}

		
		int check=hbCheck(t.root,t.nil());

		if(check<0)
		{
			cout<<"hb("<<i<<")="<<check<<endl;
			cout<<"key="<<key<<")="<<check<<endl;
			pretty2(t.root,t.nil());
			return;
		}
	}
	cout<<"remove="<<stoper()<<endl;
		
}


int main()
{	
	
	int n=5000000;
	
	n=50000000;
	// test1<RBT>(n,"RBT");
	// test1<RBTnp>(n,"RBTnp");
	// test1<RBTnpnr>(n,"RBTnpnr");
	// test1<RBTsentinel3>(n,"RBTsentinel3");


	n=2000;
	test2<RBT>(n,"RBT");
	test2<RBTnp>(n,"RBTnp");
	test2<RBTnpnr>(n,"RBTnpnr");
	test2<RBTsentinel3>(n,"RBTsentinel3");

	test2<RBT>(20,"RBT",true);
}