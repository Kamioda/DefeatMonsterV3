#include <iutest/iutest.hpp>
#include "Number.hpp"
#include <sstream>

template<std::integral I>
struct NumberTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(NumberTest, ::iutest::Types<short, int, long, long long, unsigned short, unsigned int, unsigned long, unsigned long long>);
IUTEST_TYPED_TEST(NumberTest, Constructor) {
    using Number = kamioda::Number<TypeParam>;
    Number num{};
    IUTEST_ASSERT_EQ(num, 0);
    Number num2(10);
    IUTEST_ASSERT_EQ(num2, 10);
    Number num3(10, 5, 15);
    IUTEST_ASSERT_EQ(num3, 10);
    Number num4(num3);
    IUTEST_ASSERT_EQ(num4, 10);
    Number num5(std::move(num4));
    IUTEST_ASSERT_EQ(num5, 10);
}

IUTEST_TYPED_TEST(NumberTest, Assignment) {
    using Number = kamioda::Number<TypeParam>;
    Number num;
    num = 10;
    IUTEST_ASSERT_EQ(num, 10);
    Number num2;
    num2 = num;
    IUTEST_ASSERT_EQ(num2, 10);
    Number num3;
    num3 = std::move(num2);
    IUTEST_ASSERT_EQ(num3, 10);
}

IUTEST_TYPED_TEST(NumberTest, Addition) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num += Number(5);
    IUTEST_ASSERT_EQ(num, 15);
    num += 5;
    IUTEST_ASSERT_EQ(num, 20);
}

IUTEST_TYPED_TEST(NumberTest, Increment) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(num++, 10);
    IUTEST_ASSERT_EQ(num, 11);
    IUTEST_ASSERT_EQ(++num, 12);
}

IUTEST_TYPED_TEST(NumberTest, Subtraction) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num -= Number(5);
    IUTEST_ASSERT_EQ(num, 5);
    num -= 5;
    IUTEST_ASSERT_EQ(num, 0);
}

IUTEST_TYPED_TEST(NumberTest, Decrement) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(num--, 10);
    IUTEST_ASSERT_EQ(num, 9);
    IUTEST_ASSERT_EQ(--num, 8);
}

IUTEST_TYPED_TEST(NumberTest, Multiplication) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num *= Number(5);
    IUTEST_ASSERT_EQ(num, 50);
}

IUTEST_TYPED_TEST(NumberTest, Division) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num /= Number(5);
    IUTEST_ASSERT_EQ(num, 2);
}

IUTEST_TYPED_TEST(NumberTest, Modulus) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num %= Number(5);
    IUTEST_ASSERT_EQ(num, 0);
}

IUTEST_TYPED_TEST(NumberTest, Clamp) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10, 5, 15);
    IUTEST_ASSERT_EQ(num, 10);
    num = 20;
    IUTEST_ASSERT_EQ(num, 15);
    num = 0;
    IUTEST_ASSERT_EQ(num, 5);
}

IUTEST_TYPED_TEST(NumberTest, Comparison) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(num, 10);
    IUTEST_ASSERT_NE(num, 5);
    IUTEST_ASSERT_LT(num, 15);
    IUTEST_ASSERT_LE(num, 15);
    IUTEST_ASSERT_GT(num, 5);
    IUTEST_ASSERT_GE(num, 5);
}

IUTEST_TYPED_TEST(NumberTest, Stream) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    std::ostringstream oss;
    oss << num;
    IUTEST_ASSERT_EQ(oss.str(), "10");
}

IUTEST_TYPED_TEST(NumberTest, Exception) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_THROW(num /= Number(0), std::runtime_error);
}

IUTEST_TYPED_TEST(NumberTest, Cast) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(num.get<int>(), 10);
    IUTEST_ASSERT_EQ(num.get<long>(), 10);
    IUTEST_ASSERT_EQ(num.get<long long>(), 10);
}

IUTEST_TYPED_TEST(NumberTest, Arithmetic) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(~num, static_cast<TypeParam>(-11));
    IUTEST_ASSERT_EQ(num + Number(5), 15);
    IUTEST_ASSERT_EQ(num - Number(5), 5);
    IUTEST_ASSERT_EQ(num * Number(5), 50);
    IUTEST_ASSERT_EQ(num / Number(5), 2);
    IUTEST_ASSERT_EQ(num % Number(5), 0);
    IUTEST_ASSERT_EQ(num & Number(5), 0);
    IUTEST_ASSERT_EQ(num | Number(5), 15);
    IUTEST_ASSERT_EQ(num ^ Number(5), 15);
    IUTEST_ASSERT_EQ(num << 1, 20);
    IUTEST_ASSERT_EQ(num >> 1, 5);
}

IUTEST_TYPED_TEST(NumberTest, Logical) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_TRUE(num);
    IUTEST_ASSERT_FALSE(!num);
    IUTEST_ASSERT_TRUE(num && Number(5));
    IUTEST_ASSERT_TRUE(num || Number(5));
}

IUTEST_TYPED_TEST(NumberTest, Bitwise) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(num & Number(5), 0);
    IUTEST_ASSERT_EQ(num | Number(5), 15);
    IUTEST_ASSERT_EQ(num ^ Number(5), 15);
    IUTEST_ASSERT_EQ(~num, static_cast<TypeParam>(-11));
    IUTEST_ASSERT_EQ(num << 1, 20);
    IUTEST_ASSERT_EQ(num >> 1, 5);
}
