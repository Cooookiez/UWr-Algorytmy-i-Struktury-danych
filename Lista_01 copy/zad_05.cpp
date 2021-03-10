#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    string filename1 = "a.txt";
    string filename2 = "b.txt";
    string filename3 = "c.txt";

    int a_n, b_n, c_n;
    vector<int> a;
    vector<int> b;
    vector<int> c;

    string tmp;

    // first file
    ifstream myFile1;
    myFile1.open(filename1, ios::in);
    while (myFile1 >> tmp) {
        a.push_back(stoi(tmp));
    }
    myFile1.close();
    a_n = a[0];
    a.erase(a.begin());

    // second file
    ifstream myFile2;
    myFile2.open(filename2, ios::in);
    while (myFile2 >> tmp) {
        b.push_back(stoi(tmp));
    }
    myFile2.close();
    b_n = b[0];
    b.erase(b.begin());


    // vector with 0's
    for (int i = 0; i < a_n * b_n; i++) {
        c.push_back(0);
    }

    // calculating
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            c[i + j] += a[i] * b[j];
        }
    }
    //c_n
    c_n = c.size() - 1;

    ofstream myFile3;
    myFile3.open(filename3, ios::out);
    if (myFile3.good()) {
        myFile3 << c_n << " ";
        for (int i = 0; i < c.size(); i++) {
            myFile3 << c[i];
            if (i < c.size() - 1) {
                myFile3 << " ";
            }
        }
        myFile3.close();
    }


    cout << "z2 " << a[2] << endl;

    return 0;
}