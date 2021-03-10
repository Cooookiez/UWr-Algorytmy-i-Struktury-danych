#include <iostream>

using namespace std;

int ile = 0;

long double pkt_a(double x, int n) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return x;
    } else if (n % 2 == 0) { // parzystea
        long double tmp = pkt_a(x, n/2);
        ile++;
        return tmp * tmp;
    } else { // nie parzyste
        long double tmp = pkt_a(x, (n-1)/2);
        ile++;
        ile++;
        return x * tmp * tmp;
    }

    return 0;
}

long double pkt_b(double x, int n) {
    long double w = 1;
    
    while (n > 0) {
        if (n % 2 == 1) {
            w *= x;
            ile++;
        }
        ile++;
        x *= x;
        n /= 2;
    }

    return w;
}

int main() {

    ile = 0;
    cout << "pkt a:\t" << pkt_a(3, 30) << "\t" << ile << " razy" << endl;
    ile = 0;
    cout << "pkt b:\t" << pkt_b(3, 30) << "\t" << ile <<  " razy" << endl;

    return 0;
}