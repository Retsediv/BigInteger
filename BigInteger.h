#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <string>
#include <sstream>
#include "Exceptions.h"

using std::string;
using std::stringstream;

class BigInteger {
private:
    string number_;
    bool sign_;

    bool checkForDigits(const string &str);

public:
    BigInteger() : number_("0"), sign_(false) {};

    BigInteger(const string &number, bool sign) : number_(number), sign_(sign) {
        if (!checkForDigits(number))
            throw InvalidInputNumberString();
    };

    BigInteger(const string &number) : BigInteger(number, false){};

    BigInteger(intmax_t n);

    inline const string &getNumber() const { return number_; };

    inline void setNumber(const string &number) { number_ = number; };

    inline bool isSign() const { return sign_; };

    inline void setSign(bool sign) { sign_ = sign; };

};

#endif //BIGINTEGER_BIGINTEGER_H
