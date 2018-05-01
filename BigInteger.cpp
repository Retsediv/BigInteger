#include <iostream>
#include "BigInteger.h"

BigInteger::BigInteger(intmax_t n) {
    stringstream ss;
    string s;
    ss << n;
    ss >> s;


    if (isdigit(s[0])) {
        setNumber(s);
        setSign(false); // plus
    } else {
        setNumber(s.substr(1));
        setSign(s[0] == '-');
    }
}

bool BigInteger::checkForDigits(const string &str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (!isdigit(str[i]))
            return false;
    }

    return true;
}

BigInteger BigInteger::abs() {
    return BigInteger(number_);
}

bool BigInteger::operator==(const BigInteger &rhs) {
    if(number_.size() != rhs.number_.size() || sign_ != rhs.sign_){
        return false;
    }

    for (size_t i = 0; i < number_.size(); ++i) {
        if(number_[i] != rhs.number_[i])
            return false;
    }

    return true;
}

bool BigInteger::operator>(const BigInteger &rhs) {
    // case with different signs
    if(sign_ != rhs.sign_)
        return !sign_;

    // case with different lengths
    if(number_.size() != rhs.number_.size())
        return number_.size() > rhs.number_.size();

    // check every digit
    for (size_t i = 0; i < number_.size(); ++i) {
        if(number_[i] > rhs.number_[i])
            return true;

        if(number_[i] < rhs.number_[i])
            return false;
    }

    return false;
}

//BigInteger &BigInteger::operator+=(const BigInteger &rhs) {
//    BigInteger addition;
//    if (isSign() == rhs.isSign()) // both +ve or -ve
//    {
//        addition.setNumber(add(getNumber(), rhs.getNumber()));
//        addition.setSign(isSign());
//    } else // sign different
//    {
//        if (abs() > rhs.abs()) {
//            addition.setNumber(subtract(getNumber(), rhs.getNumber()));
//            addition.setSign(getSign());
//        } else {
//            addition.setNumber(subtract(b.getNumber(), getNumber()));
//            addition.setSign(b.getSign());
//        }
//    }
//
//    if (addition.getNumber() == "0") // avoid (-0) problem
//        addition.setSign(false);
//
//    return addition;
//}
