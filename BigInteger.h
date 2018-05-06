#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include "Exceptions.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::string;
using std::stringstream;

class BigInteger {
private:
    string number_;
    bool sign_;

    bool checkForDigits(const string &str);

    string add(string left, string right);
    string subtract(string left, string right);
    string multiply(string left, string right);
    pair<string, long long> divide(string n, long long den);
public:
    // constructors
    BigInteger() : number_("0"), sign_(false) {};

    BigInteger(const string &number, bool sign) : number_(number), sign_(sign) {
        if (!checkForDigits(number))
            throw InvalidInputNumberString();
    };

    explicit BigInteger(const string &number) : BigInteger(number, false){};

    explicit BigInteger(intmax_t n);

    // getters and setters
    inline const string &getNumber() const { return number_; };

    inline void setNumber(const string &number) { number_ = number; };

    inline bool isSign() const { return sign_; };

    inline void setSign(bool sign) { sign_ = sign; };

    // methods
    BigInteger abs();

    // operators

    // comparision
    bool operator==(const BigInteger &rhs);
    inline bool operator!=(const BigInteger &rhs){
        return !(operator==(rhs));
    };

    bool operator>(const BigInteger &rhs);
    bool operator>=(const BigInteger &rhs){ return (operator>(rhs) || operator==(rhs)); };
    bool operator<(const BigInteger &rhs){ return !(operator>(rhs)) && !(operator==(rhs)); };
    bool operator<=(const BigInteger &rhs){ return (operator<(rhs) || operator==(rhs)); };

    // arithmetic's
    BigInteger &operator+=(const BigInteger &rhs);
    BigInteger &operator-=(const BigInteger &rhs);
    BigInteger &operator*=(const BigInteger &rhs);
    BigInteger &operator/=(const BigInteger &rhs);

    BigInteger &operator-();
    BigInteger &operator+();
};

inline BigInteger operator+(BigInteger lhs, const BigInteger &rhs) {
    return lhs += rhs;
}

inline BigInteger operator-(BigInteger lhs, const BigInteger &rhs) {
    return lhs -= rhs;
}

inline BigInteger operator+(BigInteger lhs, int rhs) {
    return lhs += BigInteger(rhs);
}

inline BigInteger operator-(BigInteger lhs, int rhs) {
    return lhs -= BigInteger(rhs);
}

inline BigInteger operator*(BigInteger lhs, const BigInteger &rhs) {
    return lhs *= rhs;
}

inline BigInteger operator/(BigInteger lhs, const BigInteger &rhs) {
    return lhs /= rhs;
}


#endif //BIGINTEGER_BIGINTEGER_H
