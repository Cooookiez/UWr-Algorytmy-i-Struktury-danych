#include <iostream>

using namespace std;

double f(double x) {
    return 2*x*x + 4*x - 3;
}

double biskecja(double a = 0, double b = 1) {
    // check if root exist
    if (f(a) * f(b) >= 0) {
        throw invalid_argument("there is no root between a and b");
    } else {
        double c;
        while ((b-a) >= .001) {
            c = (a+b) / 2;
            if (f(c) == 0) {
                break;
            } else if (f(c) * f(a) < 0) {
                b = c;
            } else {
                a = c;
            }
        }
        return c;
    }
}

int main() {

    try {
        cout << "bisekcja:" << biskecja() << endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}