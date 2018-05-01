#ifndef BIGINTEGER_EXCEPTION_H
#define BIGINTEGER_EXCEPTION_H

#include <exception>

class BigIntegerException : public std::exception {
public:
    const char *what() const throw(){
        return "An error occurred with BigInteger";
    }
};

class InvalidInputNumberString : public BigIntegerException {
public:
    const char *what() const throw(){
        return "An error occurred with BigInteger";
    }
};

#endif //BIGINTEGER_EXCEPTION_H
