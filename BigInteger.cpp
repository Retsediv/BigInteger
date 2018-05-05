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
    if (number_.size() != rhs.number_.size() || sign_ != rhs.sign_) {
        return false;
    }

    for (size_t i = 0; i < number_.size(); ++i) {
        if (number_[i] != rhs.number_[i])
            return false;
    }

    return true;
}

bool BigInteger::operator>(const BigInteger &rhs) {
    // case with different signs
    if (sign_ != rhs.sign_)
        return !sign_;

    // case with different lengths
    if (number_.size() != rhs.number_.size())
        return number_.size() > rhs.number_.size();

    // check every digit
    for (size_t i = 0; i < number_.size(); ++i) {
        if (number_[i] > rhs.number_[i])
            return true;

        if (number_[i] < rhs.number_[i])
            return false;
    }

    return false;
}

string BigInteger::add(string left, string right) {
    string add = (left.length() > right.length()) ? left : right;
    char carry = '0';
    int differenceInLength = std::abs((int) (left.size() - right.size()));

    if (left.size() > right.size())
        right.insert(0, differenceInLength, '0'); // put zeros from left
    else
        left.insert(0, differenceInLength, '0');

    for (intmax_t i = left.size() - 1; i >= 0; --i) {
        add[i] = ((carry - '0') + (left[i] - '0') + (right[i] - '0')) + '0';

        if (i != 0) {
            if (add[i] > '9') {
                add[i] -= 10;
                carry = '1';
            } else
                carry = '0';
        }
    }
    if (add[0] > '9') {
        add[0] -= 10;
        add.insert(0, 1, '1');
    }

    return add;
}

string BigInteger::subtract(string left, string right) {
    string sub = (left.length() > right.length()) ? left : right;
    int differenceInLength = std::abs((int) (left.size() - right.size()));

    if (left.size() > right.size())
        right.insert(0, differenceInLength, '0');

    else
        left.insert(0, differenceInLength, '0');

    for (intmax_t i = left.length() - 1; i >= 0; --i) {
        if (left[i] < right[i]) {
            left[i] += 10;
            left[i - 1]--;
        }
        sub[i] = ((left[i] - '0') - (right[i] - '0')) + '0';
    }

    while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
        sub.erase(0, 1);

    return sub;
}

BigInteger &BigInteger::operator+=(const BigInteger &rhs) {
    // equal signs
    if (isSign() == rhs.isSign()) {
        setNumber(add(getNumber(), rhs.getNumber()));
        setSign(isSign());
    } else {
        // different signs
        if (*this > rhs) {
            setNumber(subtract(getNumber(), rhs.getNumber()));
            setSign(isSign());
        } else {
            setNumber(subtract(rhs.getNumber(), getNumber()));
            setSign(rhs.isSign());
        }
    }

    if (getNumber() == "0") // avoid (-0) problem
        setSign(false);

    return *this;
}


BigInteger &BigInteger::operator-=(const BigInteger &rhs) {
    BigInteger right(rhs);
    right.setSign(!right.isSign());

    return *this += (right);
}

BigInteger &BigInteger::operator-() {
    sign_ *= -1;
    return *this;
}

BigInteger &BigInteger::operator+() {
    return *this;
}
