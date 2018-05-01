#include "BigInteger.h"

BigInteger::BigInteger(intmax_t n) {
    stringstream ss;
    string s;
    ss << n;
    ss >> s;


    if( isdigit(s[0]) )  {
        setNumber( s );
        setSign( false ); // +ve
    }
    else {
        setNumber( s.substr(1) );
        setSign( s[0] == '-' );
    }
}

bool BigInteger::checkForDigits(const string &str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if(!isdigit(str[i]))
            return false;
    }

    return true;
}
