#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {

    string filename;
    string fileContent = "";

    if (argc == 2) {
        filename = argv[1];
    } else {
        throw "invaild number of arguments";
    }

    // open file and get content
    ifstream ifile;
    ifile.open(filename);
    string tmp;
    while (!ifile.eof()) {
        getline(ifile, tmp);
        fileContent += tmp;
    }
    ifile.close();

    // use map to count eatch character
    map<char, int> chars;
    for (int i = 0; i < fileContent.size(); i++) {
        chars[fileContent[i]]++;
    }

    // display all characters and noumber of appearing
    for (auto ch : chars) {
        cout << ch.first << ": " << ch.second << endl;
    }

    return 0;
}