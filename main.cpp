#include <iostream>
#include "BigInteger.h"

int main() {
    BigInteger a{100};
    BigInteger b{12};

    a += b;

    cout << a.getNumber() << endl;
    return 0;
}