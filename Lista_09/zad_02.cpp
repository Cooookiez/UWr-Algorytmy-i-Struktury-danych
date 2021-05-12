
#include <iostream>

using namespace std;

void printBits( unsigned int n )
{
    const int Bits = 8 * sizeof n;
    char tmp[ Bits + 1 ];

    for( int i = 0; i < Bits; ++i )
    {
        tmp[ Bits - i - 1 ] = '0' + n % 2;
        n /= 2;
    }

    tmp[ Bits ] = 0;
    std::cout << tmp;
}

int f(int n) {

    int ileB = 0;
    int int_size_bits = sizeof(n) * 8;
    bool tmpB;
    for (int i = 0; i < int_size_bits; i++) {
        tmpB = ((n & (1<<i)) != 0);
        // cout << tmpB;
        ileB += (int)tmpB;
    }
    return ileB;
}

int main() {

    // cout << "[bit] sizeof(int): " << sizeof(int) << endl;
    // cout << "[byte] sizeof(int) * 8: " << sizeof(int) * 8 << endl;

    cout << "f(i): " << f(7) << endl;

    // printBits(13); cout << " " << 13 << endl;
    // printBits(1<<0); cout << " " << (1<<0) << endl;
    // printBits(13 & (1<<0)); cout << " " << (13 & (1<<0)) << endl;
    // cout << ((13 & (1<<0)) != 0);
    // cout << endl << endl;

    // printBits(13); cout << " " << 13 << endl;
    // printBits(1<<1); cout << " " << (1<<1) << endl;
    // printBits(13 & (1<<1)); cout << " " << (13 & (1<<1)) << endl;
    // cout << ((13 & (1<<1)) != 0);
    // cout << endl << endl;

    // printBits(13); cout << " " << 13 << endl;
    // printBits(1<<2); cout << " " << (1<<2) << endl;
    // printBits(13 & (1<<2)); cout << " " << (13 & (1<<2)) << endl;
    // cout << ((13 & (1<<2)) != 0);
    // cout << endl << endl;

    // printBits(13); cout << " " << 13 << endl;
    // printBits(1<<3); cout << " " << (1<<3) << endl;
    // printBits(13 & (1<<3)); cout << " " << (13 & (1<<3)) << endl;
    // cout << ((13 & (1<<3)) != 0);
    // cout << endl << endl;

    // printBits(13); cout << " " << 13 << endl;
    // printBits(1<<4); cout << " " << (1<<4) << endl;
    // printBits(13 & (1<<4)); cout << " " << (13 & (1<<4)) << endl;
    // cout << ((13 & (1<<4)) != 0);
    // cout << endl << endl;

    return 0;
}