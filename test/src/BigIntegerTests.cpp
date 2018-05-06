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

TEST(BigInteger, equalityOperator){
    BigInteger a{"123456"};
    BigInteger b{123456};
    BigInteger c{"1"};
    BigInteger d{-1};
    BigInteger q{1};

    EXPECT_TRUE(b == a);
    EXPECT_TRUE(q == c);
    EXPECT_FALSE(b != a);

    EXPECT_TRUE(b != c);
    EXPECT_TRUE(b != d);
    EXPECT_TRUE(c != d);
    EXPECT_FALSE(b != a);
}


TEST(BigInteger, comparisonOperators){
    BigInteger a{1234};
    BigInteger b{1234};
    BigInteger c{111};
    BigInteger d{-1};
    BigInteger q{1};

    EXPECT_FALSE(a > a);
    EXPECT_FALSE(a > b);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_TRUE(a >= d);
    EXPECT_TRUE(a >= q);


    EXPECT_FALSE(a < c);
    EXPECT_TRUE(d < q);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(b <= a);
    EXPECT_TRUE(d <= q);
    EXPECT_TRUE(d < q);
}

TEST(BigInteger, addition){
    BigInteger a{123};
    BigInteger b{23};
    BigInteger c{-46};

    a += b;
    EXPECT_EQ("146", a.getNumber());

    a += c;
    EXPECT_EQ("100", a.getNumber());
}


TEST(BigInteger, subtraction){
    BigInteger a{123};
    BigInteger b{23};
    BigInteger c{-46};
    BigInteger d{-10};

    a -= b;
    EXPECT_EQ("100", a.getNumber());
    EXPECT_EQ(false, a.isSign());


    a -= c;
    EXPECT_EQ("146", a.getNumber());
    EXPECT_EQ(false, a.isSign());

    a += d;
    EXPECT_EQ("136", a.getNumber());
    EXPECT_EQ(false, a.isSign());

}

TEST(BigInteger, multiplication){
    BigInteger a{1};
    BigInteger b{2};
    BigInteger c{-12};
    BigInteger d{99};

    a *= b;
    EXPECT_EQ("2", a.getNumber());
    EXPECT_EQ(false, a.isSign());


    a *= c;
    EXPECT_EQ("24", a.getNumber());
    EXPECT_EQ(true, a.isSign());

    a *= d;
    EXPECT_EQ("2376", a.getNumber());
    EXPECT_EQ(true, a.isSign());
}

TEST(BigInteger, divide){
    BigInteger a{1000};
    BigInteger b{2};
    BigInteger c{-100};
    BigInteger d{100};

    a /= b;
    EXPECT_EQ("500", a.getNumber());
    EXPECT_EQ(false, a.isSign());


    a /= c;
    EXPECT_EQ("5", a.getNumber());
    EXPECT_EQ(true, a.isSign());

    a /= d;
    EXPECT_EQ("0", a.getNumber());
    EXPECT_EQ(false, a.isSign());
}