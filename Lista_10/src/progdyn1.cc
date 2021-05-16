#include <iostream>
#include <cmath>

using namespace std;


/* 

  Przykłady programowania dynamicznego
  
  Zasada: Nie licz dwa razy tego samego 

  Przykład 3) Optymalna triangulacja n kąta

*/

struct Punkt
{ 
	double x;
	double y;	
};	


double dist(Punkt A, Punkt B) // długość odcinka AB
{
	double dx = A.x-B.x;
	double dy = A.y-B.y;
	return sqrt(dx*dx+dy*dy);
}




// wierzchołki wielokąta
Punkt A[]={{0,0},{1,0},{2,1},{2,2},{1.5,3},{0.5,3},{0,2.5},{-1,1}};

const int n = sizeof(A)/sizeof(A[0]); // ilość wierzchołków wielokąta

int W[n][n]={0}; // W[a][b]=c takie, że trójkąt (a,b,c) należy do triangulacji optymalnej wielokąta A[a]..A[b]


double BestLen(int a, int b)
{
	static double L[n][n]={0}; 

	if(L[a][b]>0)          // jeśli ten wielokąt już być wyliczony 
		return L[a][b];    // zwróć obliczony wczesniej  wynik
		
	if(b<a+3)      	       // jeśli ten sam lub sąsiedni wierzchołek 
		return 0;          // 0 bo nie liczymy boków na obwodzie wielokąta tylko przekątne

    double m=0;              // najlepszy dotychczasowy wynik
	
    for(int c=a+1;c<b;c++)   // dla każdego wierzchołka c pomiędzy a i b
    {	
		
		double    koszt = BestLen(a,c) + BestLen(c,b); //  oblicz koszt triangulacji wielokątów a..c i c..b 
		if(a+1<c) koszt += dist(A[a],A[c]); // dodaj długość (a,c) jeśli jest to przekątna
		if(c+1<b) koszt += dist(A[c],A[b]); // dodaj długość (c,b) jeśli jest to przekątna

		if(koszt<m || m==0)  // jeśli koszt mniejszy od dotychczasowego minimum (lub pierwszy obliczany)
		{
			m=koszt;         // aktualizuj minimum 
			W[a][b]=c;       // zapamiętaj, z którym wierzchołkiem połączyć a i b
		}
	}
	return L[a][b]=m;        // zapamiętaj i zwróć optymalny wynik
}

void kreski(int a, int b)
{
	if(b<=a+2)
		return;
	int c=W[a][b];
	if(c>a+1)
		cout<<"  "<<a<<"--"<<c<<"  ("<<dist(A[a],A[c])<<")"<< endl;
		
	if(b>c+1)
		cout<<"  "<<c<<"--"<<b<<"  ("<<dist(A[c],A[b])<<")"<< endl;
	kreski(a,c);
	kreski(c,b);
}

bool jestWypukły(Punkt A[], int n)
{ 
	for(int i=0;i<n;i++)
	{
		Punkt a=A[i];
		Punkt b=A[(i+1)%n];
		Punkt c=A[(i+2)%n];
		
		double vx=a.x-b.x;
		double vy=a.y-b.y;
		double ux=b.x-c.x;
		double uy=b.y-c.y;

		if(ux*vy-vx*uy>0)
			return false;
	}

	return true;
}

int main()
{ 
	if(not jestWypukły(A,n))
	{	
		cout<< "Wielokąt nie jest wypukły"<<endl;
		return 0;
	}

	cout<<"Całkowita długość siatki wewnętrznej = "<<BestLen(0,n-1)<<endl;
    cout<<"Należy połączyć słupki:"<<endl;
	kreski(0,n-1);	
}


