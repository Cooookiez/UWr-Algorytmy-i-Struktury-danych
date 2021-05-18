#include <iostream>
#include <cmath>

using namespace std;

const int n = 5;
int ile[]={3, 5, 8, 4, 10}; // gdzie macierz Ai ma w[i] wierszy i w[i+1] kolumn
int s[n+1] = {0, 3, 7, 15, 19, 20};

// for(int i=1; i < n+1; i++) {
//   s[i] = s[i-1] + ile[i];
// }

// s[4] - s[3] = 19 - 15 = 4 = ile[3]
// s[4] - s[2] = 19 - 7 = 12 = 8 + 4 = ile[2] + ile[3]
// s[4] - s[1] = 19 - 3 = 16 = 4 + 8 + 4 = ile[1] + [2] + [3]
// s[4] - s[0] = 19 = 3 + 4 + 8 + 4 + 10 = ile[0] [1] [2] [3]

//ile[i] + ... + ile[j] = s[j+1] - s[i];
// s[i] = ile[0] + ile[1] + ile[2] + ... + ile[i-1]

// s[j+1] - s[i] = (ile[0] + ile[1] + ile[2] + ... + ile[j]) - (ile[0] + ile[1] + ile[2] + ... + ile[i-1]) 
//     = ile[i] + ile[i+1] + ile[i+2] + ... + ile[j]


int Last[n][n]={0}; 

double KosztMinIteracja() {
	double K[n][n] = {0};
    for(int i=0; i<n; i++) {
        K[i][i] = ile[i];
    }

	for (int d = 1; d < n; d++){
		for (int i = 0; i < n-d; i++) {
			int j = i+d;

			int myMin = INT_MAX;
			int toMinTmp;
            int suma = (s[j+1] - s[i]);
			for (int k = i+1; k < j; k++) {
				toMinTmp = K[i][k-1] + K[k+1][j]; // lewy trujkat optymalny + prawy trujkat optymalne
				if (myMin > toMinTmp) {
					myMin = toMinTmp;
					Last[i][j] = k;
				}
			}
            toMinTmp = K[i+1][j];
            if (myMin > toMinTmp) {
                myMin = toMinTmp;
                Last[i][j] = i;
            }

            toMinTmp = K[i][j-1];
            if (myMin > toMinTmp) {
                myMin = toMinTmp;
                Last[i][j] = j;
            }
			K[i][j] = myMin + suma;
		}
	}
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << K[i][j] << "\t";
        }
        cout << endl;
    }
	return K[0][n-1];
}

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
    KosztMinIteracja();
}