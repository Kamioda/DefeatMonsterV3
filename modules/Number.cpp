#include <iutest.hpp>
#include "Number.hpp"
#include <sstream>

template<std::integral I>
struct NumberTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(NumberTest, ::iutest::Types<short, int, long, long long, unsigned short, unsigned int, unsigned long, unsigned long long>);
IUTEST_TYPED_TEST(NumberTest, Constructor) {
    using Number = kamioda::Number<TypeParam>;
    Number num{};
    IUTEST_ASSERT_EQ(0, num);
    Number num2(10);
    IUTEST_ASSERT_EQ(10, num2);
    Number num3(10, 5, 15);
    IUTEST_ASSERT_EQ(10, num3);
    Number num4(num3);
    IUTEST_ASSERT_EQ(10, num4);
    Number num5(std::move(num4));
    IUTEST_ASSERT_EQ(10, num5);
}

IUTEST_TYPED_TEST(NumberTest, Assignment) {
    using Number = kamioda::Number<TypeParam>;
    Number num;
    num = 10;
    IUTEST_ASSERT_EQ(10, num);
    Number num2;
    num2 = num;
    IUTEST_ASSERT_EQ(10, num2);
    Number num3;
    num3 = std::move(num2);
    IUTEST_ASSERT_EQ(10, num3);
}

IUTEST_TYPED_TEST(NumberTest, Addition) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num += Number(5);
    IUTEST_ASSERT_EQ(15, num);
    num += 5;
    IUTEST_ASSERT_EQ(20, num);
}

IUTEST_TYPED_TEST(NumberTest, Increment) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(10, num++);
    IUTEST_ASSERT_EQ(11, num);
    IUTEST_ASSERT_EQ(12, ++num);
}

IUTEST_TYPED_TEST(NumberTest, Subtraction) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num -= Number(5);
    IUTEST_ASSERT_EQ(5, num);
    num -= 5;
    IUTEST_ASSERT_EQ(0, num);
}

IUTEST_TYPED_TEST(NumberTest, Decrement) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(10, num--);
    IUTEST_ASSERT_EQ(9, num);
    IUTEST_ASSERT_EQ(8, --num);
}

IUTEST_TYPED_TEST(NumberTest, Multiplication) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num *= Number(5);
    IUTEST_ASSERT_EQ(50, num);
}

IUTEST_TYPED_TEST(NumberTest, Division) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num /= Number(5);
    IUTEST_ASSERT_EQ(2, num);
}

IUTEST_TYPED_TEST(NumberTest, Modulus) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    num %= Number(5);
    IUTEST_ASSERT_EQ(0, num);
}

IUTEST_TYPED_TEST(NumberTest, Clamp) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10, 5, 15);
    IUTEST_ASSERT_EQ(10, num);
    num = 20;
    IUTEST_ASSERT_EQ(15, num);
    num = 0;
    IUTEST_ASSERT_EQ(5, num);
}

IUTEST_TYPED_TEST(NumberTest, Comparison) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(10, num);
    IUTEST_ASSERT_NE(5, num);
    IUTEST_ASSERT_GT(15, num);
    IUTEST_ASSERT_GE(15, num);
    IUTEST_ASSERT_LT(5, num);
    IUTEST_ASSERT_LE(5, num);
}

IUTEST_TYPED_TEST(NumberTest, Stream) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    std::ostringstream oss{};
    oss << num;
    IUTEST_ASSERT_EQ("10", oss.str());
}

IUTEST_TYPED_TEST(NumberTest, Exception) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_THROW(num /= Number(0), std::runtime_error);
}

IUTEST_TYPED_TEST(NumberTest, Cast) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(10, num.get<int>());
    IUTEST_ASSERT_EQ(10, num.get<long>());
    IUTEST_ASSERT_EQ(10, num.get<long long>());
}

IUTEST_TYPED_TEST(NumberTest, Arithmetic) {
    using Number = kamioda::Number<TypeParam>;
    Number num(10);
    IUTEST_ASSERT_EQ(static_cast<TypeParam>(-11), ~num);
    IUTEST_ASSERT_EQ(15, num + Number(5));
    IUTEST_ASSERT_EQ(5, num - Number(5));
    IUTEST_ASSERT_EQ(50, num * Number(5));
    IUTEST_ASSERT_EQ(2, num / Number(5));
    IUTEST_ASSERT_EQ(0, num % Number(5));
    IUTEST_ASSERT_EQ(0, num & Number(5));
    IUTEST_ASSERT_EQ(15, num | Number(5));
    IUTEST_ASSERT_EQ(15, num ^ Number(5));
    IUTEST_ASSERT_EQ(20, num << 1);
    IUTEST_ASSERT_EQ(5, num >> 1);
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
    IUTEST_ASSERT_EQ(0, num & Number(5));
    IUTEST_ASSERT_EQ(15, num | Number(5));
    IUTEST_ASSERT_EQ(15, num ^ Number(5));
    IUTEST_ASSERT_EQ(static_cast<TypeParam>(-11), ~num);
    IUTEST_ASSERT_EQ(20, num << 1);
    IUTEST_ASSERT_EQ(5, num >> 1);
}
