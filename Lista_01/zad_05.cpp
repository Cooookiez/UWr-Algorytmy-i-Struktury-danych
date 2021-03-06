#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    string filename1 = "a.txt";
    string filename2 = "b.txt";
    string filename3 = "c.txt";

    int a_n, b_n;
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



    int tmp_val;
    for (int i = 0; i < a.size(); i++) {
        tmp_val = 0;
        for (int j = 0; j < b.size(); j++) {
            tmp_val += a[i] * b[j];
        }
        c.push_back(0);
        c.push_back(tmp_val);

    }

    ofstream myFile3;
    myFile3.open(filename3, ios::out);
    if (myFile3.good()) {
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