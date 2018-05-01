#include <gtest/gtest.h>
#include "../../BigInteger.h"
#include "../../Exceptions.h"

TEST(BigInteger, createEmpty){
    BigInteger a{};

    EXPECT_EQ("0", a.getNumber());
    EXPECT_EQ(false, a.isSign());
}

TEST(BigInteger, createFromStringWithoutSign){
    EXPECT_NO_THROW(BigInteger t{"12356"});
    EXPECT_THROW(BigInteger t{"+112"}, InvalidInputNumberString);
    EXPECT_THROW(BigInteger t{"-132"}, InvalidInputNumberString);
    EXPECT_THROW(BigInteger t{"1a2d4c"}, InvalidInputNumberString);


    BigInteger a{"1234554321"};

    EXPECT_EQ("1234554321", a.getNumber());
    EXPECT_EQ(false, a.isSign());
}

TEST(BigInteger, createFromStringWithSign){
    BigInteger a{"1234554321", true};

    EXPECT_EQ("1234554321", a.getNumber());
    EXPECT_EQ(true, a.isSign());
}

TEST(BigInteger, createFromNumber){
    BigInteger a{123456};

    EXPECT_EQ("123456", a.getNumber());
    EXPECT_EQ(false, a.isSign());

    BigInteger b{-999};

    EXPECT_EQ("999", b.getNumber());
    EXPECT_EQ(true, b.isSign());
}