#include <iostream>
#include <cmath>

using namespace std;


/* 
  
  Przykłady programowania dynamicznego

  Zasada: Nie licz dwa razy tego samego 

  Przykład 2) Optymalne mnożenie ciągu macierzy

*/


const int n=7; // mnożymy 7 macierzy: A0*A1*A2*A3*A4*A5*A6

// Wymiary macierzy 
//     A0 (1 x 100)  tzn. 1 wiersz x 100 kolumn
//     A1 (100 x 1)  tzn. 100 wierszy x 1 kolumna
//     A2 (1 x 100)
//     A3 (100 x 4)
// 	   A4 (4 x 5)
// 	   A5 (5 x 6)
// 	   A6 (6 x 7)

// muszą umozliwiać mnożenie, więc tworzą ciąg:

int w[n+1]={1,100,1,100,4,5,6,7}; // gdzie macierz Ai ma w[i] wierszy i w[i+1] kolumn

// A0 1 x 100
// A1 100 x 1
// A2 1 x 100
// A3 100 x 4
// A4 4 x 5

//?  i = 1, j = 4; k = 2

// (A1 A2 )  (A3 A4)
// w[i] * w[k+1] * w[j+1]



// mnożąc macierze o wymiarach (a x b) oraz (b x c) 
// otrzymujemy macierz o wymiarach (a x c)
// koszt mnożenia = ilość mnożeń do wykonania = a*b*c 
// bo wyliczenie każdego z a*c elementów  wymaga b mnożeń

// Przykład:                     3*2*4 = 24 mnożenia
//   │a b│   │A B C D│       │aA+bH aB+bF aC+bG aD+bH│ 
//   │c d│ * │E F G H│   =   │cA+dH cB+dF cC+dG cD+dH│ 
//	 │e f│	                 │cA+fH eB+fF eC+fG eD+fH│

// w[]={1,100,1,100,...}
// (A0*A1)*A2  koszt = 1*100*1 + 1*1*100 = 200 mnożeń
// A0*(A1*A2)  koszt = 100*1*100 + 1*100*100 = 20000 mnożeń 

// Wynik jest ten sam ale czas działania 100 razy dłuższy

int Last[n][n]={0}; 
// w elemencie Last[i,j] pamiętamy, które mnożenie trzeba wykonać jako ostatnie, by pomnożyć optymalnie macierze Ai*...*Aj
// na przykład Last[0,2]=1, bo mnożenie optymalne to (A0*A1)*A2, czyli na końcu trzeba wykonać * znajdującą się po macierzy A1


double KosztMin(int a, int b) // minimalna ilość mnożeń potrzebna do obliczenia iloczynu macierzy Aa*...*Ab
{
	static double K[n][n]={0}; // K[a][b] - zapamiętana minimalna ilość mnożeń potrzebna do obliczenia Aa*...*Ab
	if(K[a][b]>0)        	   // jeśli wartość niezerowa, to ten koszt już był obliczany 
		return K[a][b];  	   // i wystarczy zwrócić obliczoną wcześniej wartość
	if(b==a)             	   // jeśli a==b to ciąg składa się z jednej macierzy
		return 0;              // więc nie trzeba nic mnożyć 

    double m=0;          		// m to dotychczasowe minimum 
    for(int l=a;l<b;l++) 		// jeśli jako ostatni wykonamy mnożenie numer l
    {                    		// to optymalny koszt wyniesie
		// (Aa Aa+1 .. Al) (Al+1 Al+2 ... Ab)
		double koszt=KosztMin(a,l) + KosztMin(l+1,b) + w[a]*w[l+1]*w[b+1]; 
		if(koszt<m || m==0)     // jeśli koszt mniejszy od dotychczasowego minimum (lub pierwszy,  jaki jest obliczany)
		{
			m=koszt;            // popraw najlepszy dotychczasowy wynik
			Last[a][b]=l;       // zapamiętaj, które mnożenie wykonać jako ostatnie, by zrealizować optymalny wariant
		}
	}
	return K[a][b]=m;           // zapamiętaj wynik w tablicy K by nie obliczać go ponownie 
}

double KosztMinIteracja() {
	double K[n][n] = {0};
	// 1
	for (int d = 1; d < n; d++){
		for (int i = 0; i < n-d; i++) {
			int j = i+d;
			// K[i][j]
			// cout << "("<<i<<","<<j<<")" << endl;


			int myMin = INT_MAX;
			int toMinTmp;
			for (int k = i; k < j; k++) {
				// 2 (3 4 5)
				// (2 3) (4 5)
				// (2 3 4) 5
				// 2(34)
				toMinTmp = K[i][k] + K[k+1][j] + (w[i] * w[k+1] * w[j+1]);
				if (myMin > toMinTmp) {
					myMin = toMinTmp;
					Last[i][j] = k;
				}
			}
			K[i][j] = myMin;
			// cout << i << " " << j << " " << K[i][j] << endl;

			// 0,1
			// 1,2
			// 2,3
			// 3,4
			// 4,5

			// 0, 2
			// 1, 3
			// 2, 4
			// 3, 5

			// 0, 3
			// 1, 4
			// 2, 5

			// 0, 4
			// 1, 5

			// 0, 5
		}
		// cout << endl;
	}
	// cout << "najmniej mnozen:\t" << K[0][n-1] << endl;
	return K[0][n-1];
}

double KosztMax(int a, int b)  // obliczanie kosztu maksymalnego by zobaczyć po co to robimy
{
	static double K[n][n]={0}; 
	if(K[a][b]>0)
		return K[a][b];
	if(b==a) 
		return 0;

    double m=0;
    for(int l=a;l<b;l++)
    {
		double koszt=KosztMax(a,l)+KosztMax(l+1,b)+w[a]*w[l+1]*w[b+1];
		if(koszt>m || m==0)
		{
			m=koszt;
			Last[a][b]=l;
		}
	}
	return K[a][b]=m;
}

// Array A[7]={{1,100},{100,1}}

void mnozenie(int a, int b)  // mnożenie Aa*...*Ab w kolejności zapisanej w tablicy L[n][n]
{
	if(a==b)
		cout<<"A"<<a;       // pojedyncza macierz nie wymaga mnożenia
	else
	{   cout<<"(";    
		int l=Last[a][b];   // l to numer mnożenia jakie trzeba wykonać jako ostatnie
		mnozenie(a,l);      // iloczyn macierzy Aa*...*Al
		cout<<"*";          // pomnóż przez
		mnozenie(l+1,b);    // iloczyn macierzy A(l+1)*...Ab
		cout<<")";
	}
}


int main()
{ 
	// KosztMinIteracja();
	// return 0;
	// cout<< "koszt optymalny dla A0*A1*A2 = "<<KosztMin(0,2)<<endl;
	// cout<<"kolejność "; mnozenie(0,2);	
	
	// cout<<endl<<endl;	

	// cout<< "koszt maksymalny dla A0*A1*A2 = "<<KosztMax(0,2)<<endl;
	// cout<<"kolejność "; mnozenie(0,2);	
	
	// cout<<endl<<endl;		

	// cout<<"koszt minimalny dla A0*A2*A3*A4*A5*A6 = "<<KosztMin(0,n-1)<<endl;
    // cout<<"kolejność "; mnozenie(0,n-1);	

	// cout<<endl<<endl;	

	// cout<<"koszt maksymalny dla A0*A2*A3*A4*A5*A6 = "<<KosztMax(0,n-1)<<endl;
    // cout<<"kolejność "; mnozenie(0,n-1);	
	
	// cout<<endl<<endl;	;		

	cout<<"koszt minimalny dla A0*A2*A3*A4*A5*A6 = "<<KosztMin(0,n-1)<<endl;
    cout<<"kolejność "; mnozenie(0,n-1);	

	cout<<endl<<endl;		

	cout<<"koszt minimalny dla A0*A2*A3*A4*A5*A6 = "<<KosztMinIteracja()<<endl;
    cout<<"kolejność "; mnozenie(0,n-1);	

	cout<<endl<<endl;	
}