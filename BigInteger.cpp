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

string BigInteger::multiply(string left, string right) {
    size_t n1 = left.size();
    size_t n2 = right.size();
    if (n1 == 0 || n2 == 0)
        return "0";

    // will keep the result number in vector
    // in reverse order
    vector<int> result(n1 + n2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (intmax_t i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = left[i] - '0';

        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;

        // Go from right to left in num2
        for (intmax_t j = n2 - 1; j >= 0; j--) {
            // Take current digit of second number
            int n2 = right[j] - '0';

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum / 10;

            // Store result
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }

    // ignore '0's from the right
    intmax_t i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
        return "0";

    // generate the result string
    string s{""};
    while (i >= 0)
        s += std::to_string(result[i--]);

    return s;
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

BigInteger &BigInteger::operator*=(const BigInteger &rhs) {
    // change signs: -1 * +1 = -1 and etc...
    setSign(sign_ ^ rhs.sign_);

    // multiply strings
    setNumber(multiply(number_, rhs.number_));
    return *this;
}